// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=97674700bae9475ebac5c25c3516f47d7534a2a5$
//

#include "libacf_dll/cpptoc/resource_read_callback_cpptoc.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

void ACF_CALLBACK
resource_read_callback_cont(struct _acf_resource_read_callback_t* self,
                            int bytes_read) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;

  // Execute
  AcfResourceReadCallbackCppToC::Get(self)->Continue(bytes_read);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfResourceReadCallbackCppToC::AcfResourceReadCallbackCppToC() {
  GetStruct()->cont = resource_read_callback_cont;
}

// DESTRUCTOR - Do not edit by hand.

AcfResourceReadCallbackCppToC::~AcfResourceReadCallbackCppToC() {}

template <>
AcfRefPtr<AcfResourceReadCallback> AcfCppToCRefCounted<
    AcfResourceReadCallbackCppToC,
    AcfResourceReadCallback,
    acf_resource_read_callback_t>::UnwrapDerived(AcfWrapperType type,
                                                 acf_resource_read_callback_t*
                                                     s) {
  return nullptr;
}

template <>
AcfWrapperType AcfCppToCRefCounted<AcfResourceReadCallbackCppToC,
                                   AcfResourceReadCallback,
                                   acf_resource_read_callback_t>::kWrapperType =
    WT_RESOURCE_READ_CALLBACK;