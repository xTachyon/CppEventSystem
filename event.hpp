#pragma once

#include <cstdint>
using int32 = int32_t;

class Event {
public:
  virtual ~Event() = 0;

  virtual int32 get_event_id() const = 0;

  static int32 new_event_id();
private:
  static int32 last_event_id;
};

template <typename T>
class BasicEvent : public Event {
public:
  static int32 event_id;

  int32 get_event_id() const override;
};

template <typename T>
int32 BasicEvent<T>::event_id = new_event_id();

template<typename T>
inline int32 BasicEvent<T>::get_event_id() const {
  return event_id;
}
