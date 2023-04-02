// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=6b9da1f61263a6e7c1c81f7a681d755a94030dc1$
//

#ifndef ACF_CPPTOC_BINARY_VALUE_CPPTOC_H_
#define ACF_CPPTOC_BINARY_VALUE_CPPTOC_H_
#pragma once

#include "include/acf_values.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/cpptoc/cpptoc_ref_counted.h"

// Wrap a C++ class with a C structure.
// This class may be instantiated and accessed DLL-side only.
class AcfBinaryValueCppToC : public AcfCppToCRefCounted<AcfBinaryValueCppToC,
                                                        AcfBinaryValue,
                                                        acf_binary_value_t> {
 public:
  AcfBinaryValueCppToC();
  virtual ~AcfBinaryValueCppToC();
};

#endif  // ACF_CPPTOC_BINARY_VALUE_CPPTOC_H_
