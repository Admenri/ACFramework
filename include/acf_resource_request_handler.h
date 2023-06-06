#ifndef ACF_RESOURCE_REQUEST_HANDLER_H_
#define ACF_RESOURCE_REQUEST_HANDLER_H_

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_types.h"

#include "include/acf_profile.h"
#include "include/acf_frame.h"
#include "include/acf_response.h"
#include "include/acf_request.h"
#include "include/acf_callback.h"
#include "include/acf_frame.h"

class AcfFrame;
class AcfCallback;
class AcfResponseFilter;
class AcfResourceRequestHandler;
class AcfResourceHandler;
class AcfResourceSkipCallback;
class AcfResourceReadCallback;

///
/// Implement this interface to handle events related to browser requests. The
/// methods of this class will be called on the IO thread unless otherwise
/// indicated.
///
/*--acf(source=client)--*/
class AcfResourceRequestHandler : public virtual AcfBaseRefCounted {
 public:
  typedef acf_urlrequest_status_t URLRequestStatus;

  ///
  /// Called on the IO thread before a resource request is loaded. The |browser|
  /// and |frame| values represent the source of the request, and may be NULL
  /// for requests originating from service workers or AcfURLRequest. To
  /// redirect or change the resource load optionally modify |request|.
  /// Modification of the request URL will be treated as a redirect. Return
  /// RV_CONTINUE to continue the request immediately.
  /// Default: Continue load resource.
  ///
  /*--acf()--*/
  virtual bool OnBeforeResourceLoad(AcfRefPtr<AcfProfile> profile,
                                    int64 frame_id,
                                    AcfRefPtr<AcfRequest> request) {
    return false;
  }

  ///
  /// Called on the IO thread before a resource is loaded. The |browser| and
  /// |frame| values represent the source of the request, and may be NULL for
  /// requests originating from service workers or AcfURLRequest. To allow the
  /// resource to load using the default network loader return NULL. To specify
  /// a handler for the resource return a AcfResourceHandler object. The
  /// |request| object cannot not be modified in this callback.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfResourceHandler> GetResourceHandler(
      AcfRefPtr<AcfProfile> profile,
      int64 frame_id,
      AcfRefPtr<AcfRequest> request) {
    return nullptr;
  }

  ///
  /// Called on the IO thread when a resource load is redirected. The |browser|
  /// and |frame| values represent the source of the request, and may be NULL
  /// for requests originating from service workers or AcfURLRequest. The
  /// |request| parameter will contain the old URL and other request-related
  /// information. The |response| parameter will contain the response that
  /// resulted in the redirect. The |new_url| parameter will contain the new URL
  /// and can be changed if desired. The |request| and |response| objects cannot
  /// be modified in this callback.
  ///
  /*--acf()--*/
  virtual void OnResourceRedirect(AcfRefPtr<AcfProfile> profile,
                                  int64 frame_id,
                                  AcfRefPtr<AcfRequest> request,
                                  AcfRefPtr<AcfResponse> response,
                                  AcfString& new_url) {}

  ///
  /// Called on the IO thread when a resource response is received. The
  /// |browser| and |frame| values represent the source of the request, and may
  /// be NULL for requests originating from service workers or CefURLRequest. To
  /// allow the resource load to proceed without modification return false. To
  /// redirect or retry the resource load optionally modify |request| and return
  /// true. Modification of the request URL will be treated as a redirect.
  /// Requests handled using the default network loader cannot be redirected in
  /// this callback. The |response| object cannot be modified in this callback.
  ///
  /// WARNING: Redirecting using this method is deprecated. Use
  /// OnBeforeResourceLoad or GetResourceHandler to perform redirects.
  ///
  /*--acf()--*/
  virtual void OnResourceResponse(AcfRefPtr<AcfProfile> profile,
                                  int64 frame_id,
                                  AcfRefPtr<AcfRequest> request,
                                  AcfRefPtr<AcfResponse> response) {}

  ///
  /// Called on the IO thread to optionally filter resource response content.
  /// The |browser| and |frame| values represent the source of the request, and
  /// may be NULL for requests originating from service workers or
  /// AcfURLRequest. |request| and |response| represent the request and response
  /// respectively and cannot be modified in this callback.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfResponseFilter> GetResourceResponseFilter(
      AcfRefPtr<AcfProfile> profile,
      int64 frame_id,
      AcfRefPtr<AcfRequest> request,
      AcfRefPtr<AcfResponse> response) {
    return nullptr;
  }

  ///
  /// Called on the IO thread when a resource load has completed. The |browser|
  /// and |frame| values represent the source of the request, and may be NULL
  /// for requests originating from service workers or AcfURLRequest. |request|
  /// and |response| represent the request and response respectively and cannot
  /// be modified in this callback. |status| indicates the load completion
  /// status. |received_content_length| is the number of response bytes actually
  /// read. This method will be called for all requests, including requests that
  /// are aborted due to Acf shutdown or destruction of the associated browser.
  /// In cases where the associated browser is destroyed this callback may
  /// arrive after the AcfLifeSpanHandler::OnBeforeClose callback for that
  /// browser. The AcfFrame::IsValid method can be used to test for this
  /// situation, and care should be taken not to call |browser| or |frame|
  /// methods that modify state (like LoadURL, SendProcessMessage, etc.) if the
  /// frame is invalid.
  ///
  /*--acf()--*/
  virtual void OnResourceLoadComplete(AcfRefPtr<AcfProfile> profile,
                                      int64 frame_id,
                                      AcfRefPtr<AcfRequest> request,
                                      AcfRefPtr<AcfResponse> response,
                                      URLRequestStatus status,
                                      int64 received_content_length) {}
};

///
/// Callback for asynchronous continuation of AcfResourceHandler::Skip().
///
/*--acf(source=library)--*/
class AcfResourceSkipCallback : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Callback for asynchronous continuation of Skip(). If |bytes_skipped| > 0
  /// then either Skip() will be called again until the requested number of
  /// bytes have been skipped or the request will proceed. If |bytes_skipped|
  /// <= 0 the request will fail with ERR_REQUEST_RANGE_NOT_SATISFIABLE.
  ///
  /*--acf(capi_name=cont)--*/
  virtual void Continue(int64 bytes_skipped) = 0;
};

///
/// Callback for asynchronous continuation of AcfResourceHandler::Read().
///
/*--acf(source=library)--*/
class AcfResourceReadCallback : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Callback for asynchronous continuation of Read(). If |bytes_read| == 0
  /// the response will be considered complete. If |bytes_read| > 0 then Read()
  /// will be called again until the request is complete (based on either the
  /// result or the expected content length). If |bytes_read| < 0 then the
  /// request will fail and the |bytes_read| value will be treated as the error
  /// code.
  ///
  /*--acf(capi_name=cont)--*/
  virtual void Continue(int bytes_read) = 0;
};

///
/// Class used to implement a custom request handler interface. The methods of
/// this class will be called on the IO thread unless otherwise indicated.
///
/*--acf(source=client)--*/
class AcfResourceHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Open the response stream. To handle the request immediately set
  /// |handle_request| to true and return true. To decide at a later time set
  /// |handle_request| to false, return true, and execute |callback| to continue
  /// or cancel the request. To cancel the request immediately set
  /// |handle_request| to true and return false. This method will be called in
  /// sequence but not from a dedicated thread. For backwards compatibility set
  /// |handle_request| to false and return false and the ProcessRequest method
  /// will be called.
  ///
  /*--acf()--*/
  virtual bool Open(AcfRefPtr<AcfRequest> request,
                    bool& handle_request) {
    handle_request = false;
    return false;
  }

  ///
  /// Retrieve response header information. If the response length is not known
  /// set |response_length| to -1 and ReadResponse() will be called until it
  /// returns false. If the response length is known set |response_length|
  /// to a positive value and ReadResponse() will be called until it returns
  /// false or the specified number of bytes have been read. Use the |response|
  /// object to set the mime type, http status code and other optional header
  /// values. To redirect the request to a new URL set |redirectUrl| to the new
  /// URL. |redirectUrl| can be either a relative or fully qualified URL.
  /// It is also possible to set |response| to a redirect http status code
  /// and pass the new URL via a Location header. Likewise with |redirectUrl| it
  /// is valid to set a relative or fully qualified URL as the Location header
  /// value. If an error occured while setting up the request you can call
  /// SetError() on |response| to indicate the error condition.
  ///
  /*--acf()--*/
  virtual void GetResponseHeaders(AcfRefPtr<AcfResponse> response,
                                  int64& response_length,
                                  AcfString& redirectUrl) = 0;

  ///
  /// Skip response data when requested by a Range header. Skip over and discard
  /// |bytes_to_skip| bytes of response data. If data is available immediately
  /// set |bytes_skipped| to the number of bytes skipped and return true. To
  /// read the data at a later time set |bytes_skipped| to 0, return true and
  /// execute |callback| when the data is available. To indicate failure set
  /// |bytes_skipped| to < 0 (e.g. -2 for ERR_FAILED) and return false. This
  /// method will be called in sequence but not from a dedicated thread.
  ///
  /*--acf()--*/
  virtual void Skip(int64 bytes_to_skip,
                    AcfRefPtr<AcfResourceSkipCallback> callback) {}

  ///
  /// Read response data. If data is available immediately copy up to
  /// |bytes_to_read| bytes into |data_out|, set |bytes_read| to the number of
  /// bytes copied, and return true. To read the data at a later time keep a
  /// pointer to |data_out|, set |bytes_read| to 0, return true and execute
  /// |callback| when the data is available (|data_out| will remain valid until
  /// the callback is executed). To indicate response completion set
  /// |bytes_read| to 0 and return false. To indicate failure set |bytes_read|
  /// to < 0 (e.g. -2 for ERR_FAILED) and return false. This method will be
  /// called in sequence but not from a dedicated thread. For backwards
  /// compatibility set |bytes_read| to -1 and return false and the ReadResponse
  /// method will be called.
  ///
  /*--acf()--*/
  virtual void Read(void* data_out,
                    int bytes_to_read,
                    AcfRefPtr<AcfResourceReadCallback> callback) {}

  ///
  /// Request processing has been canceled.
  ///
  /*--acf()--*/
  virtual void Cancel() = 0;
};

///
/// Implement this interface to filter resource response content. The methods of
/// this class will be called on the browser process IO thread.
///
/*--acf(source=client)--*/
class AcfResponseFilter : public virtual AcfBaseRefCounted {
 public:
  typedef acf_response_filter_status_t FilterStatus;

  ///
  /// Initialize the response filter. Will only be called a single time. The
  /// filter will not be installed if this method returns false.
  ///
  /*--acf()--*/
  virtual bool InitFilter() = 0;

  ///
  /// Called to filter a chunk of data. Expected usage is as follows:
  ///
  ///  1. Read input data from |data_in| and set |data_in_read| to the number of
  ///     bytes that were read up to a maximum of |data_in_size|. |data_in| will
  ///     be NULL if |data_in_size| is zero.
  ///  2. Write filtered output data to |data_out| and set |data_out_written| to
  ///     the number of bytes that were written up to a maximum of
  ///     |data_out_size|. If no output data was written then all data must be
  ///     read from |data_in| (user must set |data_in_read| = |data_in_size|).
  ///  3. Return RESPONSE_FILTER_DONE if all output data was written or
  ///     RESPONSE_FILTER_NEED_MORE_DATA if output data is still pending.
  ///
  /// This method will be called repeatedly until the input buffer has been
  /// fully read (user sets |data_in_read| = |data_in_size|) and there is no
  /// more input data to filter (the resource response is complete). This method
  /// may then be called an additional time with an empty input buffer if the
  /// user filled the output buffer (set |data_out_written| = |data_out_size|)
  /// and returned RESPONSE_FILTER_NEED_MORE_DATA to indicate that output data
  /// is still pending.
  ///
  /// Calls to this method will stop when one of the following conditions is
  /// met:
  ///
  ///  1. There is no more input data to filter (the resource response is
  ///     complete) and the user sets |data_out_written| = 0 or returns
  ///     RESPONSE_FILTER_DONE to indicate that all data has been written, or;
  ///  2. The user returns RESPONSE_FILTER_ERROR to indicate an error.
  ///
  /// Do not keep a reference to the buffers passed to this method.
  ///
  /*--acf(optional_param=data_in,default_retval=RESPONSE_FILTER_ERROR)--*/
  virtual FilterStatus Filter(void* data_in,
                              size_t data_in_size,
                              size_t& data_in_read,
                              void* data_out,
                              size_t data_out_size,
                              size_t& data_out_written) = 0;
};

#endif  // ACF_RESOURCE_REQUEST_HANDLER_H_