// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=98357cea7c80cfe0cc53219e98a57d3600fc6961$
//

#include "libacf_dll/ctocpp/profile_ctocpp.h"
#include "libacf_dll/cpptoc/complete_handler_cpptoc.h"
#include "libacf_dll/cpptoc/profile_handler_cpptoc.h"
#include "libacf_dll/ctocpp/cookie_ctocpp.h"
#include "libacf_dll/ctocpp/cookie_manager_ctocpp.h"
#include "libacf_dll/ctocpp/environment_ctocpp.h"
#include "libacf_dll/ctocpp/value_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

AcfRefPtr<AcfProfileHandler> AcfProfileCToCpp::GetHandler() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_handler))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_profile_handler_t* _retval = _struct->get_handler(_struct);

  // Return type: refptr_diff
  return AcfProfileHandlerCppToC::Unwrap(_retval);
}

AcfRefPtr<AcfEnvironment> AcfProfileCToCpp::GetEnvironment() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_environment))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_environment_t* _retval = _struct->get_environment(_struct);

  // Return type: refptr_same
  return AcfEnvironmentCToCpp::Wrap(_retval);
}

bool AcfProfileCToCpp::IsValid() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, is_valid))
    return false;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = _struct->is_valid(_struct);

  // Return type: bool
  return _retval ? true : false;
}

AcfString AcfProfileCToCpp::GetPath() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_path))
    return AcfString();

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_string_userfree_t _retval = _struct->get_path(_struct);

  // Return type: string
  AcfString _retvalStr;
  _retvalStr.AttachToUserFree(_retval);
  return _retvalStr;
}

void AcfProfileCToCpp::SetPreference(const AcfString& name,
                                     AcfRefPtr<AcfValue> value,
                                     AcfRefPtr<AcfCompleteHandler> handler) {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, set_preference))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  if (name.empty())
    return;
  // Unverified params: value, handler

  // Execute
  _struct->set_preference(_struct, name.GetStruct(),
                          AcfValueCToCpp::Unwrap(value),
                          AcfCompleteHandlerCppToC::Wrap(handler));
}

void AcfProfileCToCpp::RemoveBrowsingData(
    RemoveDataType data_type,
    bool no_checks,
    AcfRefPtr<AcfCompleteHandler> handler) {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, remove_browsing_data))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: handler

  // Execute
  _struct->remove_browsing_data(_struct, data_type, no_checks,
                                AcfCompleteHandlerCppToC::Wrap(handler));
}

AcfRefPtr<AcfCookieManager> AcfProfileCToCpp::GetCookieManager() {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, get_cookie_manager))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  acf_cookie_manager_t* _retval = _struct->get_cookie_manager(_struct);

  // Return type: refptr_same
  return AcfCookieManagerCToCpp::Wrap(_retval);
}

AcfRefPtr<AcfCookie> AcfProfileCToCpp::CreateCookie(const AcfString& name,
                                                    const AcfString& value,
                                                    const AcfString& domain,
                                                    const AcfString& path) {
  acf_profile_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, create_cookie))
    return nullptr;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  if (name.empty())
    return nullptr;
  // Verify param: value; type: string_byref_const
  if (value.empty())
    return nullptr;
  // Verify param: domain; type: string_byref_const
  if (domain.empty())
    return nullptr;
  // Verify param: path; type: string_byref_const
  if (path.empty())
    return nullptr;

  // Execute
  acf_cookie_t* _retval =
      _struct->create_cookie(_struct, name.GetStruct(), value.GetStruct(),
                             domain.GetStruct(), path.GetStruct());

  // Return type: refptr_same
  return AcfCookieCToCpp::Wrap(_retval);
}

// CONSTRUCTOR - Do not edit by hand.

AcfProfileCToCpp::AcfProfileCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfProfileCToCpp::~AcfProfileCToCpp() {}

template <>
acf_profile_t*
AcfCToCppRefCounted<AcfProfileCToCpp, AcfProfile, acf_profile_t>::UnwrapDerived(
    AcfWrapperType type,
    AcfProfile* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfProfileCToCpp,
                                   AcfProfile,
                                   acf_profile_t>::kWrapperType = WT_PROFILE;
