// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=ea15a5639678b2e30fda6500ae97d5e95d7a7bce$
//

#ifndef ACF_CPPTOC_RESOURCE_READ_CALLBACK_CPPTOC_H_
#define ACF_CPPTOC_RESOURCE_READ_CALLBACK_CPPTOC_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_frame.h"
#include "include/acf_resource_request_handler.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_frame_capi.h"
#include "include/capi/acf_resource_request_handler_capi.h"
#include "libacf_dll/cpptoc/cpptoc_ref_counted.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class AcfResourceReadCallbackCppToC
    : public AcfCppToCRefCounted<AcfResourceReadCallbackCppToC,
                                 AcfResourceReadCallback,
                                 acf_resource_read_callback_t> {
 public:
  AcfResourceReadCallbackCppToC();
  virtual ~AcfResourceReadCallbackCppToC();
};

#endif  // ACF_CPPTOC_RESOURCE_READ_CALLBACK_CPPTOC_H_
