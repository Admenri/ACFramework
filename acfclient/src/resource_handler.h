#ifndef ACF_RESOURCE_HANDLER_H_
#define ACF_RESOURCE_HANDLER_H_

#include "include/acf_environment.h"

class TestResourceRequestHandler : public AcfResourceRequestHandler {
 public:
  TestResourceRequestHandler();
  ~TestResourceRequestHandler();

 protected:
  bool OnBeforeResourceLoad(AcfRefPtr<AcfProfile> profile,
                            int64 frame_id,
                            AcfRefPtr<AcfRequest> request) override;
  AcfRefPtr<AcfResourceHandler> GetResourceHandler(
      AcfRefPtr<AcfProfile> profile,
      int64 frame_id,
      AcfRefPtr<AcfRequest> request) override;
  void OnResourceRedirect(AcfRefPtr<AcfProfile> profile,
                          int64 frame_id,
                          AcfRefPtr<AcfRequest> request,
                          AcfRefPtr<AcfResponse> response,
                          AcfString& new_url) override;
  void OnResourceResponse(AcfRefPtr<AcfProfile> profile,
                          int64 frame_id,
                          AcfRefPtr<AcfRequest> request,
                          AcfRefPtr<AcfResponse> response) override;
  AcfRefPtr<AcfResponseFilter> GetResourceResponseFilter(
      AcfRefPtr<AcfProfile> profile,
      int64 frame_id,
      AcfRefPtr<AcfRequest> request,
      AcfRefPtr<AcfResponse> response) override;
  void OnResourceLoadComplete(AcfRefPtr<AcfProfile> profile,
                              int64 frame_id,
                              AcfRefPtr<AcfRequest> request,
                              AcfRefPtr<AcfResponse> response,
                              URLRequestStatus status,
                              int64 received_content_length) override;

 private:
  IMPLEMENT_REFCOUNTING(TestResourceRequestHandler);
};

#endif  // ACF_RESOURCE_HANDLER_H_