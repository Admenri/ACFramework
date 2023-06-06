#ifndef ACF_BROWSER_HANDLER_H_
#define ACF_BROWSER_HANDLER_H_

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_types.h"

#include "include/acf_browser.h"
#include "include/acf_context_menu.h"
#include "include/acf_environment.h"
#include "include/acf_frame.h"
#include "include/acf_values.h"
#include "include/acf_request.h"

class AcfCallback;
class AcfEnvironment;
class AcfBrowser;
class AcfNewWindowDelegate;
class AcfProfile;
class AcfFrame;
class AcfLoginDelegate;
class AcfContextMenuCallback;
class AcfDictionaryValue;
class AcfRequest;

///
/// Browser event list handler model
///
/*--acf(source=client)--*/
class AcfBrowserHandler : public virtual AcfBaseRefCounted {
 public:
  typedef acf_new_window_source_t NewWindowSource;
  typedef acf_new_window_disposition_t NewWindowDisposition;
  typedef acf_navigation_types_t NavigationTypes;

  ///
  /// Called when browser has been initialized from environment.
  ///
  /*--acf()--*/
  virtual void OnBrowserCreated(AcfRefPtr<AcfBrowser> browser) {}

  ///
  /// The browser will open a new Browser as NewWindow
  ///
  /*--acf()--*/
  virtual void OnNewWindowRequest(AcfRefPtr<AcfBrowser> browser,
                                  NewWindowSource source,
                                  NewWindowDisposition disposition,
                                  bool user_gesture,
                                  AcfRefPtr<AcfNewWindowDelegate> delegate) {}

  ///
  /// When the browser was sured to be destroyed,
  /// the browser will call this event.
  ///
  /*--acf()--*/
  virtual void OnBrowserDestroyed(AcfRefPtr<AcfBrowser> browser) {}

  ///
  /// Loading state changed (async)
  ///
  /*--acf()--*/
  virtual void OnLoadingStateChanged(AcfRefPtr<AcfBrowser> browser,
                                     bool show_loading_ui) {}

  ///
  /// Navigation state changed (title url icon historical)
  ///
  /*--acf()--*/
  virtual void OnNavigationStateChanged(AcfRefPtr<AcfBrowser> browser,
                                        NavigationTypes flags) {}

  ///
  /// Title bar info changed
  ///
  /*--acf(optional_param=title)--*/
  virtual void OnTitleChanged(AcfRefPtr<AcfBrowser> browser,
                              const AcfString& title) {}

  ///
  /// Address bar info changed
  ///
  /*--acf(optional_param=address)--*/
  virtual void OnAddressChanged(AcfRefPtr<AcfBrowser> browser,
                                const AcfString& address) {}

  ///
  /// notify fullscreen state changed
  ///
  /*--acf()--*/
  virtual void OnFullscreenStateChanged(AcfRefPtr<AcfBrowser> browser,
                                        bool fullscreen) {}

  ///
  /// network need auth request
  ///
  /*--acf(optional_param=url,optional_param=scheme,optional_param=realm,optional_param=challenge)--*/
  virtual void OnAuthLoginRequest(AcfRefPtr<AcfBrowser> browser,
                                  bool is_proxy,
                                  const AcfString& url,
                                  const AcfString& scheme,
                                  const AcfString& realm,
                                  const AcfString& challenge,
                                  bool is_main_frame,
                                  AcfRefPtr<AcfLoginDelegate> delegate) {}
  ///
  /// Context menu request, return true for blocking menu popup
  ///
  /*--acf()--*/
  virtual void OnContextMenuRequest(
      AcfRefPtr<AcfBrowser> browser,
      AcfRefPtr<AcfContextMenuParams> menu_params,
      AcfRefPtr<AcfContextMenuModel> menu_model,
      AcfRefPtr<AcfContextMenuCallback> callback) {}

  ///
  /// Context menu request to execute |command_id| associate item command.
  ///
  /*--acf()--*/
  virtual void OnContextMenuExecute(AcfRefPtr<AcfBrowser> browser,
                                    AcfRefPtr<AcfContextMenuParams> menu_params,
                                    int command_id,
                                    int event_flags) {}

  ///
  /// Load start notify
  ///
  /*--acf()--*/
  virtual void OnLoadStart(AcfRefPtr<AcfBrowser> browser,
                           AcfRefPtr<AcfFrame> frame,
                           int transition) {}

  ///
  /// Load end notify
  ///
  /*--acf(optional_param=url)--*/
  virtual void OnLoadEnd(AcfRefPtr<AcfBrowser> browser,
                         AcfRefPtr<AcfFrame> frame,
                         const AcfString& url,
                         int http_status_code) {}

  ///
  /// Load error notify
  ///
  /*--acf(optional_param=url)--*/
  virtual void OnLoadError(AcfRefPtr<AcfBrowser> browser,
                           AcfRefPtr<AcfFrame> frame,
                           const AcfString& url,
                           int error_code) {}

  ///
  /// Called when the page icon changes.
  ///
  /*--acf(optional_param=icon_urls)--*/
  virtual void OnFaviconURLChange(AcfRefPtr<AcfBrowser> browser,
                                  const std::vector<AcfString>& icon_urls) {}

  ///
  /// Called to display a console message.
  ///
  /*--acf(optional_param=message,optional_param=source,optional_param=trace)--*/
  virtual void OnConsoleMessage(AcfRefPtr<AcfBrowser> browser,
                                int level,
                                const AcfString& message,
                                const AcfString& source,
                                int line,
                                const AcfString& trace) {}

  ///
  /// Called when the overall page loading progress has changed. |progress|
  /// ranges from 0.0 to 1.0.
  ///
  /*--acf()--*/
  virtual void OnLoadingProgressChange(AcfRefPtr<AcfBrowser> browser,
                                       double progress) {}

  ///
  /// Called when audible state was changed.
  ///
  /*--acf()--*/
  virtual void OnAudioStateChange(AcfRefPtr<AcfBrowser> browser, bool audible) {
  }

  ///
  /// Called when muted state was changed.
  ///
  /*--acf()--*/
  virtual void DidMuteStateUpdate(AcfRefPtr<AcfBrowser> browser, bool muted) {}

  ///
  /// Async running on browser navigation request, default: Continue(false).
  /// The request object is readonly without any post data and cookie data.
  ///
  /*--acf()--*/
  virtual void OnBeforeNavigation(AcfRefPtr<AcfBrowser> browser,
                                  AcfRefPtr<AcfFrame> frame,
                                  AcfRefPtr<AcfRequest> request,
                                  bool user_gesture,
                                  bool is_redirect,
                                  AcfRefPtr<AcfCallback> callback) {}
  
};

#endif  // ACF_BROWSER_HANDLER_H_