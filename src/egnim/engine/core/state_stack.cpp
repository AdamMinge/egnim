/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/core/state_stack.h>
#include <egnim/engine/core/state.h>
#include <egnim/engine/core/context.h>
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/events/state_event.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

StateStack::StateStack(Context& context) :
  m_context(context)
{

}

StateStack::~StateStack() = default;

void StateStack::draw()
{
  for(auto& state : m_states)
    state->draw();
  applyPendingChanges();
}

void StateStack::update(sf::Time dt)
{
  for(auto& state : m_states)
    state->update(dt);
  applyPendingChanges();
}

void StateStack::pushState(std::string_view state_id)
{
  m_pending_changes.push([this, state_id](){
    if(auto new_state = createState(state_id); new_state)
    {
      if(!m_states.empty())
      {
        m_states.back()->onInactive();
        m_context.getEventDispatcher().dispatchEvent(events::InactivatedState(*m_states.back()));
      }

      new_state->onActive();
      m_context.getEventDispatcher().dispatchEvent(events::ActivatedState(*new_state));

      m_states.push_back(std::move(new_state));
    }
  });
}

void StateStack::popState()
{
  m_pending_changes.push([this](){
    m_states.back()->onInactive();
    m_context.getEventDispatcher().dispatchEvent(events::InactivatedState(*m_states.back()));

    m_states.pop_back();

    if(!m_states.empty())
    {
      m_states.back()->onActive();
      m_context.getEventDispatcher().dispatchEvent(events::ActivatedState(*m_states.back()));
    }
  });
}

void StateStack::clearStates()
{
  m_pending_changes.push([this](){
    for(auto& state : m_states)
    {
      state->onInactive();
      m_context.getEventDispatcher().dispatchEvent(events::ActivatedState(*state));
    }
    m_states.clear();
  });
}

bool StateStack::empty()
{
  return m_states.empty();
}

std::unique_ptr<State> StateStack::createState(std::string_view state_id)
{
  if(m_factories.contains(state_id))
    return m_factories[state_id]();
  return nullptr;
}

void StateStack::applyPendingChanges()
{
  while(!m_pending_changes.empty())
  {
    auto& front_action = m_pending_changes.front();
    front_action();
    m_pending_changes.pop();
  }
}

} // namespace egnim::core
