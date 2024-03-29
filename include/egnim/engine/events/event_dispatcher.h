#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

/* --------------------------------- Standard ------------------------------- */
#include <unordered_map>
#include <functional>
#include <cstdint>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{
  class Node;
}

namespace egnim::events
{

  namespace priv { class EventListenerVector; }
  class EventListener;
  class Event;

  class EGNIM_UTILITY_API EventDispatcher
  {
  public:
    explicit EventDispatcher();
    ~EventDispatcher();

    void addEventListener(EventListener* event_listener, scene::Node* node);
    void addEventListener(EventListener* event_listener, int fixed_priority);

    void removeEventListener(EventListener* event_listener);
    void removeEventListener(scene::Node* node, bool recursive = false);
    void removeEventListener(int32_t listen_events);

    void dispatchEvent(const Event& event);

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

  private:
    void visitEventListenerVectors(int32_t listen_events, const std::function<void(priv::EventListenerVector&)>& visitor);

  private:
    bool m_enabled;
    std::unordered_map<int32_t, std::unique_ptr<priv::EventListenerVector>> m_event_to_listeners;
  };

} // namespace egnim::events

#endif //EVENT_DISPATCHER_H
