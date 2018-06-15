#include "event.hpp"

Event::~Event() = default;

int32 Event::last_event_id = 0;

int32 Event::new_event_id() {
  return last_event_id++;
}
