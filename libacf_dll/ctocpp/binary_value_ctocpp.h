// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=7271209b42f088e62ea193a899eae6e52640062f$
//

#ifndef ACF_CTOCPP_BINARY_VALUE_CTOCPP_H_
#define ACF_CTOCPP_BINARY_VALUE_CTOCPP_H_
#pragma once

#include "include/acf_values.h"
#include "include/capi/acf_values_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfBinaryValueCToCpp : public AcfCToCppRefCounted<AcfBinaryValueCToCpp,
                                                        AcfBinaryValue,
                                                        acf_binary_value_t> {
 public:
  AcfBinaryValueCToCpp();
  virtual ~AcfBinaryValueCToCpp();

  // AcfBinaryValue methods.
  bool IsValid() override;
  bool IsOwned() override;
  bool IsSame(AcfRefPtr<AcfBinaryValue> that) override;
  bool IsEqual(AcfRefPtr<AcfBinaryValue> that) override;
  AcfRefPtr<AcfBinaryValue> Copy() override;
  size_t GetSize() override;
  size_t GetData(void* buffer, size_t buffer_size, size_t data_offset) override;
};

#endif  // ACF_CTOCPP_BINARY_VALUE_CTOCPP_H_