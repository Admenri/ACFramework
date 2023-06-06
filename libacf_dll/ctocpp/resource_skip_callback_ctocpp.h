// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=a175fa1eade7c3a4b9a4adc3b673bbc791f19c64$
//

#ifndef ACF_CTOCPP_RESOURCE_SKIP_CALLBACK_CTOCPP_H_
#define ACF_CTOCPP_RESOURCE_SKIP_CALLBACK_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_frame.h"
#include "include/acf_resource_request_handler.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_frame_capi.h"
#include "include/capi/acf_resource_request_handler_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfResourceSkipCallbackCToCpp
    : public AcfCToCppRefCounted<AcfResourceSkipCallbackCToCpp,
                                 AcfResourceSkipCallback,
                                 acf_resource_skip_callback_t> {
 public:
  AcfResourceSkipCallbackCToCpp();
  virtual ~AcfResourceSkipCallbackCToCpp();

  // AcfResourceSkipCallback methods.
  void Continue(int64 bytes_skipped) override;
};

#endif  // ACF_CTOCPP_RESOURCE_SKIP_CALLBACK_CTOCPP_H_