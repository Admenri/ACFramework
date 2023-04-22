// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=c12fa36ccb04cf317a38ae3ebb0e0203cc7a6a01$
//

#ifndef ACF_CTOCPP_COOKIE_MANAGER_CTOCPP_H_
#define ACF_CTOCPP_COOKIE_MANAGER_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_environment.h"
#include "include/acf_profile.h"
#include "include/acf_values.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_environment_capi.h"
#include "include/capi/acf_profile_capi.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfCookieManagerCToCpp
    : public AcfCToCppRefCounted<AcfCookieManagerCToCpp,
                                 AcfCookieManager,
                                 acf_cookie_manager_t> {
 public:
  AcfCookieManagerCToCpp();
  virtual ~AcfCookieManagerCToCpp();

  // AcfCookieManager methods.
  void GetCookies(const AcfString& url,
                  bool includeHttpOnly,
                  AcfRefPtr<AcfCookieVisitor> visitor) override;
  void SetCookie(const AcfString& url,
                 AcfRefPtr<AcfCookie> cookie,
                 AcfRefPtr<AcfCompleteHandler> callback) override;
  void DeleteCookies(const AcfString& url,
                     const AcfString& cookie_name,
                     AcfRefPtr<AcfNumberCompleteHandler> callback) override;
  void FlushStore(AcfRefPtr<AcfCompleteHandler> callback) override;
};

#endif  // ACF_CTOCPP_COOKIE_MANAGER_CTOCPP_H_
