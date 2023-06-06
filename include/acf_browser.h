#ifndef ACF_BROWSER_H_
#define ACF_BROWSER_H_

#include <wtypes.h>

#include "include/acf_environment.h"
#include "include/acf_frame.h"
#include "include/acf_context_menu.h"
#include "include/acf_values.h"
#include "include/acf_browser_handler.h"

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_string_list.h"
#include "include/internal/acf_types.h"
#include "include/internal/acf_types_wrappers.h"

class AcfEnvironment;
class AcfBrowser;
class AcfNewWindowDelegate;
class AcfProfile;
class AcfFrame;
class AcfLoginDelegate;
class AcfContextMenuCallback;
class AcfDictionaryValue;

///
/// ACF's browser object host,
/// in fact a browser was a window in chromium with tabs control.
///
/*--acf(source=library)--*/
class AcfBrowser : public virtual AcfBaseRefCounted {
 public:
  typedef acf_mouse_button_type_t MouseButtonType;
  typedef acf_zoom_type_t ZoomType;

  ///
  /// Is same object
  ///
  /*--acf()--*/
  virtual bool IsSame(AcfRefPtr<AcfBrowser> that) = 0;

  ///
  /// Get browser event handler
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfBrowserHandler> GetHandler() = 0;

  ///
  /// Get browser create's sign.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfDictionaryValue> GetExtraInfo() = 0;

  ///
  /// Get parent environment
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfEnvironment> GetEnvironment() = 0;

  ///
  /// Close browser, it will call browser close event (or unlaod dialog)
  ///
  /*--acf()--*/
  virtual void Close(bool force) = 0;

  ///
  /// Get browser window handle
  ///
  /*--acf()--*/
  virtual AcfWindowHandle GetWindowHandle() = 0;

  ///
  /// Get delegate status
  ///
  /*--acf()--*/
  virtual bool IsValid() = 0;

  ///
  /// Browser navigation entry controller: can go back
  ///
  /*--acf()--*/
  virtual bool CanGoBack() = 0;

  ///
  /// Browser navigation entry controller: can go forward
  ///
  /*--acf()--*/
  virtual bool CanGoForward() = 0;

  ///
  /// Browser navigation entry controller: go back
  ///
  /*--acf()--*/
  virtual void GoBack() = 0;

  ///
  /// Browser navigation entry controller: go forward
  ///
  /*--acf()--*/
  virtual void GoForward() = 0;

  ///
  /// Browser navigation entry controller: reload
  ///
  /*--acf()--*/
  virtual void Reload(bool ignore_cache) = 0;

  ///
  /// Browser navigation entry controller: stop loading
  ///
  /*--acf()--*/
  virtual void Stop() = 0;

  ///
  /// Browser navigation entry controller: loading
  ///
  /*--acf()--*/
  virtual bool IsLoading() = 0;

  ///
  /// Navigate to target url (Main frame)
  ///
  /*--acf()--*/
  virtual void LoadURL(const AcfString& url) = 0;

  ///
  /// Get current url
  ///
  /*--acf()--*/
  virtual AcfString GetURL() = 0;
  
  ///
  /// Get title
  ///
  /*--acf()--*/
  virtual AcfString GetTitle() = 0;

  ///
  /// Focus to native widget
  ///
  /*--acf()--*/
  virtual void Focus() = 0;

  ///
  /// Set/Get window visible
  ///
  /*--acf()--*/
  virtual void SetVisible(bool visible) = 0;

  ///
  /// Get visibility
  ///
  /*--acf()--*/
  virtual bool GetVisible() = 0;

  ///
  /// Get profile object, maybe null
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfProfile> GetProfile() = 0;

  ///
  /// Returns the number of frames that currently exist.
  ///
  /*--acf()--*/
  virtual size_t GetFrameCount() = 0;

  ///
  /// Returns the identifiers of all existing frames.
  ///
  /*--acf(count_func=identifiers:GetFrameCount)--*/
  virtual void GetFrameIdentifiers(std::vector<int64>& identifiers) = 0;

  ///
  /// Returns the names of all existing frames.
  ///
  /*--acf()--*/
  virtual void GetFrameNames(std::vector<AcfString>& names) = 0;

  ///
  /// Returns the frame with the specified identifier, or NULL if not found.
  ///
  /*--acf(capi_name=get_frame_byident)--*/
  virtual AcfRefPtr<AcfFrame> GetFrame(int64 identifier) = 0;

  ///
  /// Returns the frame with the specified name, or NULL if not found.
  ///
  /*--acf(optional_param=name)--*/
  virtual AcfRefPtr<AcfFrame> GetFrame(const AcfString& name) = 0;

  ///
  /// Returns the main (top-level) frame for the browser. In the browser process
  /// this will return a valid object until after
  /// CefLifeSpanHandler::OnBeforeClose is called. In the renderer process this
  /// will return NULL if the main frame is hosted in a different renderer
  /// process (e.g. for cross-origin sub-frames). The main frame object will
  /// change during cross-origin navigation or re-navigation after renderer
  /// process termination (due to crashes, etc).
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfFrame> GetMainFrame() = 0;

  ///
  /// Set browser additional settings. (Dynamic)
  ///
  /*--acf()--*/
  virtual void SetSettings(const AcfBrowserSettings& settings) = 0;

  ///
  /// Send a key event to the browser.
  ///
  /*--acf()--*/
  virtual void SendKeyEvent(const AcfKeyEvent& event) = 0;

  ///
  /// Send a mouse click event to the browser. The |x| and |y| coordinates are
  /// relative to the upper-left corner of the view.
  ///
  /*--acf()--*/
  virtual void SendMouseClickEvent(const AcfMouseEvent& event,
                                   MouseButtonType type,
                                   bool mouseUp,
                                   int clickCount) = 0;

  ///
  /// Send a mouse move event to the browser. The |x| and |y| coordinates are
  /// relative to the upper-left corner of the view.
  ///
  /*--acf()--*/
  virtual void SendMouseMoveEvent(const AcfMouseEvent& event,
                                  bool mouseLeave) = 0;

  ///
  /// Send a mouse wheel event to the browser. The |x| and |y| coordinates are
  /// relative to the upper-left corner of the view. The |deltaX| and |deltaY|
  /// values represent the movement delta in the X and Y directions
  /// respectively. In order to scroll inside select popups with window
  /// rendering disabled CefRenderHandler::GetScreenPoint should be implemented
  /// properly.
  ///
  /*--acf()--*/
  virtual void SendMouseWheelEvent(const AcfMouseEvent& event,
                                   int deltaX,
                                   int deltaY) = 0;
  
  ///
  /// Set audio mute state
  ///
  /*--acf()--*/
  virtual void SetAudioMuted(bool muted) = 0;

  ///
  /// Get audio mute state
  ///
  /*--acf()--*/
  virtual bool IsAudioMuted() = 0;

  ///
  /// Toggle devtools
  ///
  /*--acf()--*/
  virtual void ToggleDevtools() = 0;

  ///
  /// Open a browser task manager
  ///
  /*--acf()--*/
  virtual void OpenTaskManager() = 0;

  ///
  /// Raise find bar
  ///
  /*--acf()--*/
  virtual void RaiseFindBar() = 0;

  ///
  /// Zoom page in current browser
  ///
  /*--acf()--*/
  virtual void ZoomPage(ZoomType zoom_type) = 0;
};

///
/// New Window delegate,
/// set a new browser to host target page.
/// Request will be handled while object was destroyed without handled.
///
/*--acf(source=library)--*/
class AcfNewWindowDelegate : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Set a browser to handle the new window
  /// new browser's profile must suit the host browser's profile,
  /// otherwise return false.
  ///
  /*--acf()--*/
  virtual bool SetNewBrowser(AcfRefPtr<AcfBrowser> browser) = 0;

  ///
  /// Get target url
  ///
  /*--acf()--*/
  virtual AcfString GetTargetURL() = 0;

  ///
  /// Put if user has been handled the request.
  /// This method will send the final request to browser.
  ///
  /*--acf()--*/
  virtual void HandleRequest(bool handled) = 0;
};

///
/// Network auth callback delegate
///
/*--acf(source=library)--*/
class AcfLoginDelegate : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Continue with username and password
  ///
  /*--acf(capi_name=cont)--*/
  virtual void Continue(const AcfString& user_name,
                        const AcfString& password) = 0;

  ///
  /// Cancel auth request (Default process)
  ///
  /*--acf()--*/
  virtual void Cancel() = 0;
};

///
/// Context menu callback
///
/*--acf(source=library)--*/
class AcfContextMenuCallback : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Continue show menu
  ///
  /*--acf(capi_name=cont)--*/
  virtual void Continue(bool suppress) = 0;
};

#endif