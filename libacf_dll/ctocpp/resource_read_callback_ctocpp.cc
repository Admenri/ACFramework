// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=fe4743a428a6ca188e5ddb0d77fbed958d32c31c$
//

#include "libacf_dll/ctocpp/resource_read_callback_ctocpp.h"

// VIRTUAL METHODS - Body may be edited by hand.

void AcfResourceReadCallbackCToCpp::Continue(int bytes_read) {
  acf_resource_read_callback_t* _struct = GetStruct();
  if (ACF_MEMBER_MISSING(_struct, cont))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  _struct->cont(_struct, bytes_read);
}

// CONSTRUCTOR - Do not edit by hand.

AcfResourceReadCallbackCToCpp::AcfResourceReadCallbackCToCpp() {}

// DESTRUCTOR - Do not edit by hand.

AcfResourceReadCallbackCToCpp::~AcfResourceReadCallbackCToCpp() {}

template <>
acf_resource_read_callback_t* AcfCToCppRefCounted<
    AcfResourceReadCallbackCToCpp,
    AcfResourceReadCallback,
    acf_resource_read_callback_t>::UnwrapDerived(AcfWrapperType type,
                                                 AcfResourceReadCallback* c) {
  return nullptr;
}

template <>
AcfWrapperType AcfCToCppRefCounted<AcfResourceReadCallbackCToCpp,
                                   AcfResourceReadCallback,
                                   acf_resource_read_callback_t>::kWrapperType =
    WT_RESOURCE_READ_CALLBACK;