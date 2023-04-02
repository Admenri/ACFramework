// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=fbb72b4bf66c2cfeb9f0d49ed2ef94b1c5fdcbb3$
//

#include "libacf_dll/cpptoc/frame_cpptoc.h"
#include "libacf_dll/cpptoc/browser_cpptoc.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int ACF_CALLBACK frame_is_valid(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfFrameCppToC::Get(self)->IsValid();

  // Return type: bool
  return _retval;
}

int ACF_CALLBACK frame_is_same(struct _acf_frame_t* self,
                               struct _acf_frame_t* object) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;
  // Verify param: object; type: refptr_same
  if (!object)
    return 0;

  // Execute
  bool _retval =
      AcfFrameCppToC::Get(self)->IsSame(AcfFrameCppToC::Unwrap(object));

  // Return type: bool
  return _retval;
}

struct _acf_frame_t* ACF_CALLBACK frame_get_parent(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfRefPtr<AcfFrame> _retval = AcfFrameCppToC::Get(self)->GetParent();

  // Return type: refptr_same
  return AcfFrameCppToC::Wrap(_retval);
}

acf_browser_t* ACF_CALLBACK frame_get_browser(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfRefPtr<AcfBrowser> _retval = AcfFrameCppToC::Get(self)->GetBrowser();

  // Return type: refptr_same
  return AcfBrowserCppToC::Wrap(_retval);
}

acf_string_userfree_t ACF_CALLBACK frame_get_url(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfString _retval = AcfFrameCppToC::Get(self)->GetURL();

  // Return type: string
  return _retval.DetachToUserFree();
}

acf_string_userfree_t ACF_CALLBACK frame_get_name(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;

  // Execute
  AcfString _retval = AcfFrameCppToC::Get(self)->GetName();

  // Return type: string
  return _retval.DetachToUserFree();
}

int64 ACF_CALLBACK frame_get_identifier(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  int64 _retval = AcfFrameCppToC::Get(self)->GetIdentifier();

  // Return type: simple
  return _retval;
}

int ACF_CALLBACK frame_is_main(struct _acf_frame_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;

  // Execute
  bool _retval = AcfFrameCppToC::Get(self)->IsMain();

  // Return type: bool
  return _retval;
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfFrameCppToC::AcfFrameCppToC() {
  GetStruct()->is_valid = frame_is_valid;
  GetStruct()->is_same = frame_is_same;
  GetStruct()->get_parent = frame_get_parent;
  GetStruct()->get_browser = frame_get_browser;
  GetStruct()->get_url = frame_get_url;
  GetStruct()->get_name = frame_get_name;
  GetStruct()->get_identifier = frame_get_identifier;
  GetStruct()->is_main = frame_is_main;
}

// DESTRUCTOR - Do not edit by hand.

AcfFrameCppToC::~AcfFrameCppToC() {}

template <>
AcfRefPtr<AcfFrame>
AcfCppToCRefCounted<AcfFrameCppToC, AcfFrame, acf_frame_t>::UnwrapDerived(
    AcfWrapperType type,
    acf_frame_t* s) {
  return nullptr;
}

template <>
AcfWrapperType
    AcfCppToCRefCounted<AcfFrameCppToC, AcfFrame, acf_frame_t>::kWrapperType =
        WT_FRAME;
