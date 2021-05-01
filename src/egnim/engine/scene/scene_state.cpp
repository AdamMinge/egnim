/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/scene/scene_state.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/core/context.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene {

SceneState::SceneState(core::StateStack& state_stack, core::Context& context) :
  core::State(state_stack, context),
  m_scene_node(std::make_unique<SceneNode>(context))
{

}

SceneState::~SceneState() = default;

void SceneState::draw()
{
  auto& render_target = getContext().getRenderWindow();
  render_target.draw(*m_scene_node);
}

void SceneState::update(sf::Time dt)
{
  m_scene_node->update(dt);
}

void SceneState::onActive()
{

}

void SceneState::onInactive()
{

}

void SceneState::onCreate()
{

}

void SceneState::onDestroy()
{

}

} // namespace egnim::scene