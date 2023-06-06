// Copyright (c) 2023 Admenri. All rights reserved.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the ACF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//
// $hash=e5206e1ef73d3de23ade1ef064d4c6f70157ebc4$
//

#include "libacf_dll/cpptoc/resource_request_handler_cpptoc.h"
#include "libacf_dll/cpptoc/resource_handler_cpptoc.h"
#include "libacf_dll/cpptoc/response_filter_cpptoc.h"
#include "libacf_dll/ctocpp/profile_ctocpp.h"
#include "libacf_dll/ctocpp/request_ctocpp.h"
#include "libacf_dll/ctocpp/response_ctocpp.h"

namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

int ACF_CALLBACK resource_request_handler_on_before_resource_load(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return 0;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return 0;
  // Verify param: request; type: refptr_diff
  if (!request)
    return 0;

  // Execute
  bool _retval =
      AcfResourceRequestHandlerCppToC::Get(self)->OnBeforeResourceLoad(
          AcfProfileCToCpp::Wrap(profile), frame_id,
          AcfRequestCToCpp::Wrap(request));

  // Return type: bool
  return _retval;
}

struct _acf_resource_handler_t* ACF_CALLBACK
resource_request_handler_get_resource_handler(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return NULL;
  // Verify param: request; type: refptr_diff
  if (!request)
    return NULL;

  // Execute
  AcfRefPtr<AcfResourceHandler> _retval =
      AcfResourceRequestHandlerCppToC::Get(self)->GetResourceHandler(
          AcfProfileCToCpp::Wrap(profile), frame_id,
          AcfRequestCToCpp::Wrap(request));

  // Return type: refptr_same
  return AcfResourceHandlerCppToC::Wrap(_retval);
}

void ACF_CALLBACK resource_request_handler_on_resource_redirect(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request,
    struct _acf_response_t* response,
    acf_string_t* new_url) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return;
  // Verify param: request; type: refptr_diff
  if (!request)
    return;
  // Verify param: response; type: refptr_diff
  if (!response)
    return;
  // Verify param: new_url; type: string_byref
  if (!new_url)
    return;

  // Translate param: new_url; type: string_byref
  AcfString new_urlStr(new_url);

  // Execute
  AcfResourceRequestHandlerCppToC::Get(self)->OnResourceRedirect(
      AcfProfileCToCpp::Wrap(profile), frame_id,
      AcfRequestCToCpp::Wrap(request), AcfResponseCToCpp::Wrap(response),
      new_urlStr);
}

void ACF_CALLBACK resource_request_handler_on_resource_response(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request,
    struct _acf_response_t* response) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return;
  // Verify param: request; type: refptr_diff
  if (!request)
    return;
  // Verify param: response; type: refptr_diff
  if (!response)
    return;

  // Execute
  AcfResourceRequestHandlerCppToC::Get(self)->OnResourceResponse(
      AcfProfileCToCpp::Wrap(profile), frame_id,
      AcfRequestCToCpp::Wrap(request), AcfResponseCToCpp::Wrap(response));
}

struct _acf_response_filter_t* ACF_CALLBACK
resource_request_handler_get_resource_response_filter(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request,
    struct _acf_response_t* response) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return NULL;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return NULL;
  // Verify param: request; type: refptr_diff
  if (!request)
    return NULL;
  // Verify param: response; type: refptr_diff
  if (!response)
    return NULL;

  // Execute
  AcfRefPtr<AcfResponseFilter> _retval =
      AcfResourceRequestHandlerCppToC::Get(self)->GetResourceResponseFilter(
          AcfProfileCToCpp::Wrap(profile), frame_id,
          AcfRequestCToCpp::Wrap(request), AcfResponseCToCpp::Wrap(response));

  // Return type: refptr_same
  return AcfResponseFilterCppToC::Wrap(_retval);
}

void ACF_CALLBACK resource_request_handler_on_resource_load_complete(
    struct _acf_resource_request_handler_t* self,
    acf_profile_t* profile,
    int64 frame_id,
    acf_request_t* request,
    struct _acf_response_t* response,
    acf_urlrequest_status_t status,
    int64 received_content_length) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  if (!self)
    return;
  // Verify param: profile; type: refptr_diff
  if (!profile)
    return;
  // Verify param: request; type: refptr_diff
  if (!request)
    return;
  // Verify param: response; type: refptr_diff
  if (!response)
    return;

  // Execute
  AcfResourceRequestHandlerCppToC::Get(self)->OnResourceLoadComplete(
      AcfProfileCToCpp::Wrap(profile), frame_id,
      AcfRequestCToCpp::Wrap(request), AcfResponseCToCpp::Wrap(response),
      status, received_content_length);
}

}  // namespace

// CONSTRUCTOR - Do not edit by hand.

AcfResourceRequestHandlerCppToC::AcfResourceRequestHandlerCppToC() {
  GetStruct()->on_before_resource_load =
      resource_request_handler_on_before_resource_load;
  GetStruct()->get_resource_handler =
      resource_request_handler_get_resource_handler;
  GetStruct()->on_resource_redirect =
      resource_request_handler_on_resource_redirect;
  GetStruct()->on_resource_response =
      resource_request_handler_on_resource_response;
  GetStruct()->get_resource_response_filter =
      resource_request_handler_get_resource_response_filter;
  GetStruct()->on_resource_load_complete =
      resource_request_handler_on_resource_load_complete;
}

// DESTRUCTOR - Do not edit by hand.

AcfResourceRequestHandlerCppToC::~AcfResourceRequestHandlerCppToC() {}

template <>
AcfRefPtr<AcfResourceRequestHandler>
AcfCppToCRefCounted<AcfResourceRequestHandlerCppToC,
                    AcfResourceRequestHandler,
                    acf_resource_request_handler_t>::
    UnwrapDerived(AcfWrapperType type, acf_resource_request_handler_t* s) {
  return nullptr;
}

template <>
AcfWrapperType
    AcfCppToCRefCounted<AcfResourceRequestHandlerCppToC,
                        AcfResourceRequestHandler,
                        acf_resource_request_handler_t>::kWrapperType =
        WT_RESOURCE_REQUEST_HANDLER;
