#ifndef ACF_ENUMS_H_
#define ACF_ENUMS_H_

typedef enum {
  /// New contents, included javascript 'window.open'
  /// or click on normal link
  NEW_CONTENTS = 0,

  /// Includes open url in menu context,
  /// and other chrome built-in operation.
  OPEN_FROM_TAB_URL,
} acf_new_window_source_t;

typedef enum {
  UNKNOWN,
  CURRENT_TAB,
  /// Indicates that only one tab with the url should exist in the same window.
  SINGLETON_TAB,
  NEW_FOREGROUND_TAB,
  NEW_BACKGROUND_TAB,
  NEW_POPUP,
  NEW_WINDOW,
  SAVE_TO_DISK,
  OFF_THE_RECORD,
  IGNORE_ACTION,
  /// Activates an existing tab containing the url, rather than navigating.
  /// This is similar to SINGLETON_TAB, but searches across all windows from
  /// the current profile and anonymity (instead of just the current one);
  /// closes the current tab on switching if the current tab was the NTP with
  /// no session history; and behaves like CURRENT_TAB instead of
  /// NEW_FOREGROUND_TAB when no existing tab is found.
  SWITCH_TO_TAB,
  /// Creates a new document picture-in-picture window showing a child WebView.
  NEW_PICTURE_IN_PICTURE,
  /// Update when adding a new disposition.
  MAX_VALUE = NEW_PICTURE_IN_PICTURE,
} acf_new_window_disposition_t;

typedef enum {
  INVALIDATE_TYPE_URL = 1 << 0,    /// The URL has changed.
  INVALIDATE_TYPE_TAB = 1 << 1,    /// The favicon, app icon, or crashed
                                   /// state changed.
  INVALIDATE_TYPE_LOAD = 1 << 2,   /// The loading state has changed.
  INVALIDATE_TYPE_TITLE = 1 << 3,  /// The title changed.
  INVALIDATE_TYPE_AUDIO = 1 << 4,  /// The tab became audible or
                                   /// inaudible.
                                   /// TODO(crbug.com/846374):
                                   /// remove this.

  INVALIDATE_TYPE_ALL = (1 << 5) - 1,
} acf_navigation_types_t;

typedef enum {
  DATA_TYPE_HISTORY = 1 << 0,
  DATA_TYPE_FORM_DATA = 1 << 1,
  DATA_TYPE_PASSWORDS = 1 << 2,
  DATA_TYPE_SITE_USAGE_DATA = 1 << 3,
  DATA_TYPE_DURABLE_PERMISSION = 1 << 4,
  DATA_TYPE_EXTERNAL_PROTOCOL_DATA = 1 << 5,
  DATA_TYPE_HOSTED_APP_DATA_TEST_ONLY = 1 << 6,
  DATA_TYPE_CONTENT_SETTINGS = 1 << 7,
  DATA_TYPE_BOOKMARKS = 1 << 8,
  DATA_TYPE_ISOLATED_ORIGINS = 1 << 9,
  DATA_TYPE_ACCOUNT_PASSWORDS = 1 << 10,
  DATA_TYPE_LOCAL_CUSTOM_DICTIONARY = 1 << 11,
  DATA_TYPE_SITE_DATA = 1 << 12,
  IMPORTANT_SITES_DATA_TYPES = 1 << 13,
  FILTERABLE_DATA_TYPES = 1 << 14,
  DEFERRED_COOKIE_DELETION_DATA_TYPES = 1 << 15,

  ALL_DATA_TYPES = 0xffffffff,
} acf_remove_data_type_t;

///
/// Supported value types.
///
typedef enum {
  VTYPE_INVALID = 0,
  VTYPE_NULL,
  VTYPE_BOOL,
  VTYPE_INT,
  VTYPE_DOUBLE,
  VTYPE_STRING,
  VTYPE_BINARY,
  VTYPE_DICTIONARY,
  VTYPE_LIST,
} acf_value_type_t;

///
/// Cookie priority values.
///
typedef enum {
  ACF_COOKIE_PRIORITY_LOW = 0,
  ACF_COOKIE_PRIORITY_MEDIUM = 1,
  ACF_COOKIE_PRIORITY_HIGH = 2,
} acf_cookie_priority_t;

///
/// Cookie same site values.
///
typedef enum {
  ACF_COOKIE_SAME_SITE_UNSPECIFIED = -1,
  ACF_COOKIE_SAME_SITE_NO_RESTRICTION = 0,
  ACF_COOKIE_SAME_SITE_LAX_MODE = 1,
  ACF_COOKIE_SAME_SITE_STRICT_MODE = 2,
} acf_cookie_same_site_t;

///
/// Supported context menu type flags.
///
typedef enum {
  ///
  /// No node is selected.
  ///
  CM_TYPEFLAG_NONE = 0,
  ///
  /// The top page is selected.
  ///
  CM_TYPEFLAG_PAGE = 1 << 0,
  ///
  /// A subframe page is selected.
  ///
  CM_TYPEFLAG_FRAME = 1 << 1,
  ///
  /// A link is selected.
  ///
  CM_TYPEFLAG_LINK = 1 << 2,
  ///
  /// A media node is selected.
  ///
  CM_TYPEFLAG_MEDIA = 1 << 3,
  ///
  /// There is a textual or mixed selection that is selected.
  ///
  CM_TYPEFLAG_SELECTION = 1 << 4,
  ///
  /// An editable element is selected.
  ///
  CM_TYPEFLAG_EDITABLE = 1 << 5,
} acf_context_menu_type_flags_t;

///
/// Supported menu item types.
///
typedef enum {
  MENUITEMTYPE_NONE = 0,
  MENUITEMTYPE_COMMAND,
  MENUITEMTYPE_CHECK,
  MENUITEMTYPE_RADIO,
  MENUITEMTYPE_SEPARATOR,
  MENUITEMTYPE_SUBMENU,
} acf_menu_item_type_t;

///
/// Supported context menu media types. These constants match their equivalents
/// in Chromium's ContextMenuDataMediaType and should not be renumbered.
///
typedef enum {
  ///
  /// No special node is in context.
  ///
  CM_MEDIATYPE_NONE = 0,
  ///
  /// An image node is selected.
  ///
  CM_MEDIATYPE_IMAGE,
  ///
  /// A video node is selected.
  ///
  CM_MEDIATYPE_VIDEO,
  ///
  /// An audio node is selected.
  ///
  CM_MEDIATYPE_AUDIO,
  ///
  /// An canvas node is selected.
  ///
  CM_MEDIATYPE_CANVAS,
  ///
  /// A file node is selected.
  ///
  CM_MEDIATYPE_FILE,
  ///
  /// A plugin node is selected.
  ///
  CM_MEDIATYPE_PLUGIN,
} acf_context_menu_media_type_t;

///
/// Supported context menu media state bit flags. These constants match their
/// equivalents in Chromium's ContextMenuData::MediaFlags and should not be
/// renumbered.
///
typedef enum {
  CM_MEDIAFLAG_NONE = 0,
  CM_MEDIAFLAG_IN_ERROR = 1 << 0,
  CM_MEDIAFLAG_PAUSED = 1 << 1,
  CM_MEDIAFLAG_MUTED = 1 << 2,
  CM_MEDIAFLAG_LOOP = 1 << 3,
  CM_MEDIAFLAG_CAN_SAVE = 1 << 4,
  CM_MEDIAFLAG_HAS_AUDIO = 1 << 5,
  CM_MEDIAFLAG_CAN_TOGGLE_CONTROLS = 1 << 6,
  CM_MEDIAFLAG_CONTROLS = 1 << 7,
  CM_MEDIAFLAG_CAN_PRINT = 1 << 8,
  CM_MEDIAFLAG_CAN_ROTATE = 1 << 9,
  CM_MEDIAFLAG_CAN_PICTURE_IN_PICTURE = 1 << 10,
  CM_MEDIAFLAG_PICTURE_IN_PICTURE = 1 << 11,
  CM_MEDIAFLAG_CAN_LOOP = 1 << 12,
} acf_context_menu_media_state_flags_t;

///
/// Supported context menu edit state bit flags. These constants match their
/// equivalents in Chromium's ContextMenuDataEditFlags and should not be
/// renumbered.
///
typedef enum {
  CM_EDITFLAG_NONE = 0,
  CM_EDITFLAG_CAN_UNDO = 1 << 0,
  CM_EDITFLAG_CAN_REDO = 1 << 1,
  CM_EDITFLAG_CAN_CUT = 1 << 2,
  CM_EDITFLAG_CAN_COPY = 1 << 3,
  CM_EDITFLAG_CAN_PASTE = 1 << 4,
  CM_EDITFLAG_CAN_DELETE = 1 << 5,
  CM_EDITFLAG_CAN_SELECT_ALL = 1 << 6,
  CM_EDITFLAG_CAN_TRANSLATE = 1 << 7,
  CM_EDITFLAG_CAN_EDIT_RICHLY = 1 << 8,
} acf_context_menu_edit_state_flags_t;

typedef enum {
  EVENTFLAG_NONE = 0,
  EVENTFLAG_CAPS_LOCK_ON = 1 << 0,
  EVENTFLAG_SHIFT_DOWN = 1 << 1,
  EVENTFLAG_CONTROL_DOWN = 1 << 2,
  EVENTFLAG_ALT_DOWN = 1 << 3,
  EVENTFLAG_LEFT_MOUSE_BUTTON = 1 << 4,
  EVENTFLAG_MIDDLE_MOUSE_BUTTON = 1 << 5,
  EVENTFLAG_RIGHT_MOUSE_BUTTON = 1 << 6,
  /// Mac OS-X command key.
  EVENTFLAG_COMMAND_DOWN = 1 << 7,
  EVENTFLAG_NUM_LOCK_ON = 1 << 8,
  EVENTFLAG_IS_KEY_PAD = 1 << 9,
  EVENTFLAG_IS_LEFT = 1 << 10,
  EVENTFLAG_IS_RIGHT = 1 << 11,
  EVENTFLAG_ALTGR_DOWN = 1 << 12,
  EVENTFLAG_IS_REPEAT = 1 << 13,
} acf_event_flags_t;

///
/// Mouse button types.
///
typedef enum {
  MBT_LEFT = 0,
  MBT_MIDDLE,
  MBT_RIGHT,
} acf_mouse_button_type_t;

///
/// Zoom type
///
typedef enum {
  ZOOM_IN = 0,
  ZOOM_RESET,
  ZOOM_OUT,
} acf_zoom_type_t;

///
/// Policy for how the Referrer HTTP header value will be sent during
/// navigation. If the `--no-referrers` command-line flag is specified then the
/// policy value will be ignored and the Referrer value will never be sent. Must
/// be kept synchronized with net::URLRequest::ReferrerPolicy from Chromium.
///
typedef enum {
  ///
  /// Clear the referrer header if the header value is HTTPS but the request
  /// destination is HTTP. This is the default behavior.
  ///
  REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_FROM_SECURE_TO_INSECURE,
  REFERRER_POLICY_DEFAULT =
      REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_FROM_SECURE_TO_INSECURE,

  ///
  /// A slight variant on CLEAR_REFERRER_ON_TRANSITION_FROM_SECURE_TO_INSECURE:
  /// If the request destination is HTTP, an HTTPS referrer will be cleared. If
  /// the request's destination is cross-origin with the referrer (but does not
  /// downgrade), the referrer's granularity will be stripped down to an origin
  /// rather than a full URL. Same-origin requests will send the full referrer.
  ///
  REFERRER_POLICY_REDUCE_REFERRER_GRANULARITY_ON_TRANSITION_CROSS_ORIGIN,

  ///
  /// Strip the referrer down to an origin when the origin of the referrer is
  /// different from the destination's origin.
  ///
  REFERRER_POLICY_ORIGIN_ONLY_ON_TRANSITION_CROSS_ORIGIN,

  ///
  /// Never change the referrer.
  ///
  REFERRER_POLICY_NEVER_CLEAR_REFERRER,

  ///
  /// Strip the referrer down to the origin regardless of the redirect location.
  ///
  REFERRER_POLICY_ORIGIN,

  ///
  /// Clear the referrer when the request's referrer is cross-origin with the
  /// request's destination.
  ///
  REFERRER_POLICY_CLEAR_REFERRER_ON_TRANSITION_CROSS_ORIGIN,

  ///
  /// Strip the referrer down to the origin, but clear it entirely if the
  /// referrer value is HTTPS and the destination is HTTP.
  ///
  REFERRER_POLICY_ORIGIN_CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE,

  ///
  /// Always clear the referrer regardless of the request destination.
  ///
  REFERRER_POLICY_NO_REFERRER,

  /// Always the last value in this enumeration.
  REFERRER_POLICY_LAST_VALUE = REFERRER_POLICY_NO_REFERRER,
} acf_referrer_policy_t;

///
/// Resource type for a request. These constants match their equivalents in
/// Chromium's ResourceType and should not be renumbered.
///
typedef enum {
  ///
  /// Top level page.
  ///
  RT_MAIN_FRAME = 0,

  ///
  /// Frame or iframe.
  ///
  RT_SUB_FRAME,

  ///
  /// CSS stylesheet.
  ///
  RT_STYLESHEET,

  ///
  /// External script.
  ///
  RT_SCRIPT,

  ///
  /// Image (jpg/gif/png/etc).
  ///
  RT_IMAGE,

  ///
  /// Font.
  ///
  RT_FONT_RESOURCE,

  ///
  /// Some other subresource. This is the default type if the actual type is
  /// unknown.
  ///
  RT_SUB_RESOURCE,

  ///
  /// Object (or embed) tag for a plugin, or a resource that a plugin requested.
  ///
  RT_OBJECT,

  ///
  /// Media resource.
  ///
  RT_MEDIA,

  ///
  /// Main resource of a dedicated worker.
  ///
  RT_WORKER,

  ///
  /// Main resource of a shared worker.
  ///
  RT_SHARED_WORKER,

  ///
  /// Explicitly requested prefetch.
  ///
  RT_PREFETCH,

  ///
  /// Favicon.
  ///
  RT_FAVICON,

  ///
  /// XMLHttpRequest.
  ///
  RT_XHR,

  ///
  /// A request for a "<ping>".
  ///
  RT_PING,

  ///
  /// Main resource of a service worker.
  ///
  RT_SERVICE_WORKER,

  ///
  /// A report of Content Security Policy violations.
  ///
  RT_CSP_REPORT,

  ///
  /// A resource that a plugin requested.
  ///
  RT_PLUGIN_RESOURCE,

  ///
  /// A main-frame service worker navigation preload request.
  ///
  RT_NAVIGATION_PRELOAD_MAIN_FRAME = 19,

  ///
  /// A sub-frame service worker navigation preload request.
  ///
  RT_NAVIGATION_PRELOAD_SUB_FRAME,
} acf_resource_type_t;

///
/// Transition type for a request. Made up of one source value and 0 or more
/// qualifiers.
///
typedef enum {
  ///
  /// Source is a link click or the JavaScript window.open function. This is
  /// also the default value for requests like sub-resource loads that are not
  /// navigations.
  ///
  TT_LINK = 0,

  ///
  /// Source is some other "explicit" navigation. This is the default value for
  /// navigations where the actual type is unknown. See also
  /// TT_DIRECT_LOAD_FLAG.
  ///
  TT_EXPLICIT = 1,

  ///
  /// User got to this page through a suggestion in the UI (for example, via the
  /// destinations page). Chrome runtime only.
  ///
  TT_AUTO_BOOKMARK = 2,

  ///
  /// Source is a subframe navigation. This is any content that is automatically
  /// loaded in a non-toplevel frame. For example, if a page consists of several
  /// frames containing ads, those ad URLs will have this transition type.
  /// The user may not even realize the content in these pages is a separate
  /// frame, so may not care about the URL.
  ///
  TT_AUTO_SUBFRAME = 3,

  ///
  /// Source is a subframe navigation explicitly requested by the user that will
  /// generate new navigation entries in the back/forward list. These are
  /// probably more important than frames that were automatically loaded in
  /// the background because the user probably cares about the fact that this
  /// link was loaded.
  ///
  TT_MANUAL_SUBFRAME = 4,

  ///
  /// User got to this page by typing in the URL bar and selecting an entry
  /// that did not look like a URL.  For example, a match might have the URL
  /// of a Google search result page, but appear like "Search Google for ...".
  /// These are not quite the same as EXPLICIT navigations because the user
  /// didn't type or see the destination URL. Chrome runtime only.
  /// See also TT_KEYWORD.
  ///
  TT_GENERATED = 5,

  ///
  /// This is a toplevel navigation. This is any content that is automatically
  /// loaded in a toplevel frame.  For example, opening a tab to show the ASH
  /// screen saver, opening the devtools window, opening the NTP after the safe
  /// browsing warning, opening web-based dialog boxes are examples of
  /// AUTO_TOPLEVEL navigations. Chrome runtime only.
  ///
  TT_AUTO_TOPLEVEL = 6,

  ///
  /// Source is a form submission by the user. NOTE: In some situations
  /// submitting a form does not result in this transition type. This can happen
  /// if the form uses a script to submit the contents.
  ///
  TT_FORM_SUBMIT = 7,

  ///
  /// Source is a "reload" of the page via the Reload function or by re-visiting
  /// the same URL. NOTE: This is distinct from the concept of whether a
  /// particular load uses "reload semantics" (i.e. bypasses cached data).
  ///
  TT_RELOAD = 8,

  ///
  /// The url was generated from a replaceable keyword other than the default
  /// search provider. If the user types a keyword (which also applies to
  /// tab-to-search) in the omnibox this qualifier is applied to the transition
  /// type of the generated url. TemplateURLModel then may generate an
  /// additional visit with a transition type of TT_KEYWORD_GENERATED against
  /// the url 'http://' + keyword. For example, if you do a tab-to-search
  /// against wikipedia the generated url has a transition qualifer of
  /// TT_KEYWORD, and TemplateURLModel generates a visit for 'wikipedia.org'
  /// with a transition type of TT_KEYWORD_GENERATED. Chrome runtime only.
  ///
  TT_KEYWORD = 9,

  ///
  /// Corresponds to a visit generated for a keyword. See description of
  /// TT_KEYWORD for more details. Chrome runtime only.
  ///
  TT_KEYWORD_GENERATED = 10,

  ///
  /// General mask defining the bits used for the source values.
  ///
  TT_SOURCE_MASK = 0xFF,

  /// Qualifiers.
  /// Any of the core values above can be augmented by one or more qualifiers.
  /// These qualifiers further define the transition.

  ///
  /// Attempted to visit a URL but was blocked.
  ///
  TT_BLOCKED_FLAG = 0x00800000,

  ///
  /// Used the Forward or Back function to navigate among browsing history.
  /// Will be ORed to the transition type for the original load.
  ///
  TT_FORWARD_BACK_FLAG = 0x01000000,

  ///
  /// Loaded a URL directly via CreateBrowser, LoadURL or LoadRequest.
  ///
  TT_DIRECT_LOAD_FLAG = 0x02000000,

  ///
  /// User is navigating to the home page. Chrome runtime only.
  ///
  TT_HOME_PAGE_FLAG = 0x04000000,

  ///
  /// The transition originated from an external application; the exact
  /// definition of this is embedder dependent. Chrome runtime and
  /// extension system only.
  ///
  TT_FROM_API_FLAG = 0x08000000,

  ///
  /// The beginning of a navigation chain.
  ///
  TT_CHAIN_START_FLAG = 0x10000000,

  ///
  /// The last transition in a redirect chain.
  ///
  TT_CHAIN_END_FLAG = 0x20000000,

  ///
  /// Redirects caused by JavaScript or a meta refresh tag on the page.
  ///
  TT_CLIENT_REDIRECT_FLAG = 0x40000000,

  ///
  /// Redirects sent from the server by HTTP headers.
  ///
  TT_SERVER_REDIRECT_FLAG = 0x80000000,

  ///
  /// Used to test whether a transition involves a redirect.
  ///
  TT_IS_REDIRECT_MASK = 0xC0000000,

  ///
  /// General mask defining the bits used for the qualifiers.
  ///
  TT_QUALIFIER_MASK = 0xFFFFFF00,
} acf_transition_type_t;

///
/// Post data elements may represent either bytes or files.
///
typedef enum {
  PDE_TYPE_EMPTY = 0,
  PDE_TYPE_BYTES,
  PDE_TYPE_FILE,
} acf_postdataelement_type_t;

///
/// Flags that represent CefURLRequest status.
///
typedef enum {
  ///
  /// Unknown status.
  ///
  UR_UNKNOWN = 0,

  ///
  /// Request succeeded.
  ///
  UR_SUCCESS,

  ///
  /// An IO request is pending, and the caller will be informed when it is
  /// completed.
  ///
  UR_IO_PENDING,

  ///
  /// Request was canceled programatically.
  ///
  UR_CANCELED,

  ///
  /// Request failed for some reason.
  ///
  UR_FAILED,
} acf_urlrequest_status_t;

///
/// Return values for AcfResponseFilter::Filter().
///
typedef enum {
  ///
  /// Some or all of the pre-filter data was read successfully but more data is
  /// needed in order to continue filtering (filtered output is pending).
  ///
  RESPONSE_FILTER_NEED_MORE_DATA,

  ///
  /// Some or all of the pre-filter data was read successfully and all available
  /// filtered output has been written.
  ///
  RESPONSE_FILTER_DONE,

  ///
  /// An error occurred during filtering.
  ///
  RESPONSE_FILTER_ERROR
} acf_response_filter_status_t;

///
/// Key event types.
///
typedef enum {
  ///
  /// Notification that a key transitioned from "up" to "down".
  ///
  KEYEVENT_RAWKEYDOWN = 0,

  ///
  /// Notification that a key was pressed. This does not necessarily correspond
  /// to a character depending on the key and language. Use KEYEVENT_CHAR for
  /// character input.
  ///
  KEYEVENT_KEYDOWN,

  ///
  /// Notification that a key was released.
  ///
  KEYEVENT_KEYUP,

  ///
  /// Notification that a character was typed. Use this for text input. Key
  /// down events may generate 0, 1, or more than one character event depending
  /// on the key, locale, and operating system.
  ///
  KEYEVENT_CHAR
} acf_key_event_type_t;

#endif // ACF_ENUMS_H_