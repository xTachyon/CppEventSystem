#pragma once

#include <map>
#include <vector>
#include <memory>
#include <functional>
#include "event.hpp"

struct EventInformation {
  using function_type = void(*)(void*, void*);
  using deleter = void(*)(void*);

  function_type handler_function;
  std::unique_ptr<void, void(*)(void*)> handler;

  EventInformation(function_type handler_function, void* handler, deleter deleter);

  void operator()(void* event);
};

class EventManager {
public:
  template <typename T>
  using std_function_event = std::function<void(T&)>;

  template <typename T>
  void register_event(std_function_event<T> handler);

  void fire(Event& event);
private:
  using map_type = std::map<int32, std::vector<EventInformation>>;

  map_type map;

  template <typename T>
  static EventManager::std_function_event<T>* get_handler(void* ptr);
  template <typename T>
  static void actual_handler(void* event_ptr, void* handler_ptr);
  template <typename T>
  static void handler_deleter(void* handler_ptr);
};

template <typename T>
void EventManager::register_event(EventManager::std_function_event<T> handler) {
  EventManager::std_function_event<T>* ptr = new EventManager::std_function_event<T>(std::move(handler));
  map[T::event_id].push_back(EventInformation(actual_handler<T>, ptr, handler_deleter<T>));
}

template <typename T>
EventManager::std_function_event<T>* EventManager::get_handler(void* ptr) {
  return reinterpret_cast<EventManager::std_function_event<T>*>(ptr);
}

template <typename T>
void EventManager::actual_handler(void* event_ptr, void* handler_ptr) {
  auto& event = *reinterpret_cast<T*>(event_ptr);
  auto& handler = *get_handler<T>(handler_ptr);
  handler(event);
}

template <typename T>
void EventManager::handler_deleter(void* handler_ptr) {
  auto handler = get_handler<T>(handler_ptr);
  delete handler;
}
