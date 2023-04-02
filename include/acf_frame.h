#ifndef ACF_FRAME_H_
#define ACF_FRAME_H_

#include "include/internal/acf_scoped_refptr.h"
#include "include/internal/acf_types.h"
#include "include/acf_browser.h"

class AcfBrowser;

///
/// Frame object that host a iframe dom in browser webcontents,
/// Any operation is async in thread for multi-process arch.
///
/*--acf(source=library)--*/
class AcfFrame : public virtual AcfBaseRefCounted {
 public:
  ///
  /// Get frame object valid state.
  ///
  /*--acf()--*/
  virtual bool IsValid() = 0;

  ///
  /// Compare object with other object.
  ///
  /*--acf()--*/
  virtual bool IsSame(AcfRefPtr<AcfFrame> object) = 0;

  ///
  /// Returns the parent of this frame or NULL if this is the main (top-level)
  /// frame.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfFrame> GetParent() = 0;

  ///
  /// Returns the browser that this frame belongs to.
  ///
  /*--acf()--*/
  virtual AcfRefPtr<AcfBrowser> GetBrowser() = 0;

  ///
  /// Returns the URL currently loaded in this frame.
  ///
  /*--acf()--*/
  virtual AcfString GetURL() = 0;

  ///
  /// Returns the name for this frame. If the frame has an assigned name (for
  /// example, set via the iframe "name" attribute) then that value will be
  /// returned. Otherwise a unique name will be constructed based on the frame
  /// parent hierarchy. The main (top-level) frame will always have an empty
  /// name value.
  ///
  /*--acf()--*/
  virtual AcfString GetName() = 0;

  ///
  /// Returns the globally unique identifier for this frame or < 0 if the
  /// underlying frame does not yet exist.
  ///
  /*--acf()--*/
  virtual int64 GetIdentifier() = 0;

  ///
  /// Is frame main context in browser.
  ///
  /*--acf()--*/
  virtual bool IsMain() = 0;
};

#endif