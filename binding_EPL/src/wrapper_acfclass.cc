#include "wrapper_acfclass.h"
#include "struct_class.h"

#undef min

extern DWORD acf_cpp_fntable_request[];
extern DWORD acf_cpp_fntable_response[];

void responsecb_continue(ACFResourceResponseCallback* obj, const void* buffer,
                         size_t size, AcfResponse* response, LPCSTR redirect) {
  obj->Continue(new AcfRequestResponseWrapper(
      buffer, size, response, size, redirect ? redirect : AcfString()));
}

DWORD acf_cpp_fntable_responsecallback[] = {
    (DWORD)responsecb_continue,
};

namespace {

int ACF_CALLBACK filter_get_total_bytes(ACFResourceFilter* obj) {
  ISVALIDR(obj, NULL);

  return obj->GetTotalBytes();
}

void ACF_CALLBACK filter_get_buffer(ACFResourceFilter* obj, LPVOID buffer,
                                    int length) {
  ISVALID(obj);

  obj->GetBuffer(buffer, length);
}

void ACF_CALLBACK filter_set_buffer(ACFResourceFilter* obj, LPVOID buffer,
                                    int length) {
  ISVALID(obj);

  obj->SetBuffer(buffer, length);
}

} // namespace

DWORD acf_cpp_fntable_filter[] = {
    (DWORD)filter_get_total_bytes,
    (DWORD)filter_get_buffer,
    (DWORD)filter_set_buffer,
};

AcfRequestResponseWrapper::AcfRequestResponseWrapper(
    const void* buffer, size_t size, AcfRefPtr<AcfResponse> response,
    int64_t length, std::string redirect)
    : response_(response), length_(length), redirect_(redirect) {
  data_.assign(size, 0);
  memcpy((void*)data_.data(), buffer, size);
}

AcfRequestResponseWrapper::~AcfRequestResponseWrapper() {}

bool AcfRequestResponseWrapper::Open(AcfRefPtr<AcfRequest> request,
                                     bool& handle_request) {
  return true;
}

void AcfRequestResponseWrapper::GetResponseHeaders(
    AcfRefPtr<AcfResponse> response, int64& response_length,
    AcfString& redirectUrl) {
  response_length = length_;
  redirectUrl = redirect_;
  response->Set(response_);
}

void AcfRequestResponseWrapper::Skip(
    int64 bytes_to_skip, AcfRefPtr<AcfResourceSkipCallback> callback) {
  offset_ += bytes_to_skip;
  callback->Continue(bytes_to_skip);
}

void AcfRequestResponseWrapper::Read(
    void* data_out, int bytes_to_read,
    AcfRefPtr<AcfResourceReadCallback> callback) {
  bool has_data = false;
  int bytes_read = 0;

  if (offset_ < data_.length()) {
    // Copy the next block of data into the buffer.
    int transfer_size =
        std::min(bytes_to_read, static_cast<int>(data_.length() - offset_));
    memcpy(data_out, data_.data() + offset_, transfer_size);
    offset_ += transfer_size;

    bytes_read = transfer_size;
    has_data = true;
  }

  callback->Continue(has_data ? bytes_read : 0);
}

void AcfRequestResponseWrapper::Cancel() {}

ACFResourceFilterHandler::ACFResourceFilterHandler(
    LPVOID callback, AcfRefPtr<AcfProfile> profile, int64_t frame_id,
    AcfRefPtr<AcfRequest> request, AcfRefPtr<AcfResponse> response)
    : _rawcallback(callback),
      profile_(profile),
      frame_id_(frame_id),
      request_(request),
      response_(response) {}

ACFResourceFilterHandler::~ACFResourceFilterHandler() {}

size_t ACFResourceFilterHandler::GetTotalBytes() { return _totalReadBytes; }

void ACFResourceFilterHandler::GetBuffer(void* outputBuffer, size_t length) {
  if (!outputBuffer || length <= 0 || _totalReadBytes <= 0 ||
      length > _totalReadBytes) {
    return;
  }
  _rdbuf.seekg(0, std::ios_base::beg);
  _rdbuf.read((char*)outputBuffer, length);
  _rdbuf.seekg(0, std::ios_base::beg);
}

void ACFResourceFilterHandler::SetBuffer(void* inputBuffer, size_t length) {
  _rdbuf.clear();
  _rdbuf.seekp(0, std::ios_base::beg);
  _rdbuf.write((char*)inputBuffer, length);
  _totalReadBytes = length;
}

bool ACFResourceFilterHandler::InitFilter() {
  _readEnded = false;
  _rdbuf.clear();
  _totalReadBytes = NULL;

  return true;
}

ACFResourceFilterHandler::FilterStatus ACFResourceFilterHandler::Filter(
    void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out,
    size_t data_out_size, size_t& data_out_written) {
  // Read All Data
  if (data_in && data_in_size > 0) {
    _rdbuf.write((char*)data_in, data_in_size);
    _totalReadBytes += data_in_size;
    data_in_read = data_in_size;
  } else {
    if (_readEnded == false) {
      // Handler
      if (_rawcallback != NULL) {
        LPVOID pClass = _rawcallback;

        AcfRefPtr<ACFResourceFilter> filter = new ACFResourceFilter(this);
        
        IMP_NEWECLASS(TempFilter, filter.get(),
                      eClass::m_pVfTable_ResponseFilter,
                      acf_cpp_fntable_filter);
        IMP_NEWECLASS(TempResponse, response_.get(),
                      eClass::m_pVfTable_Response,
                      acf_cpp_fntable_filter);
        IMP_NEWECLASS(TempRequest, request_.get(),
                      eClass::m_pVfTable_Request, acf_cpp_fntable_request);

        request_->AddRef();
        response_->AddRef();
        filter->AddRef();
        __asm {
					push ecx;
					push ebx;
					push edi;
					push esi;
					mov ebx, pClass;
					mov edx, [ebx];
					lea ecx, pClass;
					push TempFilter;
					push TempResponse;
					push TempRequest;
					push ecx;
					call[edx + 0x24];
					pop esi;
					pop edi;
					pop ebx;
					pop ecx;
        }
        request_->Release();
        response_->Release();
        filter->Release();
      }

      _readEnded = true;
    }

    if (_totalReadBytes > 0) {
      if (_totalReadBytes < data_out_size) {
        _rdbuf.read((char*)data_out, _totalReadBytes);
        data_out_written = _totalReadBytes;
        _totalReadBytes = 0;
        return FilterStatus::RESPONSE_FILTER_DONE;
      } else {
        _rdbuf.read((char*)data_out, data_out_size);
        data_out_written = data_out_size;
        _totalReadBytes -= data_out_size;
      }
    }
  }

  return FilterStatus::RESPONSE_FILTER_NEED_MORE_DATA;
}

ACFResourceFilter::ACFResourceFilter(AcfRefPtr<ACFResourceFilterHandler> filter)
    : _rawptr(filter) {}

ACFResourceFilter::~ACFResourceFilter() {}

size_t ACFResourceFilter::GetTotalBytes() { return _rawptr->GetTotalBytes(); }

void ACFResourceFilter::GetBuffer(void* outputBuffer, size_t length) {
  _rawptr->GetBuffer(outputBuffer, length);
}

void ACFResourceFilter::SetBuffer(void* inputBuffer, size_t length) {
  _rawptr->SetBuffer(inputBuffer, length);
}
