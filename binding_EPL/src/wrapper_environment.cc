
#include "include/acf_environment.h"

#include "message_pump.h"
#include "wrapper_utility.h"
#include "wrapper_handler_interface.h"

#include <memory>
#include <windows.h>
#include <iostream>
#include <atomic>

namespace {

/// <summary>
/// Global UI Thread message pump
/// </summary>
std::unique_ptr<acf_wrapper::MessagePump> g_message_pump;

class UITask : public acf_wrapper::UIThreadTask {
 public:
  using TaskCallback = void(WINAPI*)(intptr_t);
  UITask(TaskCallback cb, intptr_t param) : callback_(cb), param_(param) {}
  ~UITask() override {}

 protected:
  void Execute() override { callback_(param_); }

 private:
  TaskCallback callback_;
  intptr_t param_;

  IMPLEMENT_REFCOUNTING(UITask);
};

} // namespace

extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];

DLL_EXPORTS(PostTaskOnUIThread, BOOL)
(UITask::TaskCallback callback, intptr_t param) {
  g_message_pump->PostTask(new UITask(callback, param));

  return !!g_message_pump;
}

DLL_EXPORTS(InitACFContext, BOOL)() {
  g_message_pump.reset(new acf_wrapper::MessagePump(GetModuleHandle(0)));
  return AcfEnvironment::InitACFContext();
}

DLL_EXPORTS(QuitACFContext, BOOL)() {
  g_message_pump.reset();
  return AcfEnvironment::QuitACFContext();
}

using EnvironmentParams = struct {
  LPCSTR command_line;
  LPCSTR user_data_dir;
};
DLL_EXPORTS(CreateEnvironment, BOOL)
(LPCSTR browser_path, EnvironmentParams* params, LPVOID handler, bool sync,
 DWORD* retObj) {
  AcfRefPtr<wrapper::EnvironmentHandler> lpHandler(
      new wrapper::EnvironmentHandler(handler));
  AcfEnvironmentSettings settings;

  if (params) {
    AcfString(&settings.command_line).FromString(params->command_line);
    AcfString(&settings.user_data_dir).FromString(params->user_data_dir);
  }

  AcfRefPtr<AcfEnvironment> env =
      AcfEnvironment::CreateEnvironment(browser_path, settings, lpHandler);

  if (sync) {
    while (!env->IsValid()) {
      ::Sleep(0);
    }
  }

  if (env) {
    env->AddRef();
    retObj[1] = (DWORD)env.get();
    retObj[2] = (DWORD)acf_cpp_fntable_environment;
  }

  return !!env.get();
}

/// <summary>
/// Export function table pass by memory
/// </summary>
namespace {

BOOL ACF_CALLBACK is_same(AcfEnvironment* obj, AcfEnvironment* that) {
  return obj->IsSame(that);
}

BOOL ACF_CALLBACK is_valid(AcfEnvironment* obj) { return obj->IsValid(); }

DWORD ACF_CALLBACK get_handler(AcfEnvironment* obj) {
  return (DWORD)obj->GetHandler().get();
}

LPSTR ACF_CALLBACK get_version(AcfEnvironment* obj) {
  return GetEString(obj->GetBrowserVersion());
}

uint32_t ACF_CALLBACK get_process_id(AcfEnvironment* obj) {
  return obj->GetProcessPID();
}

int ACF_CALLBACK terminate_process(AcfEnvironment* obj) {
  return obj->Terminate();
}

BOOL ACF_CALLBACK create_profile(AcfEnvironment* obj, LPCSTR path, bool sync,
                                 DWORD* retObj) {
  AcfRefPtr<AcfProfile> profile = obj->CreateProfile(path, nullptr);

  // Wait for thread synchronize
  if (sync) {
    while (!profile->IsValid()) {
      ::Sleep(0);
    }
  }

  if (profile) {
    profile->AddRef();
    retObj[1] = (DWORD)profile.get();
    retObj[2] = (DWORD)acf_cpp_fntable_profile;
  }

  return !!profile.get();
}

using BrowserParams = struct {
  HWND parent;
  bool visible;
  int x;
  int y;
  int width;
  int height;
};
BOOL ACF_CALLBACK create_browser(AcfEnvironment* obj, AcfProfile* profile,
                                 BrowserParams* pparams, AcfDictionaryValue* extra,
                                 LPVOID callback,
                                 DWORD* retObj) {
  AcfRefPtr<wrapper::BrowserHandler> lphandler(
      new wrapper::BrowserHandler(callback));

  AcfBrowserCreateParams params;
  params.parent = pparams->parent;
  params.visible = pparams->visible;
  params.x = pparams->x;
  params.y = pparams->y;
  params.width = pparams->width;
  params.height = pparams->height;

  AcfRefPtr<AcfBrowser> browser =
      obj->CreateBrowser(profile, lphandler, params, extra);

  if (browser) {
    browser->AddRef();
    retObj[1] = (DWORD)browser.get();
    retObj[2] = (DWORD)acf_cpp_fntable_browser;
  }

  return !!browser.get();
}

BOOL ACF_CALLBACK get_default_profile(AcfEnvironment* obj, DWORD* retObj) {
  AcfRefPtr<AcfProfile> pf = obj->GetDefaultProfile();

  if (pf) {
    pf->AddRef();
    retObj[1] = (DWORD)pf.get();
    retObj[2] = (DWORD)acf_cpp_fntable_profile;
  }

  return !!pf.get();
}

}  // namespacek

DWORD acf_cpp_fntable_environment[] = {
    (DWORD)is_same,        (DWORD)is_valid,       (DWORD)get_handler,
    (DWORD)get_version,    (DWORD)get_process_id, (DWORD)terminate_process,
    (DWORD)create_profile, (DWORD)create_browser, (DWORD)get_default_profile,
};
