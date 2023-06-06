// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=a26a115345a3498b5e586ce793e8de9a01bff099$
//

#include "libacf_dll/ctocpp/resource_skip_callback_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

void AcfResourceSkipCallbackCToCpp::Continue(int64 bytes_skipped) {
  acf_resource_skip_callback_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, cont))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->cont(_struct, bytes_skipped);
}

// CONSTRUCTOR - Do not edit by hand.

AcfResourceSkipCallbackCToCpp::AcfResourceSkipCallbackCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfResourceSkipCallbackCToCpp::~AcfResourceSkipCallbackCToCpp() {}

template <>
acf_resource_skip_callback_t* AcfCToCppRefCounted<
    AcfResourceSkipCallbackCToCpp,
    AcfResourceSkipCallback,
    acf_resource_skip_callback_t>::UnwrapDerived(AcfWrapperType type,
                                                 AcfResourceSkipCallback* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfResourceSkipCallbackCToCpp,
                                   AcfResourceSkipCallback,
                                   acf_resource_skip_callback_t>::kWrapperType =
    WT_RESOURCE_SKIP_CALLBACK;