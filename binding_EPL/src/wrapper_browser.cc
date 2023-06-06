
#include "include/acf_browser.h"
#include "wrapper_utility.h"

extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];
extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_frame[];
extern DWORD acf_cpp_fntable_value[];
extern DWORD acf_cpp_fntable_dictionary[];

namespace {

BOOL ACF_CALLBACK is_same(AcfBrowser* obj, AcfBrowser* that) {
  return obj->IsSame(that);
}

BOOL ACF_CALLBACK is_valid(AcfBrowser* obj) { return obj->IsValid(); }

BOOL ACF_CALLBACK get_env(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfEnvironment> env = obj->GetEnvironment();

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_environment;
  }

  return !!env.get();
}

BOOL ACF_CALLBACK get_profile(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfProfile> env = obj->GetProfile();

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_profile;
  }

  return !!env.get();
}

HWND ACF_CALLBACK get_hwnd(AcfBrowser* obj) { return obj->GetWindowHandle(); }

void ACF_CALLBACK close(AcfBrowser* obj, bool force) { obj->Close(force); }

BOOL ACF_CALLBACK can_goback(AcfBrowser* obj) { return obj->CanGoBack(); }

BOOL ACF_CALLBACK can_goforward(AcfBrowser* obj) { return obj->CanGoForward(); }

void ACF_CALLBACK goback(AcfBrowser* obj) { obj->GoBack(); }

void ACF_CALLBACK goforward(AcfBrowser* obj) { obj->GoForward(); }

void ACF_CALLBACK reload(AcfBrowser* obj, bool cache) { obj->Reload(cache); }

void ACF_CALLBACK stop(AcfBrowser* obj) { obj->Stop(); }

BOOL ACF_CALLBACK isloading(AcfBrowser* obj) { return obj->IsLoading(); }

void ACF_CALLBACK load_url(AcfBrowser* obj, LPCSTR url) {
  return obj->LoadURL(url);
}

LPSTR ACF_CALLBACK get_url(AcfBrowser* obj) {
  return GetEString(obj->GetURL());
}

LPSTR ACF_CALLBACK get_title(AcfBrowser* obj) {
  return GetEString(obj->GetTitle());
}

void ACF_CALLBACK focus(AcfBrowser* obj) { obj->Focus(); }

void ACF_CALLBACK set_visible(AcfBrowser* obj, bool visible) {
  obj->SetVisible(visible);
}

BOOL ACF_CALLBACK get_visible(AcfBrowser* obj) { return obj->GetVisible(); }

BOOL ACF_CALLBACK get_user_data(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfDictionaryValue> data = obj->GetExtraInfo();

  if (retObj && data) {
    data->AddRef();
    retObj[1] = (DWORD)data.get();
    retObj[2] = (DWORD)acf_cpp_fntable_dictionary;
  }

  return !!retObj;
}

int ACF_CALLBACK get_frame_count(AcfBrowser* obj) {
  return obj->GetFrameCount();
}

bool ACF_CALLBACK get_frame_identifiers(AcfBrowser* obj, LPVOID* eArray) {
  ISVALIDR(obj, NULL);

  std::vector<int64> data;

  obj->GetFrameIdentifiers(data);

  FreeAryElement(*eArray);

  int nSize = data.size() * sizeof(int64);
  LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
  *(LPINT)pAry = 1;
  *(LPINT)(pAry + sizeof(INT)) = data.size();
  memcpy(pAry + sizeof(INT) * 2, data.data(), nSize);

  *eArray = pAry;

  return !!eArray;
}

bool ACF_CALLBACK get_frame_names(AcfBrowser* obj, LPVOID* eArray) {
  ISVALIDR(obj, NULL);

  std::vector<AcfString> keys;
  obj->GetFrameNames(keys);

  LPSTR* pStrs = new LPSTR[keys.size()];
  for (size_t i = 0; i < keys.size(); i++) {
    pStrs[i] = GetEString(keys[i].c_str());
  }

  FreeAryElement(*eArray);

  int nSize = keys.size() * sizeof(DWORD);
  LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
  *(LPINT)pAry = 1;
  *(LPINT)(pAry + sizeof(INT)) = keys.size();
  memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
  delete[] pStrs;

  *eArray = pAry;

  return 0;
}

BOOL ACF_CALLBACK get_frame_by_name(AcfBrowser* obj, LPCSTR name,
                                    DWORD* retObj) {
  AcfRefPtr<AcfFrame> frame = obj->GetFrame(name);

  if (frame) {
    frame->AddRef();
    retObj[1] = (DWORD)frame.get();
    retObj[2] = (DWORD)acf_cpp_fntable_frame;
  }

  return !!frame.get();
}

BOOL ACF_CALLBACK get_frame_by_id(AcfBrowser* obj, int64_t* id, DWORD* retObj) {
  AcfRefPtr<AcfFrame> frame = obj->GetFrame(*id);

  if (frame) {
    frame->AddRef();
    retObj[1] = (DWORD)frame.get();
    retObj[2] = (DWORD)acf_cpp_fntable_frame;
  }

  return !!frame.get();
}

BOOL ACF_CALLBACK get_main_frame(AcfBrowser* obj, DWORD* retObj) {
  AcfRefPtr<AcfFrame> frame = obj->GetMainFrame();

  if (frame) {
    frame->AddRef();
    retObj[1] = (DWORD)frame.get();
    retObj[2] = (DWORD)acf_cpp_fntable_frame;
  }

  return !!frame.get();
}

void ACF_CALLBACK set_browser_settings(AcfBrowser* obj,
                                       acf_browser_settings_t** settings) {
  obj->SetSettings(**settings);
}

void ACF_CALLBACK key_event(AcfBrowser* obj, acf_key_event_t** event) {
  obj->SendKeyEvent(**event);
}

void ACF_CALLBACK mouse_click_event(AcfBrowser* obj, acf_mouse_event_t** event,
                                    acf_mouse_button_type_t type, bool up,
                                    int count) {
  obj->SendMouseClickEvent(**event, type, up, count);
}

void ACF_CALLBACK mouse_move_event(AcfBrowser* obj, acf_mouse_event_t** event,
                                   bool leave) {
  obj->SendMouseMoveEvent(**event, leave);
}

void ACF_CALLBACK mouse_wheel_event(AcfBrowser* obj, acf_mouse_event_t** event,
                                    int x, int y) {
  obj->SendMouseWheelEvent(**event, x, y);
}

void ACF_CALLBACK mute_audio(AcfBrowser* obj, bool mute) {
  obj->SetAudioMuted(mute);
}

bool ACF_CALLBACK get_mute_audio(AcfBrowser* obj) {
  return obj->IsAudioMuted();
}

void ACF_CALLBACK toggle_devtools(AcfBrowser* obj) { obj->ToggleDevtools(); }

void ACF_CALLBACK toggle_taskmanager(AcfBrowser* obj) {
  obj->OpenTaskManager();
}

void ACF_CALLBACK toggle_findbar(AcfBrowser* obj) { obj->RaiseFindBar(); }

void ACF_CALLBACK zoom_page(AcfBrowser* obj, acf_zoom_type_t type) {
  obj->ZoomPage(type);
}

/// <summary>
/// New Window Delagate
/// </summary>
/// <param name="obj"></param>
/// <returns></returns>

BOOL ACF_CALLBACK set_new_browser(AcfNewWindowDelegate* obj,
                                  AcfBrowser* browser) {
  return obj->SetNewBrowser(browser);
}

LPSTR ACF_CALLBACK get_target_url(AcfNewWindowDelegate* obj) {
  return GetEString(obj->GetTargetURL());
}

void ACF_CALLBACK handle_new_window(AcfNewWindowDelegate* obj, bool handle) {
  obj->HandleRequest(handle);
}

}  // namespace

DWORD acf_cpp_fntable_browser[] = {
    (DWORD)is_same,
    (DWORD)is_valid,
    (DWORD)get_env,
    (DWORD)get_profile,
    (DWORD)get_hwnd,
    (DWORD)close,
    (DWORD)can_goback,
    (DWORD)can_goforward,
    (DWORD)goback,
    (DWORD)goforward,
    (DWORD)reload,
    (DWORD)stop,
    (DWORD)isloading,
    (DWORD)load_url,
    (DWORD)get_url,
    (DWORD)get_title,
    (DWORD)focus,
    (DWORD)set_visible,
    (DWORD)get_visible,
    (DWORD)get_user_data,
    (DWORD)get_frame_count,
    (DWORD)get_frame_identifiers,
    (DWORD)get_frame_names,
    (DWORD)get_frame_by_name,
    (DWORD)get_frame_by_id,
    (DWORD)get_main_frame,
    (DWORD)set_browser_settings,
    (DWORD)key_event,
    (DWORD)mouse_click_event,
    (DWORD)mouse_move_event,
    (DWORD)mouse_wheel_event,
    (DWORD)mute_audio,
    (DWORD)get_mute_audio,
    (DWORD)toggle_devtools,
    (DWORD)toggle_taskmanager,
    (DWORD)toggle_findbar,
    (DWORD)zoom_page,
};

DWORD acf_cpp_fntable_new_window_delegate[] = {
    (DWORD)set_new_browser,
    (DWORD)get_target_url,
    (DWORD)handle_new_window,
};

namespace {

bool ACF_CALLBACK frame_is_valid(AcfFrame* obj) { return obj->IsValid(); }

bool ACF_CALLBACK frame_is_same(AcfFrame* obj, AcfFrame* that) {
  return obj->IsSame(that);
}

BOOL ACF_CALLBACK frame_get_parent(AcfFrame* obj, DWORD* retObj) {
  AcfRefPtr<AcfFrame> frame = obj->GetParent();

  if (frame) {
    frame->AddRef();
    retObj[1] = (DWORD)frame.get();
    retObj[2] = (DWORD)acf_cpp_fntable_frame;
  }

  return !!frame.get();
}

BOOL ACF_CALLBACK frame_get_browser(AcfFrame* obj, DWORD* retObj) {
  AcfRefPtr<AcfBrowser> frame = obj->GetBrowser();

  if (frame) {
    frame->AddRef();
    retObj[1] = (DWORD)frame.get();
    retObj[2] = (DWORD)acf_cpp_fntable_browser;
  }

  return !!frame.get();
}

LPSTR ACF_CALLBACK frame_get_url(AcfFrame* obj) {
  return GetEString(obj->GetURL());
}

void ACF_CALLBACK frame_get_id(AcfFrame* obj, int64_t* ret) {
  *ret = obj->GetIdentifier();
}

bool ACF_CALLBACK frame_is_main(AcfFrame* obj) { return obj->IsMain(); }

class ExecJsCallback : public AcfCompleteValueHandler {
 public:
  ExecJsCallback(std::atomic<bool>* notify) : notify_(notify) {}
  ~ExecJsCallback() {}

  AcfRefPtr<AcfValue> GetResult() { return result_; }

 protected:
  void OnComplete(AcfRefPtr<AcfValue> value) override {
    result_ = value;
    *notify_ = true;
  }

 private:
  std::atomic<bool>* notify_;
  AcfRefPtr<AcfValue> result_;

  IMPLEMENT_REFCOUNTING(ExecJsCallback);
};

BOOL ACF_CALLBACK frame_execute_javascript(AcfFrame* obj, LPCSTR script,
                                           LPCSTR url, DWORD* retObj) {
  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);
  AcfRefPtr<ExecJsCallback> lpHandler = new ExecJsCallback(notify.get());
  obj->ExecuteJavascript(script, url, lpHandler);

  if (retObj) {
    while (!*notify) {
      ::Sleep(10);
    }

    AcfRefPtr<AcfValue> value = lpHandler->GetResult();

    if (value) {
      value->AddRef();
      retObj[1] = (DWORD)value.get();
      retObj[2] = (DWORD)acf_cpp_fntable_value;
    }
  }

  return !!lpHandler->GetResult().get();
}

class GetTextSync : public AcfStringVisitor {
 public:
  GetTextSync(std::atomic<bool>* notify) : notify_(notify) {}
  ~GetTextSync() {}

  std::string GetResult() { return result_; }

 protected:
  void Visit(const AcfString& string) override {
    result_ = string;
    *notify_ = true;
  }

 private:
  std::string result_;
  std::atomic<bool>* notify_;

  IMPLEMENT_REFCOUNTING(GetTextSync);
};

void ACF_CALLBACK frame_get_source(AcfFrame* obj, LPSTR* retStr) {
  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);
  AcfRefPtr<GetTextSync> lpHandler = new GetTextSync(notify.get());
  obj->GetSource(lpHandler);

  while (!*notify) {
    ::Sleep(0);
  }

  *retStr = GetEString(lpHandler->GetResult());
}

void ACF_CALLBACK frame_get_text(AcfFrame* obj, LPSTR* retStr) {
  std::unique_ptr<std::atomic<bool>> notify =
      std::make_unique<std::atomic<bool>>(false);
  AcfRefPtr<GetTextSync> lpHandler = new GetTextSync(notify.get());
  obj->GetText(lpHandler);

  while (!*notify) {
    ::Sleep(0);
  }

  *retStr = GetEString(lpHandler->GetResult());
}

}  // namespace

DWORD acf_cpp_fntable_frame[] = {
    (DWORD)frame_is_valid,   (DWORD)frame_is_same,
    (DWORD)frame_get_parent, (DWORD)frame_get_browser,
    (DWORD)frame_get_url,    (DWORD)frame_get_id,
    (DWORD)frame_is_main,    (DWORD)frame_execute_javascript,
    (DWORD)frame_get_source, (DWORD)frame_get_text,
};
