// Copyright (c) 2023 Admenri. All rights reserved.
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=8ddab34f038e17f0953b29c2b42eb8044eabdfee$
//

#ifndef ACF_INCLUDE_CAPI_ACF_BROWSER_CAPI_H_
#define ACF_INCLUDE_CAPI_ACF_BROWSER_CAPI_H_
#pragma once

#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_frame_capi.h"
#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_string_list.h"
#include "include/internal/acf_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _acf_browser_t;
struct _acf_environment_t;
struct _acf_frame_t;
struct _acf_new_window_delegate_t;
struct _acf_profile_t;

///
/// Browser event list handler model
///
typedef struct _acf_browser_handler_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Called when browser has been initialized from environment.
  ///
  void(ACF_CALLBACK* on_browser_created)(struct _acf_browser_handler_t* self,
                                         struct _acf_browser_t* browser);

  ///
  /// The browser will open a new Browser as NewWindow
  ///
  void(ACF_CALLBACK* on_new_window_request)(
      struct _acf_browser_handler_t* self,
      struct _acf_browser_t* browser,
      acf_new_window_source_t source,
      acf_new_window_disposition_t disposition,
      int user_gesture,
      struct _acf_new_window_delegate_t* delegate);

  ///
  /// When the browser was sured to be destroyed, the browser will call this
  /// event.
  ///
  void(ACF_CALLBACK* on_browser_destroyed)(struct _acf_browser_handler_t* self,
                                           struct _acf_browser_t* browser);

  ///
  /// Loading state changed (async)
  ///
  void(ACF_CALLBACK* on_loading_state_changed)(
      struct _acf_browser_handler_t* self,
      struct _acf_browser_t* browser,
      int show_loading_ui);

  ///
  /// Navigation state changed (title url icon historical)
  ///
  void(ACF_CALLBACK* on_navigation_state_changed)(
      struct _acf_browser_handler_t* self,
      struct _acf_browser_t* browser,
      acf_navigation_types_t flags);

  ///
  /// Title bar info changed
  ///
  void(ACF_CALLBACK* on_title_changed)(struct _acf_browser_handler_t* self,
                                       struct _acf_browser_t* browser,
                                       const acf_string_t* title);

  ///
  /// Address bar info changed
  ///
  void(ACF_CALLBACK* on_address_changed)(struct _acf_browser_handler_t* self,
                                         struct _acf_browser_t* browser,
                                         const acf_string_t* address);

  ///
  /// notify fullscreen state changed
  ///
  void(ACF_CALLBACK* on_fullscreen_state_changed)(
      struct _acf_browser_handler_t* self,
      struct _acf_browser_t* browser,
      int fullscreen);
} acf_browser_handler_t;

///
/// ACF's browser object host, in fact a browser was a window in chromium with
/// tabs control.
///
typedef struct _acf_browser_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Is same object
  ///
  int(ACF_CALLBACK* is_same)(struct _acf_browser_t* self,
                             struct _acf_browser_t* that);

  ///
  /// Get browser event handler
  ///
  struct _acf_browser_handler_t*(ACF_CALLBACK* get_handler)(
      struct _acf_browser_t* self);

  ///
  /// Get browser create's sign.
  ///
  acf_user_data_t(ACF_CALLBACK* get_user_data)(struct _acf_browser_t* self);

  ///
  /// Get parent environment
  ///
  struct _acf_environment_t*(ACF_CALLBACK* get_environment)(
      struct _acf_browser_t* self);

  ///
  /// Close browser, it will call browser close event (or unlaod dialog)
  ///
  void(ACF_CALLBACK* close)(struct _acf_browser_t* self, int force);

  ///
  /// Get browser window handle
  ///
  acf_window_handle_t(ACF_CALLBACK* get_window_handle)(
      struct _acf_browser_t* self);

  ///
  /// Get delegate status
  ///
  int(ACF_CALLBACK* is_valid)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: can go back
  ///
  int(ACF_CALLBACK* can_go_back)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: can go forward
  ///
  int(ACF_CALLBACK* can_go_forward)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: go back
  ///
  void(ACF_CALLBACK* go_back)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: go forward
  ///
  void(ACF_CALLBACK* go_forward)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: reload
  ///
  void(ACF_CALLBACK* reload)(struct _acf_browser_t* self, int ignore_cache);

  ///
  /// Browser navigation entry controller: stop loading
  ///
  void(ACF_CALLBACK* stop)(struct _acf_browser_t* self);

  ///
  /// Browser navigation entry controller: loading
  ///
  int(ACF_CALLBACK* is_loading)(struct _acf_browser_t* self);

  ///
  /// Navigate to target url (Main frame)
  ///
  void(ACF_CALLBACK* load_url)(struct _acf_browser_t* self,
                               const acf_string_t* url);

  ///
  /// Get current url
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_url)(struct _acf_browser_t* self);

  ///
  /// Get title
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_title)(struct _acf_browser_t* self);

  ///
  /// Focus to native widget
  ///
  void(ACF_CALLBACK* focus)(struct _acf_browser_t* self);

  ///
  /// Set/Get window visible
  ///
  void(ACF_CALLBACK* set_visible)(struct _acf_browser_t* self, int visible);

  ///
  /// Get visibility
  ///
  int(ACF_CALLBACK* get_visible)(struct _acf_browser_t* self);

  ///
  /// Get profile object, maybe null
  ///
  struct _acf_profile_t*(ACF_CALLBACK* get_profile)(
      struct _acf_browser_t* self);

  ///
  /// Returns the number of frames that currently exist.
  ///
  size_t(ACF_CALLBACK* get_frame_count)(struct _acf_browser_t* self);

  ///
  /// Returns the identifiers of all existing frames.
  ///
  void(ACF_CALLBACK* get_frame_identifiers)(struct _acf_browser_t* self,
                                            size_t* identifiersCount,
                                            int64* identifiers);

  ///
  /// Returns the names of all existing frames.
  ///
  void(ACF_CALLBACK* get_frame_names)(struct _acf_browser_t* self,
                                      acf_string_list_t names);

  ///
  /// Returns the frame with the specified identifier, or NULL if not found.
  ///
  struct _acf_frame_t*(ACF_CALLBACK* get_frame_byident)(
      struct _acf_browser_t* self,
      int64 identifier);

  ///
  /// Returns the frame with the specified name, or NULL if not found.
  ///
  struct _acf_frame_t*(ACF_CALLBACK* get_frame)(struct _acf_browser_t* self,
                                                const acf_string_t* name);
} acf_browser_t;

///
/// New Window delegate, set a new browser to host target page. Request will be
/// handled while object was destroyed without handled.
///
typedef struct _acf_new_window_delegate_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Set a browser to handle the new window new browser's profile must suit the
  /// host browser's profile, otherwise return false (0).
  ///
  int(ACF_CALLBACK* set_new_browser)(struct _acf_new_window_delegate_t* self,
                                     struct _acf_browser_t* browser);

  ///
  /// Get target url
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_target_url)(
      struct _acf_new_window_delegate_t* self);

  ///
  /// Put if user has been handled the request. This function will send the
  /// final request to browser.
  ///
  void(ACF_CALLBACK* handle_request)(struct _acf_new_window_delegate_t* self,
                                     int handled);
} acf_new_window_delegate_t;

#ifdef __cplusplus
}
#endif

#endif  // ACF_INCLUDE_CAPI_ACF_BROWSER_CAPI_H_
