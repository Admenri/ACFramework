// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=8869760fcd10d3e0f048e02d4215f843ba004daf$
//

#include "libacf_dll/cpptoc/frame_cpptoc.h"
#include "libacf_dll/cpptoc/browser_cpptoc.h"
#include "libacf_dll/ctocpp/complete_value_handler_ctocpp.h"
#include "libacf_dll/ctocpp/string_visitor_ctocpp.h"

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

void ACF_CALLBACK
frame_execute_javascript(struct _acf_frame_t* self,
                         const acf_string_t* script,
                         const acf_string_t* url,
                         acf_complete_value_handler_t* handler) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: script; type: string_byref_const
  if (!script)
    return;
  // Verify param: url; type: string_byref_const
  if (!url)
    return;
  // Unverified params: handler

  // Execute
  AcfFrameCppToC::Get(self)->ExecuteJavascript(
      AcfString(script), AcfString(url),
      AcfCompleteValueHandlerCToCpp::Wrap(handler));
}

void ACF_CALLBACK frame_get_source(struct _acf_frame_t* self,
                                   acf_string_visitor_t* visitor) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: visitor; type: refptr_diff
  if (!visitor)
    return;

  // Execute
  AcfFrameCppToC::Get(self)->GetSource(AcfStringVisitorCToCpp::Wrap(visitor));
}

void ACF_CALLBACK frame_get_text(struct _acf_frame_t* self,
                                 acf_string_visitor_t* visitor) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: visitor; type: refptr_diff
  if (!visitor)
    return;

  // Execute
  AcfFrameCppToC::Get(self)->GetText(AcfStringVisitorCToCpp::Wrap(visitor));
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
  GetStruct()->execute_javascript = frame_execute_javascript;
  GetStruct()->get_source = frame_get_source;
  GetStruct()->get_text = frame_get_text;
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
