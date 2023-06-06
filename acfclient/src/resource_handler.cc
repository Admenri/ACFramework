#include "resource_handler.h"

#include <iostream>

#undef min

namespace {

// Filter that writes out all of the contents unchanged.
class PassThruResponseFilter : public AcfResponseFilter {
 public:
  PassThruResponseFilter() {}

  bool InitFilter() override { return true; }

  FilterStatus Filter(void* data_in,
                      size_t data_in_size,
                      size_t& data_in_read,
                      void* data_out,
                      size_t data_out_size,
                      size_t& data_out_written) override {
    // Write out the contents unchanged.
    data_out_written = std::min(data_in_size, data_out_size);

    // All data will be read.
    data_in_read = data_out_written;

    if (data_out_written > 0) {
      memcpy(data_out, data_in, data_out_written);
    }

    return RESPONSE_FILTER_DONE;
  }

 private:
  IMPLEMENT_REFCOUNTING(PassThruResponseFilter);
};

class ClientSchemeHandler : public AcfResourceHandler {
 public:
  ClientSchemeHandler() : offset_(0) {}

  bool Open(AcfRefPtr<AcfRequest> request, bool& handle_request) override {
    // The request will be continued or canceled based on the return value.
    handle_request = true;

    bool handled = false;

    std::string url = request->GetURL();
    if (strstr(url.c_str(), "/handler.html") != nullptr) {
      // Build the response html
      data_ =
          "<html><head><title>Client Scheme Handler</title></head>"
          "<body bgcolor=\"white\">"
          "This contents of this page page are served by the "
          "ClientSchemeHandler class handling the client:// protocol."
          "<br/>You should see an image:"
          "<br/><img src=\"client://tests/logo.png\"><pre>";
      data_.append(
          "</pre><br/>Try the test form:"
          "<form method=\"POST\" action=\"handler.html\">"
          "<input type=\"text\" name=\"field1\">"
          "<input type=\"text\" name=\"field2\">"
          "<input type=\"submit\">"
          "</form></body></html>");

      handled = true;

      // Set the resulting mime type
      mime_type_ = "text/html";
    }

    return handled;
  }

  void GetResponseHeaders(AcfRefPtr<AcfResponse> response,
                          int64& response_length,
                          AcfString& redirectUrl) override {
    response->SetMimeType(mime_type_);
    response->SetStatus(200);

    // Set the resulting response length
    response_length = data_.length();
  }

  void Cancel() override {}

  void Read(void* data_out,
            int bytes_to_read,
            AcfRefPtr<AcfResourceReadCallback> callback) override {
    bool has_data = false;
    int bytes_read = 0;

    if (offset_ < data_.length()) {
      // Copy the next block of data into the buffer.
      int transfer_size =
          std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
      memcpy(data_out, data_.c_str() + offset_, transfer_size);
      offset_ += transfer_size;

      bytes_read = transfer_size;
      has_data = true;
    }

    callback->Continue(has_data ? bytes_read : 0);
  }

 private:
  std::string data_;
  std::string mime_type_;
  size_t offset_;

  IMPLEMENT_REFCOUNTING(ClientSchemeHandler);
};

}  // namespace

TestResourceRequestHandler::TestResourceRequestHandler() {}

TestResourceRequestHandler::~TestResourceRequestHandler() {}

bool TestResourceRequestHandler::OnBeforeResourceLoad(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request) {
  return false;
}

AcfRefPtr<AcfResourceHandler> TestResourceRequestHandler::GetResourceHandler(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request) {
  if (request->GetURL().ToString().find("://test/acf_page") !=
      std::string::npos) {
    std::cout << __FUNCTION__ << '\n';
    return new ClientSchemeHandler();
  }
  return nullptr;
}

void TestResourceRequestHandler::OnResourceRedirect(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request,
    AcfRefPtr<AcfResponse> response,
    AcfString& new_url) {}

void TestResourceRequestHandler::OnResourceResponse(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request,
    AcfRefPtr<AcfResponse> response) {}

AcfRefPtr<AcfResponseFilter>
TestResourceRequestHandler::GetResourceResponseFilter(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request,
    AcfRefPtr<AcfResponse> response) {
  return nullptr;
}

void TestResourceRequestHandler::OnResourceLoadComplete(
    AcfRefPtr<AcfProfile> profile,
    int64 frame_id,
    AcfRefPtr<AcfRequest> request,
    AcfRefPtr<AcfResponse> response,
    URLRequestStatus status,
    int64 received_content_length) {}
