// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=6fa1c6bf34102798ace6cd39b1be144e78a9ba7d$
//

#include "libacf_dll/cpptoc/post_data_cpptoc.h"
#include <algorithm>
#include "libacf_dll/cpptoc/post_data_element_cpptoc.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int ACF_CALLBACK post_data_is_read_only(struct _acf_post_data_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfPostDataCppToC::Get(self)->IsReadOnly();

  // Return type: bool
  return _retval;
}

int ACF_CALLBACK
post_data_has_excluded_elements(struct _acf_post_data_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfPostDataCppToC::Get(self)->HasExcludedElements();

  // Return type: bool
  return _retval;
}

size_t ACF_CALLBACK post_data_get_element_count(struct _acf_post_data_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  size_t _retval = AcfPostDataCppToC::Get(self)->GetElementCount();

  // Return type: simple
  return _retval;
}

void ACF_CALLBACK
post_data_get_elements(struct _acf_post_data_t* self,
                       size_t* elementsCount,
                       struct _acf_post_data_element_t** elements) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: elements; type: refptr_vec_same_byref
  if (!elementsCount || (*elementsCount > 0 && !elements))
    return;

  // Translate param: elements; type: refptr_vec_same_byref
  std::vector<AcfRefPtr<AcfPostDataElement>> elementsList;
  if (elementsCount && *elementsCount > 0 && elements) {
    for (size_t i = 0; i < *elementsCount; ++i) {
      elementsList.push_back(AcfPostDataElementCppToC::Unwrap(elements[i]));
    }
  }

  // Execute
  AcfPostDataCppToC::Get(self)->GetElements(elementsList);

  // Restore param: elements; type: refptr_vec_same_byref
  if (elementsCount && elements) {
    *elementsCount = std::min(elementsList.size(), *elementsCount);
    if (*elementsCount > 0) {
      for (size_t i = 0; i < *elementsCount; ++i) {
        elements[i] = AcfPostDataElementCppToC::Wrap(elementsList[i]);
      }
    }
  }
}

int ACF_CALLBACK
post_data_remove_element(struct _acf_post_data_t* self,
                         struct _acf_post_data_element_t* element) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;
  // Verify param: element; type: refptr_same
  if (!element)
    return 0;

  // Execute
  bool _retval = AcfPostDataCppToC::Get(self)->RemoveElement(
      AcfPostDataElementCppToC::Unwrap(element));

  // Return type: bool
  return _retval;
}

int ACF_CALLBACK
post_data_add_element(struct _acf_post_data_t* self,
                      struct _acf_post_data_element_t* element) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;
  // Verify param: element; type: refptr_same
  if (!element)
    return 0;

  // Execute
  bool _retval = AcfPostDataCppToC::Get(self)->AddElement(
      AcfPostDataElementCppToC::Unwrap(element));

  // Return type: bool
  return _retval;
}

void ACF_CALLBACK post_data_remove_elements(struct _acf_post_data_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;

  // Execute
  AcfPostDataCppToC::Get(self)->RemoveElements();
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfPostDataCppToC::AcfPostDataCppToC() {
  GetStruct()->is_read_only = post_data_is_read_only;
  GetStruct()->has_excluded_elements = post_data_has_excluded_elements;
  GetStruct()->get_element_count = post_data_get_element_count;
  GetStruct()->get_elements = post_data_get_elements;
  GetStruct()->remove_element = post_data_remove_element;
  GetStruct()->add_element = post_data_add_element;
  GetStruct()->remove_elements = post_data_remove_elements;
}

// DESTRUCTOR - Do not edit by hand.

AcfPostDataCppToC::~AcfPostDataCppToC() {}

template <>
AcfRefPtr<AcfPostData>
AcfCppToCRefCounted<AcfPostDataCppToC, AcfPostData, acf_post_data_t>::
    UnwrapDerived(AcfWrapperType type, acf_post_data_t* s) {
  return nullptr;
}

template <>
AcfWrapperType AcfCppToCRefCounted<AcfPostDataCppToC,
                                   AcfPostData,
                                   acf_post_data_t>::kWrapperType =
    WT_POST_DATA;