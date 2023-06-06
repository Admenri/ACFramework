// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=a3587a4d58a34d5f5c6354058c3f5427c1f456a2$
//

#ifndef ACF_CTOCPP_POST_DATA_CTOCPP_H_
#define ACF_CTOCPP_POST_DATA_CTOCPP_H_
#pragma once

#include "include/acf_request.h"
#include "include/capi/acf_request_capi.h"
#include "libacf_dll/ctocpp/ctocpp_ref_counted.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class AcfPostDataCToCpp : public AcfCToCppRefCounted<AcfPostDataCToCpp,
                                                     AcfPostData,
                                                     acf_post_data_t> {
 public:
  AcfPostDataCToCpp();
  virtual ~AcfPostDataCToCpp();

  // AcfPostData methods.
  bool IsReadOnly() override;
  bool HasExcludedElements() override;
  size_t GetElementCount() override;
  void GetElements(ElementVector& elements) override;
  bool RemoveElement(AcfRefPtr<AcfPostDataElement> element) override;
  bool AddElement(AcfRefPtr<AcfPostDataElement> element) override;
  void RemoveElements() override;
};

#endif  // ACF_CTOCPP_POST_DATA_CTOCPP_H_
