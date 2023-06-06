#ifndef ACF_TYPES_WRAPPERS_H_
#define ACF_TYPES_WRAPPERS_H_

#include "include/internal/acf_types.h"

///
/// Template class that provides common functionality for CEF structure
/// wrapping. Use only with non-POD types that benefit from referencing unowned
/// members.
///
template <class traits>
class AcfStructBase : public traits::struct_type {
 public:
  using struct_type = typename traits::struct_type;

  AcfStructBase() : attached_to_(NULL) { Init(); }
  virtual ~AcfStructBase() {
    // Only clear this object's data if it isn't currently attached to a
    // structure.
    if (!attached_to_)
      Clear(this);
  }

  AcfStructBase(const AcfStructBase& r) {
    Init();
    *this = r;
  }
  AcfStructBase(const struct_type& r) {
    Init();
    *this = r;
  }

  ///
  /// Attach to the source structure's existing values. DetachTo() can be called
  /// to insert the values back into the existing structure.
  ///
  void AttachTo(struct_type& source) {
    // Only clear this object's data if it isn't currently attached to a
    // structure.
    if (!attached_to_)
      Clear(this);

    // This object is now attached to the new structure.
    attached_to_ = &source;

    // Transfer ownership of the values from the source structure.
    memcpy(static_cast<struct_type*>(this), &source, sizeof(struct_type));
  }

  ///
  /// Relinquish ownership of values to the target structure.
  ///
  void DetachTo(struct_type& target) {
    if (attached_to_ != &target) {
      // Clear the target structure's values only if we are not currently
      // attached to that structure.
      Clear(&target);
    }

    // Transfer ownership of the values to the target structure.
    memcpy(&target, static_cast<struct_type*>(this), sizeof(struct_type));

    // Remove the references from this object.
    Init();
  }

  ///
  /// Set this object's values. If |copy| is true the source structure's values
  /// will be copied instead of referenced.
  ///
  void Set(const struct_type& source, bool copy) {
    traits::set(&source, this, copy);
  }

  AcfStructBase& operator=(const AcfStructBase& s) {
    return operator=(static_cast<const struct_type&>(s));
  }

  AcfStructBase& operator=(const struct_type& s) {
    Set(s, true);
    return *this;
  }

 protected:
  void Init() {
    memset(static_cast<struct_type*>(this), 0, sizeof(struct_type));
    attached_to_ = NULL;
    traits::init(this);
  }

  static void Clear(struct_type* s) { traits::clear(s); }

  struct_type* attached_to_;
};

struct AcfEnvironmentSettingsTraits {
  using struct_type = acf_environment_settings_t;

  static inline void init(struct_type* s) { s->size = sizeof(struct_type); }

  static inline void clear(struct_type* s) {
    acf_string_clear(&s->command_line);
    acf_string_clear(&s->user_data_dir);
    s->no_sandbox = false;
  }

  static inline void set(const struct_type* src,
                         struct_type* target,
                         bool copy) {
    acf_string_set(src->command_line.str, src->command_line.length,
                   &target->command_line, copy);
    acf_string_set(src->user_data_dir.str, src->user_data_dir.length,
                   &target->user_data_dir, copy);
    target->no_sandbox = src->no_sandbox;
  }
};
using AcfEnvironmentSettings = AcfStructBase<AcfEnvironmentSettingsTraits>;

struct AcfBrowserCreateParamsTraits {
  using struct_type = acf_browser_create_params_t;

  static inline void init(struct_type* s) {
    s->size = sizeof(struct_type);
    s->parent = nullptr;
    s->visible = true;
    s->x = 0;
    s->y = 0;
    s->width = 100;
    s->height = 100;
  }

  static inline void clear(struct_type* s) {}

  static inline void set(const struct_type* src,
                         struct_type* target,
                         bool copy) {
    memcpy(target, src, sizeof(struct_type));
  }
};
using AcfBrowserCreateParams = AcfStructBase<AcfBrowserCreateParamsTraits>;

///
/// Class representing a a keyboard event.
///
class AcfKeyEvent : public acf_key_event_t {
 public:
  AcfKeyEvent() : acf_key_event_t{} {}
  AcfKeyEvent(const acf_key_event_t& r) : acf_key_event_t(r) {}
};

///
/// Class representing a mouse event.
///
class AcfMouseEvent : public acf_mouse_event_t {
 public:
  AcfMouseEvent() : acf_mouse_event_t{} {}
  AcfMouseEvent(const acf_mouse_event_t& r) : acf_mouse_event_t(r) {}
};

///
/// Class defined browser settings wrapper
///
class AcfBrowserSettings : public acf_browser_settings_t {
 public:
  AcfBrowserSettings() : acf_browser_settings_t{} {}
  AcfBrowserSettings(const acf_browser_settings_t& r)
      : acf_browser_settings_t(r) {}
};

#endif  // ACF_TYPES_WRAPPERS_H_