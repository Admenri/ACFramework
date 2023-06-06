
#include "wrapper_handler_interface.h"

#include "wrapper_acfclass.h"

#include "struct_class.h"

extern DWORD acf_cpp_fntable_browser[];
extern DWORD acf_cpp_fntable_new_window_delegate[];
extern DWORD acf_cpp_fntable_environment[];
extern DWORD acf_cpp_fntable_profile[];
extern DWORD acf_cpp_fntable_frame[];
extern DWORD acf_cpp_fntable_value[];
extern DWORD acf_cpp_fntable_authcallback[];
extern DWORD acf_cpp_fntable_menucallback[];
extern DWORD acf_cpp_fntable_menuparams[];
extern DWORD acf_cpp_fntable_menumodel[];
extern DWORD acf_cpp_fntable_request[];
extern DWORD acf_cpp_fntable_response[];
extern DWORD acf_cpp_fntable_responsecallback[];

namespace wrapper {

EnvironmentHandler::EnvironmentHandler(LPVOID callback) : callback_(callback) {}

EnvironmentHandler::~EnvironmentHandler() {
  if (callback_) LocalFree(callback_);
}

void EnvironmentHandler::OnInitialized(AcfRefPtr<AcfEnvironment> env,
                                       bool success) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    env->AddRef();
    IMP_NEWECLASS(TempEnv, env.get(), eClass::m_pVfTable_Environment,
                  acf_cpp_fntable_environment);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, success; 
			push eax;
			push TempEnv;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    env->Release();
  }
}

AcfRefPtr<AcfResourceRequestHandler>
EnvironmentHandler::GetResourceRequestHandler(
    AcfRefPtr<AcfProfile> profile, int64 frame_id,
    AcfRefPtr<AcfRequest> request, bool is_navigation, bool is_download,
    const AcfString& request_initiator, bool& block_request) {
  BOOL bRetVal = false;
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);
    LPSTR pinitiator = GetEString(request_initiator);
    LPVOID lpInitiator = &pinitiator;
    bool* pblock = &block_request;
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pblock;
			push lpInitiator;
			movzx eax, is_download;
			push eax;
			movzx eax, is_navigation;
			push eax;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x0C];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
  }
  return bRetVal ? this : nullptr;
}

bool EnvironmentHandler::OnBeforeResourceLoad(AcfRefPtr<AcfProfile> profile,
                                              int64 frame_id,
                                              AcfRefPtr<AcfRequest> request) {
  BOOL bRetVal = false;
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x10];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
  }
  return bRetVal;
}

AcfRefPtr<AcfResourceHandler> EnvironmentHandler::GetResourceHandler(
    AcfRefPtr<AcfProfile> profile, int64 frame_id,
    AcfRefPtr<AcfRequest> request) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);

    AcfRefPtr<ACFResourceResponseCallback> callback =
        new ACFResourceResponseCallback();
    IMP_NEWECLASS(TempCallback, callback.get(),
                  eClass::m_pVfTable_ResponseCallback,
                  acf_cpp_fntable_responsecallback);

    callback->AddRef();

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();

    callback->Release();
    return callback->GetResponse();
  }
  return nullptr;
}

void EnvironmentHandler::OnResourceRedirect(AcfRefPtr<AcfProfile> profile,
                                            int64 frame_id,
                                            AcfRefPtr<AcfRequest> request,
                                            AcfRefPtr<AcfResponse> response,
                                            AcfString& new_url) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    response->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfTable_Response,
                  acf_cpp_fntable_response);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);

    LPCSTR purl = GetEString(new_url);
    LPVOID ppurl = &purl;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppurl;
			push TempResponse;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
    response->Release();
  }
}

void EnvironmentHandler::OnResourceResponse(AcfRefPtr<AcfProfile> profile,
                                            int64 frame_id,
                                            AcfRefPtr<AcfRequest> request,
                                            AcfRefPtr<AcfResponse> response) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    response->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfTable_Response,
                  acf_cpp_fntable_response);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempResponse;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
    response->Release();
  }
}

AcfRefPtr<AcfResponseFilter> EnvironmentHandler::GetResourceResponseFilter(
    AcfRefPtr<AcfProfile> profile, int64 frame_id,
    AcfRefPtr<AcfRequest> request, AcfRefPtr<AcfResponse> response) {
  BOOL bRetVal = FALSE;
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    response->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfTable_Response,
                  acf_cpp_fntable_response);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempResponse;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x20];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
    response->Release();
  }
  return bRetVal ? new ACFResourceFilterHandler(callback_, profile, frame_id,
                                                request, response)
                 : nullptr;
}

void EnvironmentHandler::OnResourceLoadComplete(AcfRefPtr<AcfProfile> profile,
                                                int64 frame_id,
                                                AcfRefPtr<AcfRequest> request,
                                                AcfRefPtr<AcfResponse> response,
                                                URLRequestStatus status,
                                                int64 received_content_length) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    profile->AddRef();
    request->AddRef();
    response->AddRef();
    IMP_NEWECLASS(TempProfile, profile.get(), eClass::m_pVfTable_Profile,
                  acf_cpp_fntable_profile);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    IMP_NEWECLASS(TempResponse, response.get(), eClass::m_pVfTable_Response,
                  acf_cpp_fntable_response);
    int* pFID = (int*)&frame_id;
    int pFID_1 = *pFID;
    int pFID_2 = *(pFID + 1);

		int* pLEN = (int*)&received_content_length;
    int pLEN_1 = *pLEN;
    int pLEN_2 = *(pLEN + 1);

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pLEN_2;
			push pLEN_1;
			push status;
			push TempResponse;
			push TempRequest;
			push pFID_2;
			push pFID_1;
			push TempProfile;
			push ecx;
			call[edx + 0x28];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    profile->Release();
    request->Release();
    response->Release();
  }
}

BrowserHandler::BrowserHandler(LPVOID callback) : callback_(callback) {}

BrowserHandler::~BrowserHandler() {
  if (callback_) LocalFree(callback_);
}

void BrowserHandler::OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x08];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnNewWindowRequest(
    AcfRefPtr<AcfBrowser> browser, NewWindowSource source,
    NewWindowDisposition disposition, bool user_gesture,
    AcfRefPtr<AcfNewWindowDelegate> delegate) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    delegate->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempDelegate, delegate.get(),
                  eClass::m_pVfTable_NewWindowDelegate,
                  acf_cpp_fntable_new_window_delegate);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempDelegate;
			movzx eax, user_gesture;
			push eax;
			push disposition;
			push source;
			push TempBrowser;
			push ecx;
			call[edx + 0x0C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    delegate->Release();
    browser->Release();
  }
}

void BrowserHandler::OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempBrowser;
			push ecx;
			call[edx + 0x10];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                           bool show_loading_ui) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, show_loading_ui;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x14];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                              NavigationTypes flags) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push flags;
			push TempBrowser;
			push ecx;
			call[edx + 0x18];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                                    const AcfString& title) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    LPSTR pTitle = GetEString(title);
    LPVOID ppTitle = &pTitle;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppTitle;
			push TempBrowser;
			push ecx;
			call[edx + 0x1C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                                      const AcfString& address) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    LPSTR pTitle = GetEString(address);
    LPVOID ppTitle = &pTitle;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppTitle;
			push TempBrowser;
			push ecx;
			call[edx + 0x20];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                              bool fullscreen) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, fullscreen;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x24];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadStart(AcfRefPtr<AcfBrowser> browser,
                                 AcfRefPtr<AcfFrame> frame, int transition) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push transition;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x28];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadEnd(AcfRefPtr<AcfBrowser> browser,
                               AcfRefPtr<AcfFrame> frame, const AcfString& url,
                               int http_status_code) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push http_status_code;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x2C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadError(AcfRefPtr<AcfBrowser> browser,
                                 AcfRefPtr<AcfFrame> frame,
                                 const AcfString& url, int error_code) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push error_code;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x30];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnAuthLoginRequest(
    AcfRefPtr<AcfBrowser> browser, bool is_proxy, const AcfString& url,
    const AcfString& scheme, const AcfString& realm, const AcfString& challenge,
    bool is_main_frame, AcfRefPtr<AcfLoginDelegate> delegate) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempCallback, delegate.get(), eClass::m_pVfTable_AuthCallback,
                  acf_cpp_fntable_authcallback);

    LPCSTR pUrl = GetEString(url), pScheme = GetEString(scheme),
           pRealm = GetEString(realm), pChallenge = GetEString(challenge);

    LPVOID ppURL = &pUrl, ppScheme = &pScheme, ppRealm = &pRealm,
           ppChallenge = &pChallenge;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			movzx eax, is_main_frame;
			push eax;
			push ppChallenge;
			push ppRealm;
			push ppScheme;
			push ppURL;
			movzx eax, is_proxy;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x34];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnContextMenuRequest(
    AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfContextMenuParams> menu_params,
    AcfRefPtr<AcfContextMenuModel> menu_model,
    AcfRefPtr<AcfContextMenuCallback> callback) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempParams, menu_params.get(), eClass::m_pVfTable_MenuParams,
                  acf_cpp_fntable_menuparams);
    IMP_NEWECLASS(TempModel, menu_model.get(), eClass::m_pVfTable_MenuModel,
                  acf_cpp_fntable_menumodel);
    IMP_NEWECLASS(TempCallback, callback.get(), eClass::m_pVfTable_MenuCallback,
                  acf_cpp_fntable_menucallback);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push TempCallback;
			push TempModel;
			push TempParams;
			push TempBrowser;
			push ecx;
			call[edx + 0x38];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnContextMenuExecute(
    AcfRefPtr<AcfBrowser> browser, AcfRefPtr<AcfContextMenuParams> menu_params,
    int command_id, int event_flags) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempParams, menu_params.get(), eClass::m_pVfTable_MenuParams,
                  acf_cpp_fntable_menuparams);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push event_flags;
			push command_id;
			push TempParams;
			push TempBrowser;
			push ecx;
			call[edx + 0x3C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnFaviconURLChange(
    AcfRefPtr<AcfBrowser> browser, const std::vector<AcfString>& icon_urls) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

    DWORD* pStrs = new DWORD[icon_urls.size()];
    for (size_t i = 0; i < icon_urls.size(); i++) {
      pStrs[i] = (DWORD)GetEString(icon_urls[i].c_str());
    }

    int nSize = icon_urls.size() * sizeof(DWORD);
    LPSTR pAry = (LPSTR)malloc(sizeof(INT) * 2 + nSize);
    *(LPINT)pAry = 1;
    *(LPINT)(pAry + sizeof(INT)) = icon_urls.size();
    memcpy(pAry + sizeof(INT) * 2, pStrs, nSize);
    delete[] pStrs;

    LPVOID pList = &pAry;

    browser->AddRef();
    __asm {
			push ecx;
			push esi;
			push edi;
			push ebx;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pList;
			push TempBrowser;
			push ecx;
			call[edx + 0x40];
			pop ecx;
			pop ebx;
			pop edi;
			pop esi;
    }
    browser->Release();
  }
}

void BrowserHandler::OnConsoleMessage(AcfRefPtr<AcfBrowser> browser, int level,
                                      const AcfString& message,
                                      const AcfString& source, int line,
                                      const AcfString& trace) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

		LPCSTR pMsg = GetEString(message);
    LPVOID ppMsg = &pMsg;

		LPCSTR pSrc = GetEString(source);
    LPVOID ppSrc = &pSrc;

		LPCSTR pTrace = GetEString(trace);
    LPVOID ppTrace = &pTrace;

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push ppTrace;
			push line;
			push ppSrc;
			push ppMsg;
			push level;
			push TempBrowser;
			push ecx;
			call[edx + 0x44];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnLoadingProgressChange(AcfRefPtr<AcfBrowser> browser,
                                             double progress) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);

		int* pPro = (int*)&progress;
    int pPro_1 = *pPro;
    int pPro_2 = *(pPro + 1);

    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			push pPro_2;
			push pPro_1;
			push TempBrowser;
			push ecx;
			call[edx + 0x48];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnAudioStateChange(AcfRefPtr<AcfBrowser> browser,
                                        bool audible) {
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, audible;
			push eax;
			push TempBrowser;
			push ecx;
			call[edx + 0x4C];
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
  }
}

void BrowserHandler::OnBeforeNavigation(AcfRefPtr<AcfBrowser> browser,
                                        AcfRefPtr<AcfFrame> frame,
                                        AcfRefPtr<AcfRequest> request,
                                        bool user_gesture, bool is_redirect,
                                        AcfRefPtr<AcfCallback> callback) {
  BOOL bRetVal = FALSE;
  if (this->callback_ != NULL) {
    LPVOID pClass = this->callback_;
    browser->AddRef();
    frame->AddRef();
    request->AddRef();
    IMP_NEWECLASS(TempBrowser, browser.get(), eClass::m_pVfTable_Browser,
                  acf_cpp_fntable_browser);
    IMP_NEWECLASS(TempFrame, frame.get(), eClass::m_pVfTable_Frame,
                  acf_cpp_fntable_frame);
    IMP_NEWECLASS(TempRequest, request.get(), eClass::m_pVfTable_Request,
                  acf_cpp_fntable_request);
    __asm {
			push ecx;
			push ebx;
			push edi;
			push esi;
			mov ebx, pClass;
			mov edx, [ebx];
			lea ecx, pClass;
			movzx eax, is_redirect;
			push eax;
			movzx eax, user_gesture;
			push eax;
			push TempRequest;
			push TempFrame;
			push TempBrowser;
			push ecx;
			call[edx + 0x50];
			mov bRetVal, eax;
			pop esi;
			pop edi;
			pop ebx;
			pop ecx;
    }
    browser->Release();
    frame->Release();
    request->Release();
  }
  callback->Continue(bRetVal);
}

}  // namespace wrapper