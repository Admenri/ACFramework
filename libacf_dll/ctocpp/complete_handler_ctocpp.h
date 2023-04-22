// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=60751e602b1b071baceb0fe003fa9057a9155215$
//

#ifndef ACF_CTOCPP_COMPLETE_HANDLER_CTOCPP_H_
#define ACF_CTOCPP_COMPLETE_HANDLER_CTOCPP_H_
#pragma once

#include "include/acf_callback.h"
#include "include/acf_values.h"
#include "include/capi/acf_callback_capi.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class AcfCompleteHandlerCToCpp
    : public AcfCToCppRefCounted<AcfCompleteHandlerCToCpp,
                                 AcfCompleteHandler,
                                 acf_complete_handler_t> {
 public:
  AcfCompleteHandlerCToCpp();
  virtual ~AcfCompleteHandlerCToCpp();

  // AcfCompleteHandler methods.
  void OnComplete(bool success) override;
};

#endif  // ACF_CTOCPP_COMPLETE_HANDLER_CTOCPP_H_
