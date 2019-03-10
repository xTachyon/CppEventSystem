#include <iostream>
#include <string>
#include "event.hpp"
#include "event_manager.hpp"

class PlayerJoinEvent : public BasicEvent<PlayerJoinEvent> {
public:
  std::string name;
  PlayerJoinEvent(std::string name);
};

PlayerJoinEvent::PlayerJoinEvent(std::string name)
  : name(name) {}

int main() {
  EventManager manager;
  std::function<void(PlayerJoinEvent&)> handler([](PlayerJoinEvent& event) {
    std::cout << "hello " << event.name;
  });

  manager.register_event(std::move(handler));
  PlayerJoinEvent event("tachyon");
  manager.fire(event);
  // salut
}