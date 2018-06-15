#include "event_manager.hpp"

EventInformation::EventInformation(function_type handler_function, void* handler, deleter deleter)
  : handler_function(handler_function), handler(handler, deleter) {
}

void EventInformation::operator()(void* event) {
  handler_function(event, handler.get());
}

void EventManager::fire(Event& event) {
  auto iterator = map.find(event.get_event_id());
  if (iterator == map.end()) {
    return;
  }

  for (EventInformation& inf : iterator->second) {
    inf(&event);
  }
}
