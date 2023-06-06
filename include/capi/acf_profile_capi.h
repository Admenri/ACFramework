// Copyright (c) 2023 Admenri. All rights reserved.
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//
// $hash=9b0bd507c304aa99b18ef003160f4a3516873a4a$
//

#ifndef ACF_INCLUDE_CAPI_ACF_PROFILE_CAPI_H_
#define ACF_INCLUDE_CAPI_ACF_PROFILE_CAPI_H_
#pragma once

#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_values_capi.h"
#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_string.h"
#include "include/internal/acf_types.h"
#include "include/internal/acf_types_wrappers.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _acf_complete_handler_t;
struct _acf_cookie_manager_t;
struct _acf_cookie_t;
struct _acf_cookie_visitor_t;
struct _acf_cookies_getter_t;
struct _acf_environment_t;
struct _acf_profile_t;
struct _acf_value_t;

///
/// ACF's profile object for create browser in environment. In chromium, it is
/// user profile
///
typedef struct _acf_profile_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Get host environment object
  ///
  struct _acf_environment_t*(ACF_CALLBACK* get_environment)(
      struct _acf_profile_t* self);

  ///
  /// Get object remote state
  ///
  int(ACF_CALLBACK* is_valid)(struct _acf_profile_t* self);

  ///
  /// Is same object
  ///
  int(ACF_CALLBACK* is_same)(struct _acf_profile_t* self,
                             struct _acf_profile_t* that);

  ///
  /// Get profile storage path
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_path)(struct _acf_profile_t* self);

  ///
  /// Set the |value| associated with preference |name|.
  ///
  void(ACF_CALLBACK* set_preference)(struct _acf_profile_t* self,
                                     const acf_string_t* name,
                                     struct _acf_value_t* value,
                                     struct _acf_complete_handler_t* handler);

  ///
  /// Remove browsing data when running profile, when completed it will call
  /// OnProfileRemoveDataCompleted
  ///
  void(ACF_CALLBACK* remove_browsing_data)(
      struct _acf_profile_t* self,
      acf_remove_data_type_t data_type,
      int no_checks,
      struct _acf_complete_handler_t* handler);

  ///
  /// Get cookie manager for current profile
  ///
  struct _acf_cookie_manager_t*(ACF_CALLBACK* get_cookie_manager)(
      struct _acf_profile_t* self);
} acf_profile_t;

///
/// Cookie data storage
///
typedef struct _acf_cookie_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Get cookie name
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_name)(struct _acf_cookie_t* self);

  ///
  /// Set cookie name
  ///
  void(ACF_CALLBACK* set_name)(struct _acf_cookie_t* self,
                               const acf_string_t* value);

  ///
  /// Get cookie value
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_value)(struct _acf_cookie_t* self);

  ///
  /// Set cookie value
  ///
  void(ACF_CALLBACK* set_value)(struct _acf_cookie_t* self,
                                const acf_string_t* value);

  ///
  /// Get cookie domain
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_domain)(struct _acf_cookie_t* self);

  ///
  /// Set cookie domain
  ///
  void(ACF_CALLBACK* set_domain)(struct _acf_cookie_t* self,
                                 const acf_string_t* value);

  ///
  /// Get cookie path
  ///
  // The resulting string must be freed by calling acf_string_userfree_free().
  acf_string_userfree_t(ACF_CALLBACK* get_path)(struct _acf_cookie_t* self);

  ///
  /// Set cookie path
  ///
  void(ACF_CALLBACK* set_path)(struct _acf_cookie_t* self,
                               const acf_string_t* value);

  ///
  /// Is cookie httponly
  ///
  int(ACF_CALLBACK* is_httponly)(struct _acf_cookie_t* self);

  ///
  /// Set cookie httponly
  ///
  void(ACF_CALLBACK* set_httponly)(struct _acf_cookie_t* self, int value);

  ///
  /// Is cookie secure
  ///
  int(ACF_CALLBACK* is_secure)(struct _acf_cookie_t* self);

  ///
  /// Set cookie secure
  ///
  void(ACF_CALLBACK* set_secure)(struct _acf_cookie_t* self, int value);

  ///
  /// Get same site infomation
  ///
  acf_cookie_same_site_t(ACF_CALLBACK* get_same_site)(
      struct _acf_cookie_t* self);

  ///
  /// Set same site infomation
  ///
  void(ACF_CALLBACK* set_same_site)(struct _acf_cookie_t* self,
                                    acf_cookie_same_site_t value);

  ///
  /// Get priority
  ///
  acf_cookie_priority_t(ACF_CALLBACK* get_priority)(struct _acf_cookie_t* self);

  ///
  /// Set priority
  ///
  void(ACF_CALLBACK* set_priority)(struct _acf_cookie_t* self,
                                   acf_cookie_priority_t value);

  ///
  /// Get create time
  ///
  double(ACF_CALLBACK* get_creation)(struct _acf_cookie_t* self);

  ///
  /// Set create time
  ///
  void(ACF_CALLBACK* set_creation)(struct _acf_cookie_t* self, double value);

  ///
  /// Get expiry time
  ///
  double(ACF_CALLBACK* get_expiry)(struct _acf_cookie_t* self);

  ///
  /// Set expiry time
  ///
  void(ACF_CALLBACK* set_expiry)(struct _acf_cookie_t* self, double value);

  ///
  /// Get last access time
  ///
  double(ACF_CALLBACK* get_last_access)(struct _acf_cookie_t* self);

  ///
  /// Set last access time
  ///
  void(ACF_CALLBACK* set_last_access)(struct _acf_cookie_t* self, double value);

  ///
  /// Get last update time
  ///
  double(ACF_CALLBACK* get_last_update)(struct _acf_cookie_t* self);

  ///
  /// Set last update time
  ///
  void(ACF_CALLBACK* set_last_update)(struct _acf_cookie_t* self, double value);
} acf_cookie_t;

///
/// Cookie getter
///
typedef struct _acf_cookies_getter_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Get count
  ///
  size_t(ACF_CALLBACK* get_cookies_count)(struct _acf_cookies_getter_t* self);

  ///
  /// Get cookie data
  ///
  struct _acf_cookie_t*(ACF_CALLBACK* get_cookie_at)(
      struct _acf_cookies_getter_t* self,
      size_t index);
} acf_cookies_getter_t;

///
/// Cookie visitor
///
typedef struct _acf_cookie_visitor_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Called when completed.
  ///
  void(ACF_CALLBACK* visit)(struct _acf_cookie_visitor_t* self,
                            struct _acf_cookies_getter_t* cookie_getter);
} acf_cookie_visitor_t;

///
/// Structure used for managing cookies. The functions of this structure may be
/// called on any thread unless otherwise indicated.
///
typedef struct _acf_cookie_manager_t {
  ///
  /// Base structure.
  ///
  acf_base_ref_counted_t base;

  ///
  /// Get hosted profile object
  ///
  struct _acf_profile_t*(ACF_CALLBACK* get_profile)(
      struct _acf_cookie_manager_t* self);

  ///
  /// Visit cookies on the current thread. The returned cookies are ordered by
  /// longest path, then by earliest creation date. Returns false (0) if cookies
  /// cannot be accessed.
  ///
  void(ACF_CALLBACK* get_cookies)(struct _acf_cookie_manager_t* self,
                                  const acf_string_t* url,
                                  int includeHttpOnly,
                                  struct _acf_cookie_visitor_t* visitor);

  ///
  /// Sets a cookie given a valid URL and explicit user-provided cookie
  /// attributes. This function expects each attribute to be well-formed. It
  /// will check for disallowed characters (e.g. the ';' character is disallowed
  /// within the cookie value attribute) and fail without setting the cookie if
  /// such characters are found. If |callback| is non-NULL it will be executed
  /// asnychronously on the UI thread after the cookie has been set. Returns
  /// false (0) if an invalid URL is specified or if cookies cannot be accessed.
  ///
  void(ACF_CALLBACK* set_cookie)(struct _acf_cookie_manager_t* self,
                                 const acf_string_t* url,
                                 struct _acf_cookie_t* cookie,
                                 struct _acf_complete_handler_t* callback);

  ///
  /// Delete all cookies that match the specified parameters. If both |url| and
  /// |cookie_name| values are specified all host and domain cookies matching
  /// both will be deleted. If only |url| is specified all host cookies (but not
  /// domain cookies) irrespective of path will be deleted. If |url| is NULL all
  /// cookies for all hosts and domains will be deleted. If |callback| is non-
  /// NULL it will be executed asnychronously on the UI thread after the cookies
  /// have been deleted. Returns false (0) if a non-NULL invalid URL is
  /// specified or if cookies cannot be accessed. Cookies can alternately be
  /// deleted using the Visit*Cookies() functions.
  ///
  void(ACF_CALLBACK* delete_cookies)(
      struct _acf_cookie_manager_t* self,
      const acf_string_t* url,
      const acf_string_t* cookie_name,
      struct _acf_number_complete_handler_t* callback);

  ///
  /// Flush the backing store (if any) to disk. If |callback| is non-NULL it
  /// will be executed asnychronously on the UI thread after the flush is
  /// complete. Returns false (0) if cookies cannot be accessed.
  ///
  void(ACF_CALLBACK* flush_store)(struct _acf_cookie_manager_t* self,
                                  struct _acf_complete_handler_t* callback);
} acf_cookie_manager_t;

#ifdef __cplusplus
}
#endif

#endif  // ACF_INCLUDE_CAPI_ACF_PROFILE_CAPI_H_
