
#include "client_window.h"
#include "message_loop_manager.h"

#include <sstream>

#define IDC_GoBack 201
#define IDC_GoForward 202
#define IDC_Reload 203
#define IDC_Stop 204
#define IDC_Nav 205
#define IDC_More 206

#define IDC_NewWindow 301
#define IDC_CloseWindow 302
#define IDC_ToggleVisible 303
#define IDC_ClearCache 304
#define IDC_EnumFrames 305
#define IDC_ExecuteJS 306
#define IDC_GetSource 307
#define IDC_GetAllCookies 308
#define IDC_MuteAudio 309
#define IDC_ToggleDevtools 310
#define IDC_Find 311
#define IDC_ZoomIn 312
#define IDC_ZoomReset 313
#define IDC_ZoomOut 314
#define IDC_TaskManager 315
#define IDC_KeyEvent 316
#define IDC_MouseEvent 317
#define IDC_SetProxy 318

extern AcfRefPtr<AcfProfile> g_profile;
extern AcfRefPtr<AcfEnvironment> g_env;
extern acfclient::MessageWindow* msg_dispatcher;

namespace {

class TestCookieVisitor : public AcfCookieVisitor {
 public:
  TestCookieVisitor() {}
  ~TestCookieVisitor() {}

  void Visit(AcfRefPtr<AcfCookiesGetter> cookie_getter) override {
    for (size_t i = 0; i < cookie_getter->GetCookiesCount(); i++) {
      std::cout << "Name: "
                << cookie_getter->GetCookieAt(i)->GetName().ToString()
                << " Value: "
                << cookie_getter->GetCookieAt(i)->GetValue().ToString() << '\n';
    }
  }

  IMPLEMENT_REFCOUNTING(TestCookieVisitor);
};

class TestStringVisitor : public AcfStringVisitor {
 public:
  TestStringVisitor() {}
  ~TestStringVisitor() {}

  void Visit(const AcfString& string) override {
    std::cout << "String Visitor: PayloadSize: " << string.size() << '\n';
  }

  IMPLEMENT_REFCOUNTING(TestStringVisitor);
};

class TestJSCallback : public AcfCompleteValueHandler {
 public:
  TestJSCallback() { std::cout << "JSCallback Init\n"; }
  ~TestJSCallback() { std::cout << "JSCallback Quit\n"; }

  void OnComplete(AcfRefPtr<AcfValue> value) override {
    std::stringstream ss;
    if (value->GetType() == AcfValueType::VTYPE_INT)
      ss << value->GetInt();
    if (value->GetType() == AcfValueType::VTYPE_STRING)
      ss << value->GetString().ToString();
    AcfString str(ss.str());
    MessageBox(0, (LPWSTR)str.ToString16().data(), L"Execute result", 0);
  }

  IMPLEMENT_REFCOUNTING(TestJSCallback);
};

class TestTask_Quit : public acfclient::Task {
 public:
  TestTask_Quit() {}
  ~TestTask_Quit() override {}

  void Execute() override;

  IMPLEMENT_REFCOUNTING(TestTask_Quit);
};

void TestTask_Quit::Execute() {
  PostQuitMessage(0);
}

class TestTask_NewWindow : public acfclient::Task {
 public:
  TestTask_NewWindow() {}
  ~TestTask_NewWindow() override {}

  void Execute() override;

  AcfRefPtr<AcfNewWindowDelegate> new_browser_delegate_;
  AcfString url_;

  IMPLEMENT_REFCOUNTING(TestTask_NewWindow);
};

void TestTask_NewWindow::Execute() {
  AcfRefPtr<acfclient::Window> window = new acfclient::Window(
      g_env, GetModuleHandle(0), nullptr, new_browser_delegate_);
  ::SetWindowText(window->GetEditHandle(), (LPCWSTR)url_.ToString16().c_str());
  window->Show();
}

}  // namespace

namespace acfclient {

std::vector<AcfRefPtr<AcfBrowser>> g_browsers;

static const wchar_t kClassName[] = L"acfClient_Window";

WNDPROC SetWndProcPtr(HWND hWnd, WNDPROC wndProc) {
  WNDPROC old =
      reinterpret_cast<WNDPROC>(::GetWindowLongPtr(hWnd, GWLP_WNDPROC));
  [[maybe_unused]] LONG_PTR result = ::SetWindowLongPtr(
      hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndProc));
  return old;
}

void SetUserDataPtr(HWND hWnd, void* ptr) {
  SetLastError(ERROR_SUCCESS);
  [[maybe_unused]] LONG_PTR result =
      ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(ptr));
}

template <typename T>
T GetUserDataPtr(HWND hWnd) {
  return reinterpret_cast<T>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
}

Window::Window(AcfRefPtr<AcfEnvironment> env,
               HINSTANCE instance,
               RECT* initial_rect,
               AcfRefPtr<AcfNewWindowDelegate> new_window)
    : instance_(instance), new_browser_delegate_(new_window) {
  RegisterWindowClass();

  [[maybe_unused]] int x, y, width, height;
  if (!initial_rect || ::IsRectEmpty(initial_rect)) {
    // Use the default window position/size.
    x = y = width = height = CW_USEDEFAULT;
  } else {
    x = initial_rect->left;
    y = initial_rect->top;
    width = initial_rect->right - initial_rect->left;
    height = initial_rect->bottom - initial_rect->top;
  }

  const DWORD dwStyle = WS_OVERLAPPEDWINDOW;
  window_ = CreateWindow(kClassName, L"acfclient", dwStyle, x, y, width, height,
                         nullptr, nullptr, instance, this);
  UpdateWindow(window_);

  // Create browser
  AcfBrowserCreateParams params;
  RECT bound = GetBrowserBound();

  CreateMenu();

  if (IsWindow(window_)) {
    std::cout << "[ACFClient] Window:" << window_ << "\n";
  }

  params.parent = window_;
  params.x = bound.left;
  params.y = bound.top;
  params.width = bound.right;
  params.height = bound.bottom;

  // Call on any thread
  env->CreateBrowser(g_profile, this, params, nullptr);

  std::cout << "Window Create: " << g_browsers.size() << "\n";
}

Window::~Window() {
  std::cout << "Window Destroy: " << g_browsers.size() << "\n";

  if (more_menu_)
    DestroyMenu(more_menu_);

  SetUserDataPtr(window_, nullptr);
  PostMessage(window_, WM_CLOSE, 0, 0);

  if (g_browsers.size() <= 0) {
    msg_dispatcher->PostTask(new TestTask_Quit());
  }
}

void Window::Show() {
  ShowWindow(window_, SW_SHOW);
}

void Window::Hide() {
  ShowWindow(window_, SW_HIDE);
}

HWND Window::GetHandle() {
  return window_;
}

HWND Window::GetHandle() const {
  return window_;
}

LRESULT CALLBACK Window::MainWndProc(HWND hWnd,
                                     UINT message,
                                     WPARAM wParam,
                                     LPARAM lParam) {
  Window* self = nullptr;
  self = GetUserDataPtr<Window*>(hWnd);

  // Callback for the main window
  switch (message) {
    case WM_NCCREATE: {
      CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
      self = reinterpret_cast<Window*>(cs->lpCreateParams);
      SetUserDataPtr(hWnd, self);
      break;
    }
    case WM_CREATE: {
      self->OnCreate(hWnd);
      break;
    }
    case WM_SIZE: {
      if (self)
        self->OnSize(hWnd);
      break;
    }
    case WM_CLOSE:
      // wait for browser
      if (self) {
        self->OnClose();
        return 0;
      } else
        break;
    case WM_SETFOCUS: {
      if (self)
        self->OnFocus();
      break;
    }
    case WM_PAINT: {
      PAINTSTRUCT ps;
      BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;
    }
    case WM_COMMAND:
      if (self->OnCommand(LOWORD(wParam)))
        return 0;
      break;
    default:
      break;
  }

  return DefWindowProc(hWnd, message, wParam, lParam);
}

void Window::OnClose() {
  if (browser_weak_ptr_ && browser_weak_ptr_->IsValid()) {
    browser_weak_ptr_->Close(false);
  }
}

void Window::OnFocus() {
  if (browser_weak_ptr_ && browser_weak_ptr_->IsValid()) {
    browser_weak_ptr_->Focus();
  }
}

void Window::CreateMenu() {
  more_menu_ = ::CreatePopupMenu();

  MENUITEMINFO info = {0};
  info.cbSize = sizeof(MENUITEMINFO);

  UINT count = 0;
  std::wstring labelStr;

#define SET_MENU(name, idc)                               \
  labelStr = L##name;                                     \
  info.fMask |= MIIM_STRING | MIIM_ID;                    \
  info.cch = labelStr.size();                             \
  info.dwTypeData = const_cast<LPWSTR>(labelStr.c_str()); \
  info.wID = idc;                                         \
  ::InsertMenuItem(more_menu_, count, TRUE, &info);       \
  count++;

  SET_MENU("New Window", IDC_NewWindow);
  SET_MENU("Close Window", IDC_CloseWindow);
  SET_MENU("Toggle Visibility", IDC_ToggleVisible);
  SET_MENU("Clear All BrowsingData", IDC_ClearCache);
  SET_MENU("Enum Frames Info", IDC_EnumFrames);
  SET_MENU("Execute JS", IDC_ExecuteJS);
  SET_MENU("Get Page Source", IDC_GetSource);
  SET_MENU("Get All Cookies", IDC_GetAllCookies);
  SET_MENU("Mute audio", IDC_MuteAudio);
  SET_MENU("Toggle Devtools", IDC_ToggleDevtools);
  SET_MENU("Task Manager", IDC_TaskManager);
  SET_MENU("Find", IDC_Find);
  SET_MENU("ZoomIn", IDC_ZoomIn);
  SET_MENU("ZoomReset", IDC_ZoomReset);
  SET_MENU("ZoomOut", IDC_ZoomOut);
  SET_MENU("Key Event", IDC_KeyEvent);
  SET_MENU("Mouse Event", IDC_MouseEvent);
  SET_MENU("Set Proxy", IDC_SetProxy);
}

bool Window::OnCommand(UINT id) {
  switch (id) {
    case IDC_GoBack:  // Back button
      if (browser_weak_ptr_)
        browser_weak_ptr_->GoBack();
      break;
    case IDC_GoForward:  // Forward button
      if (browser_weak_ptr_)
        browser_weak_ptr_->GoForward();
      break;
    case IDC_Reload:  // Reload button
      if (browser_weak_ptr_)
        browser_weak_ptr_->Reload(false);
      break;
    case IDC_Stop:  // Stop button
      if (browser_weak_ptr_)
        browser_weak_ptr_->Stop();
      break;
    case IDC_Nav:  // Navigate button
    {
#define MAX_URL_LENGTH 255
      wchar_t strPtr[MAX_URL_LENGTH + 1] = {0};
      *((LPWORD)strPtr) = MAX_URL_LENGTH;
      LRESULT strLen =
          SendMessage(edit_control_, EM_GETLINE, 0, (LPARAM)strPtr);
      if (strLen > 0) {
        strPtr[strLen] = 0;

        browser_weak_ptr_->LoadURL((const char16_t*)strPtr);
      }
#undef MAX_URL_LENGTH
    } break;
    case IDC_More: {
      POINT pt = {0};
      ::GetCursorPos(&pt);

      ::TrackPopupMenu(more_menu_,
                       TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON, pt.x,
                       pt.y, 0, window_, nullptr);
    } break;
    case IDC_NewWindow: {
      std::cout << "Menu: NewWindow\n";

      AcfRefPtr<TestTask_NewWindow> task = new TestTask_NewWindow();
      task->new_browser_delegate_ = nullptr;
      msg_dispatcher->PostTask(task);
    } break;
    case IDC_CloseWindow: {
      std::cout << "Menu: CloseWindow\n";

      PostMessage(window_, WM_CLOSE, 0, 0);
    } break;
    case IDC_ToggleVisible: {
      // toggle visible
      if (browser_weak_ptr_) {
        std::cout << "Menu: Set to Visible: "
                  << !browser_weak_ptr_->GetVisible() << "\n";
        browser_weak_ptr_->SetVisible(!browser_weak_ptr_->GetVisible());
      }
    } break;
    case IDC_ClearCache: {
      g_env->GetDefaultProfile()->RemoveBrowsingData(
          AcfProfile::RemoveDataType::ALL_DATA_TYPES, true, nullptr);
    } break;
    case IDC_EnumFrames: {
      if (browser_weak_ptr_) {
        std::vector<int64> m_ids;
        browser_weak_ptr_->GetFrameIdentifiers(m_ids);

        for (auto i : m_ids) {
          AcfRefPtr<AcfFrame> f = browser_weak_ptr_->GetFrame(i);
          
          if (f)
            std::cout << "FrameID: " << f->GetIdentifier()
                      << " Name: " << f->GetName().ToString()
                      << " URL: " << f->GetURL().ToString() << "\n";
        }
      }
    } break;
    case IDC_ExecuteJS: {
      if (browser_weak_ptr_) {
        std::string script;
        std::cout << "Enter script to eval: ";
        std::cin >> script;
        browser_weak_ptr_->GetMainFrame()->ExecuteJavascript(
            script, "about:blank", new TestJSCallback());
      }
    } break;
    case IDC_GetSource: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->GetMainFrame()->GetSource(new TestStringVisitor());
      }
    } break;
    case IDC_GetAllCookies: {
      if (browser_weak_ptr_) {
        auto cm = g_profile->GetCookieManager();
        cm->GetCookies("", true, new TestCookieVisitor());
      }
    } break;
    case IDC_MuteAudio: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->SetAudioMuted(!browser_weak_ptr_->IsAudioMuted());
      }
    } break;
    case IDC_ToggleDevtools: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->ToggleDevtools();
      }
    } break;
    case IDC_TaskManager: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->OpenTaskManager();
      }
    } break;
    case IDC_Find: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->RaiseFindBar();
      }
    } break;
    case IDC_ZoomIn: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->ZoomPage(ZOOM_IN);
      }
    } break;
    case IDC_ZoomReset: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->ZoomPage(ZOOM_RESET);
      }
    } break;
    case IDC_ZoomOut: {
      if (browser_weak_ptr_) {
        browser_weak_ptr_->ZoomPage(ZOOM_OUT);
      }
    } break;
    case IDC_KeyEvent: {
      if (browser_weak_ptr_) {
        AcfKeyEvent e;
        e.type = acf_key_event_type_t::KEYEVENT_CHAR;
        e.windows_key_code = VK_RETURN;
        e.modifiers = EVENTFLAG_NONE;
        e.is_system_key = false;
        e.focus_on_editable_field = true;
        browser_weak_ptr_->SendKeyEvent(e);
      }
    } break;
    case IDC_MouseEvent: {
      if (browser_weak_ptr_) {
        AcfMouseEvent e;
        std::cout << "MouseXY: \n";
        std::cin >> e.x >> e.y;
        browser_weak_ptr_->SendMouseClickEvent(
            e, AcfBrowser::MouseButtonType::MBT_LEFT, false, 1);
        browser_weak_ptr_->SendMouseClickEvent(
            e, AcfBrowser::MouseButtonType::MBT_LEFT, true, 1);
      }
    } break;
    case IDC_SetProxy: {
      if (browser_weak_ptr_) {
        AcfRefPtr<AcfDictionaryValue> dict = AcfEnvironment::CreateDictionary();
        std::cout << "Enter Proxy (- for empty): ";
        std::string proxy = "-";
        std::cin >> proxy;

        if (proxy != "-") {
          dict->SetString("server", proxy);
          dict->SetString("mode", "fixed_servers");
        } else {
          dict->SetString("mode", "system");
        }

        AcfRefPtr<AcfValue> proxy_value = AcfEnvironment::CreateValue();
        proxy_value->SetDictionary(dict);

        g_profile->SetPreference("proxy", proxy_value, nullptr);
      }
    } break;
    default:
      return false;
  }

  // menu command except
  if (id < 300)
    OnFocus();

  return true;
}

void Window::OnCreate(HWND window) {
  RECT rect;
  GetClientRect(window, &rect);

  int x_offset = 0;

  const int button_width = 72;
  const int urlbar_height = 24;

  back_button_ =
      CreateWindow(L"BUTTON", L"Back", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_GoBack), instance_, 0);
  x_offset += button_width;

  forward_button_ =
      CreateWindow(L"BUTTON", L"Forward", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_GoForward), instance_, 0);
  x_offset += button_width;

  reload_button_ =
      CreateWindow(L"BUTTON", L"Reload", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_Reload), instance_, 0);
  x_offset += button_width;

  stop_button_ =
      CreateWindow(L"BUTTON", L"Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_Stop), instance_, 0);
  x_offset += button_width;

  more_button_ =
      CreateWindow(L"BUTTON", L"More", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                   x_offset, 0, button_width, urlbar_height, window,
                   reinterpret_cast<HMENU>(IDC_More), instance_, 0);
  x_offset += button_width;

  edit_control_ = CreateWindow(L"EDIT", 0,
                               WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT |
                                   ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                               x_offset, 0, rect.right - button_width * 6,
                               urlbar_height, window, 0, instance_, 0);

  nav_button_ = CreateWindow(
      L"BUTTON", L"Navigate", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
      rect.right - button_width, 0, button_width, urlbar_height, window,
      reinterpret_cast<HMENU>(IDC_Nav), instance_, 0);
}

void Window::OnSize(HWND window) {
  RECT rect;
  GetClientRect(window, &rect);

  const int button_width = 72;
  const int urlbar_height = 24;

  SetWindowPos(edit_control_, 0, button_width * 5, 0,
               rect.right - button_width * 6, urlbar_height, SWP_NOZORDER);
  SetWindowPos(nav_button_, 0, rect.right - button_width, 0, button_width,
               urlbar_height, SWP_NOZORDER);

  if (browser_window_)
    SetWindowPos(browser_window_, 0, 0, urlbar_height, rect.right,
                 rect.bottom - urlbar_height, SWP_NOZORDER);
}

RECT Window::GetBrowserBound() {
  const int urlbar_height = 24;

  RECT rect;
  GetClientRect(window_, &rect);

  return {0, urlbar_height, rect.right, rect.bottom - urlbar_height};
}

void Window::RegisterWindowClass() {
  // Only register the class one time.
  static bool class_registered = false;
  if (class_registered)
    return;
  class_registered = true;

  WNDCLASSEX wcex = {0};

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.lpszClassName = kClassName;
  wcex.lpfnWndProc = MainWndProc;
  wcex.hInstance = instance_;
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

  RegisterClassEx(&wcex);
}

void Window::SetBrowser(HWND handle) {
  browser_window_ = handle;
  OnSize(window_);
}

// On Brwoser IPC Thread
void Window::OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {
  std::cout << "OnBrowserCreated\n";

  if (new_browser_delegate_) {
    new_browser_delegate_->SetNewBrowser(browser);
    new_browser_delegate_.reset();
  } else {
    browser->LoadURL("bilibili.com");
  }

  // storage weak ptr
  browser_weak_ptr_ = browser.get();
  SetBrowser(browser->GetWindowHandle());
  Show();

  g_browsers.push_back(browser);
  std::cout << "Append browser\n";
}

void Window::OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser,
                                NewWindowSource source,
                                NewWindowDisposition disposition,
                                bool user_gesture,
                                AcfRefPtr<AcfNewWindowDelegate> delegate) {
  std::cout << "OnNewWindow Request\n";

  AcfRefPtr<TestTask_NewWindow> task = new TestTask_NewWindow();
  task->new_browser_delegate_ = delegate;
  task->url_ = delegate->GetTargetURL();
  msg_dispatcher->PostTask(task);
}

void Window::OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {
  std::cout << "OnBrowserDestroyed\n";

  browser_weak_ptr_ = nullptr;
  for (auto iter = g_browsers.begin(); iter != g_browsers.end(); iter++) {
    if ((*iter)->IsSame(browser)) {
      std::cout << "Remove browser\n";
      g_browsers.erase(iter);
      break;
    }
  }
}

void Window::OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                   bool show_loading_ui) {
  std::cout << "OnLoadingStateChanged\n";

  if (back_button_)
    EnableWindow(back_button_, browser->CanGoBack());
  if (forward_button_)
    EnableWindow(forward_button_, browser->CanGoForward());
  if (reload_button_)
    EnableWindow(reload_button_, !browser->IsLoading());
  if (stop_button_)
    EnableWindow(stop_button_, browser->IsLoading());
}

void Window::OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                      NavigationTypes flags) {
  std::cout << "OnNavigationStateChanged\n";
}

void Window::OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                            const AcfString& title) {
  AcfString rtitle = title.ToString() + " - acfclient";
  SetWindowText(window_, (LPWSTR)rtitle.ToString16().c_str());
}

void Window::OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                              const AcfString& address) {
  SetWindowText(edit_control_, (LPWSTR)address.ToString16().c_str());
}

void Window::OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                      bool fullscreen) {
  std::cout << "OnFullscreenStateChanged: " << fullscreen << "\n";
}

void Window::OnAuthLoginRequest(AcfRefPtr<AcfBrowser> browser,
                                bool is_proxy,
                                const AcfString& url,
                                const AcfString& scheme,
                                const AcfString& realm,
                                const AcfString& challenge,
                                bool is_main_frame,
                                AcfRefPtr<AcfLoginDelegate> delegate) {
  std::cout << "OnAuthLoginRequest: " << url.ToString() << "\n";
  
  // Auth Test
  if (url == "https://authenticationtest.com/HTTPAuth/")
    delegate->Continue("user", "pass");
}

void Window::OnContextMenuRequest(AcfRefPtr<AcfBrowser> browser,
                                  AcfRefPtr<AcfContextMenuParams> menu_params,
                                  AcfRefPtr<AcfContextMenuModel> menu_model,
                                  AcfRefPtr<AcfContextMenuCallback> callback) {
  std::cout << "OnContextMenuRequest\n";
  
  menu_model->InsertSeparatorAt(menu_model->GetCount());
  menu_model->InsertItemAt(menu_model->GetCount(), 310001, "Test Menu Item");
  AcfRefPtr<AcfContextMenuModel> sub_menu = menu_model->InsertSubMenuAt(
      menu_model->GetCount(), 310002, "Sub menu test");
  sub_menu->InsertItemAt(sub_menu->GetCount(), 310003, "Normal item");
  sub_menu->InsertSeparatorAt(sub_menu->GetCount());

  sub_menu->InsertRadioItemAt(sub_menu->GetCount(), 310004, "Item 1", 1000);
  sub_menu->SetCheckedAt(sub_menu->GetCount() - 1, true);

  sub_menu->InsertRadioItemAt(sub_menu->GetCount(), 310005, "Item 2", 1000);
  sub_menu->InsertRadioItemAt(sub_menu->GetCount(), 310006, "Item 3", 1000);
  sub_menu->InsertSeparatorAt(sub_menu->GetCount());
  sub_menu->InsertCheckItemAt(sub_menu->GetCount(), 310007, "Item 1");

  sub_menu->InsertCheckItemAt(sub_menu->GetCount(), 310008, "Item 2");
  sub_menu->SetCheckedAt(sub_menu->GetCount() - 1, true);

  sub_menu->InsertCheckItemAt(sub_menu->GetCount(), 310009, "Item 3");
}

void Window::OnContextMenuExecute(AcfRefPtr<AcfBrowser> browser,
                                  AcfRefPtr<AcfContextMenuParams> menu_params,
                                  int command_id,
                                  int event_flags) {
  if (command_id == 310001)
    MessageBox(window_, L"Execute test menu", L"AcfClient", 0);
  std::cout << "Execute command id: " << command_id << '\n';
}

void Window::OnFaviconURLChange(AcfRefPtr<AcfBrowser> browser,
                                const std::vector<AcfString>& icon_urls) {
  std::cout << "Favicons List: ";
  for (auto i : icon_urls)
    std::cout << i.ToString() << " ";
  std::cout << '\n';
}

void Window::OnConsoleMessage(AcfRefPtr<AcfBrowser> browser,
                              int level,
                              const AcfString& message,
                              const AcfString& source,
                              int line,
                              const AcfString& trace) {
  std::cout << "ConsoleMessage: " << message.ToString() << '\n';
}

void Window::OnLoadingProgressChange(AcfRefPtr<AcfBrowser> browser,
                                     double progress) {}

void Window::OnAudioStateChange(AcfRefPtr<AcfBrowser> browser, bool audible) {
  std::cout << "AudioStateChanged: "
            << (audible ? std::string("true") : std::string("false")) << '\n';
}

void Window::OnLoadStart(AcfRefPtr<AcfBrowser> browser,
                         AcfRefPtr<AcfFrame> frame,
                         int transition) {
  std::cout << "LoadStart: " << frame->GetURL().ToString() << '\n';
}

void Window::OnLoadEnd(AcfRefPtr<AcfBrowser> browser,
                       AcfRefPtr<AcfFrame> frame,
                       const AcfString& url,
                       int http_status_code) {
  std::cout << "LoadEnd: " << frame->GetURL().ToString() << '\n';
}

void Window::OnLoadError(AcfRefPtr<AcfBrowser> browser,
                         AcfRefPtr<AcfFrame> frame,
                         const AcfString& url,
                         int error_code) {}

void Window::OnBeforeNavigation(AcfRefPtr<AcfBrowser> browser,
                                AcfRefPtr<AcfFrame> frame,
                                AcfRefPtr<AcfRequest> request,
                                bool user_gesture,
                                bool is_redirect,
                                AcfRefPtr<AcfCallback> callback) {
  std::cout << "OnBeforeNavigation: URL: " << request->GetURL().ToString()
            << '\n';
}

}  // namespace acfclient