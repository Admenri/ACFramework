// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=b7cef7bbe73ce74f0b395b1aec713a7d3f802a5a$
//

#include "libacf_dll/ctocpp/complete_value_handler_ctocpp.h"
#include "libacf_dll/cpptoc/value_cpptoc.h"

// VIRTUAL METHODS - Body may be edited by hand.

void AcfCompleteValueHandlerCToCpp::OnComplete(AcfRefPtr<AcfValue> value) {
  acf_complete_value_handler_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, on_complete))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: value

  // Execute
  _struct->on_complete(_struct, AcfValueCppToC::Wrap(value));
}

// CONSTRUCTOR - Do not edit by hand.

AcfCompleteValueHandlerCToCpp::AcfCompleteValueHandlerCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfCompleteValueHandlerCToCpp::~AcfCompleteValueHandlerCToCpp() {}

template <>
acf_complete_value_handler_t* AcfCToCppRefCounted<
    AcfCompleteValueHandlerCToCpp,
    AcfCompleteValueHandler,
    acf_complete_value_handler_t>::UnwrapDerived(AcfWrapperType type,
                                                 AcfCompleteValueHandler* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfCompleteValueHandlerCToCpp,
                                   AcfCompleteValueHandler,
                                   acf_complete_value_handler_t>::kWrapperType =
    WT_COMPLETE_VALUE_HANDLER;
