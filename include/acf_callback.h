#ifndef ACF_CALLBACK_H_
#define ACF_CALLBACK_H_

#include "include/internal/acf_scoped_refptr.h"
#include "include/acf_values.h"

class AcfValue;

///
/// Complete event notify
///
/*--acf(source=client)--*/
class AcfCompleteHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called when task has been completed.
  ///
  /*--acf()--*/
  virtual void OnComplete(bool success) = 0;
};

///
/// Complete callback with value
///
/*--acf(source=client)--*/
class AcfCompleteValueHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called when task has been completed.
  ///
  /*--acf(optional_param=value)--*/
  virtual void OnComplete(AcfRefPtr<AcfValue> value) = 0;
};

///
/// Implement this interface to receive string values asynchronously.
///
/*--acf(source=client)--*/
class AcfStringVisitor : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Method that will be executed.
  ///
  /*--acf(optional_param=string)--*/
  virtual void Visit(const AcfString& string) = 0;
};

///
/// Complete event notify
///
/*--acf(source=client)--*/
class AcfNumberCompleteHandler : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Called when task has been completed.
  ///
  /*--acf()--*/
  virtual void OnComplete(int value) = 0;
};

///
/// Complete event callback generic
///
/*--acf(source=library)--*/
class AcfCallback : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Continue process event
  ///
  /*--acf(capi_name=cont)--*/
  virtual void Continue(bool cancel) = 0;
};

#endif  // ACF_CALLBACK_H_