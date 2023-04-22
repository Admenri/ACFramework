// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=651b1f7eb6b2e6c9fa7c95af5234b49dfb29db88$
//

#include "libacf_dll/ctocpp/environment_ctocpp.h"
#include "libacf_dll/cpptoc/browser_handler_cpptoc.h"
#include "libacf_dll/cpptoc/environment_handler_cpptoc.h"
#include "libacf_dll/cpptoc/profile_handler_cpptoc.h"
#include "libacf_dll/ctocpp/browser_ctocpp.h"
#include "libacf_dll/ctocpp/profile_ctocpp.h"

// STATIC METHODS - Body may be edited by hand.

bool AcfEnvironment::InitACFContext() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = acf_environment_init_acfcontext();

  // Return type: bool
  return _retval ? true : false;
}

bool AcfEnvironment::QuitACFContext() {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = acf_environment_quit_acfcontext();

  // Return type: bool
  return _retval ? true : false;
}

AcfRefPtr<AcfEnvironment> AcfEnvironment::CreateEnvironment(
    const AcfString& browser_path,
    const AcfEnvironmentSettings& settings,
    AcfRefPtr<AcfEnvironmentHandler> handler) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser_path; type: string_byref_const
  if (browser_path.empty())
    return nullptr;
  // Unverified params: handler

  // Execute
  acf_environment_t* _retval =
      acf_environment_create(browser_path.GetStruct(), &settings,
                             AcfEnvironmentHandlerCppToC::Wrap(handler));

  // Return type: refptr_same
  return AcfEnvironmentCToCpp::Wrap(_retval);
}

// VIRTUAL METHODS - Body may be edited by hand.

bool AcfEnvironmentCToCpp::IsSame(AcfRefPtr<AcfEnvironment> that) {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, is_same))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: that; type: refptr_same
  if (!that.get())
    return false;

  // Execute
  int _retval = _struct->is_same(_struct, AcfEnvironmentCToCpp::Unwrap(that));

  // Return type: bool
  return _retval ? true : false;
}

bool AcfEnvironmentCToCpp::IsValid() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, is_valid))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_valid(_struct);

  // Return type: bool
  return _retval ? true : false;
}

AcfRefPtr<AcfEnvironmentHandler> AcfEnvironmentCToCpp::GetHandler() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_handler))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_environment_handler_t* _retval = _struct->get_handler(_struct);

  // Return type: refptr_diff
  return AcfEnvironmentHandlerCppToC::Unwrap(_retval);
}

AcfString AcfEnvironmentCToCpp::GetBrowserVersion() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_browser_version))
    return AcfString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_string_userfree_t _retval = _struct->get_browser_version(_struct);

  // Return type: string
  AcfString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

uint32 AcfEnvironmentCToCpp::GetProcessPID() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_process_pid))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  uint32 _retval = _struct->get_process_pid(_struct);

  // Return type: simple
  return _retval;
}

int AcfEnvironmentCToCpp::Terminate() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, terminate))
    return 0;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->terminate(_struct);

  // Return type: simple
  return _retval;
}

AcfRefPtr<AcfProfile> AcfEnvironmentCToCpp::GetDefaultProfile() {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_default_profile))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_profile_t* _retval = _struct->get_default_profile(_struct);

  // Return type: refptr_same
  return AcfProfileCToCpp::Wrap(_retval);
}

AcfRefPtr<AcfProfile> AcfEnvironmentCToCpp::CreateProfile(
    const AcfString& path,
    AcfRefPtr<AcfProfileHandler> handler) {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, create_profile))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: path; type: string_byref_const
  if (path.empty())
    return nullptr;
  // Unverified params: handler

  // Execute
  acf_profile_t* _retval = _struct->create_profile(
      _struct, path.GetStruct(), AcfProfileHandlerCppToC::Wrap(handler));

  // Return type: refptr_same
  return AcfProfileCToCpp::Wrap(_retval);
}

AcfRefPtr<AcfBrowser> AcfEnvironmentCToCpp::CreateBrowser(
    AcfRefPtr<AcfProfile> profile,
    AcfRefPtr<AcfBrowserHandler> handler,
    const AcfBrowserCreateParams& params,
    AcfUserData user_data) {
  acf_environment_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, create_browser))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: profile, handler

  // Execute
  acf_browser_t* _retval = _struct->create_browser(
      _struct, AcfProfileCToCpp::Unwrap(profile),
      AcfBrowserHandlerCppToC::Wrap(handler), &params, user_data);

  // Return type: refptr_same
  return AcfBrowserCToCpp::Wrap(_retval);
}

// CONSTRUCTOR - Do not edit by hand.

AcfEnvironmentCToCpp::AcfEnvironmentCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfEnvironmentCToCpp::~AcfEnvironmentCToCpp() {}

template <>
acf_environment_t*
AcfCToCppRefCounted<AcfEnvironmentCToCpp, AcfEnvironment, acf_environment_t>::
    UnwrapDerived(AcfWrapperType type, AcfEnvironment* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfEnvironmentCToCpp,
                                   AcfEnvironment,
                                   acf_environment_t>::kWrapperType =
    WT_ENVIRONMENT;
