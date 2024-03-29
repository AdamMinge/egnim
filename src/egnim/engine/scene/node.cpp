/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/component_container.h>
#include <egnim/engine/scene/camera_node.h>
#include <egnim/engine/scene/component.h>
#include <egnim/engine/scene/camera_manager.h>
#include <egnim/engine/actions/action_manager.h>
#include <egnim/engine/actions/action.h>
/* --------------------------------- Standard ------------------------------- */
#include <cassert>
#include <regex>
#include <cmath>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

Node::Node() :
  m_parent(nullptr),
  m_components(std::make_unique<ComponentContainer>(*this)),
  m_action_manager(std::make_unique<actions::ActionManager>(*this)),
  m_camera_mask(CameraNode::CameraFlag::DEFAULT)
{

}

Node::~Node() = default;

void Node::attachChild(std::unique_ptr<Node> node)
{
  auto& node_ref = *node;
  m_children.push_back(std::move(node));
  node_ref.setParent(this);
  node_ref.onEnter();
}

std::unique_ptr<Node> Node::detachChild(const Node &node)
{
  auto found = std::find_if(m_children.begin(), m_children.end(), [&node](auto &child)
  {
    return child.get() == std::addressof(node);
  });

  if (found == m_children.end())
    return nullptr;

  auto child = std::move(*found);
  m_children.erase(found);
  child->setParent(nullptr);
  child->onExit();
  return child;
}

const std::vector<std::unique_ptr<Node>>& Node::getChildren() const
{
  return m_children;
}

void Node::attachComponent(std::unique_ptr<Component> component)
{
  assert(m_components);
  m_components->add(std::move(component));
}

std::unique_ptr<Component> Node::detachComponent(const Component &component)
{
  assert(m_components);
  auto detached_component = m_components->take(component);
  return detached_component;
}

const ComponentContainer& Node::getComponentContainer() const
{
  assert(m_components);
  return *m_components;
}

void Node::attachAction(std::unique_ptr<actions::Action> action)
{
  assert(m_action_manager);
  m_action_manager->attachAction(std::move(action));
}

std::unique_ptr<actions::Action> Node::detachAction(const actions::Action& action)
{
  assert(m_action_manager);
  return m_action_manager->detachAction(action);
}

const actions::ActionManager& Node::getActionManager() const
{
  assert(m_action_manager);
  return *m_action_manager;
}

void Node::setCameraMask(size_t mask, bool applyChildren)
{
  m_camera_mask = mask;

  if(applyChildren)
  {
    for (const auto &child : m_children)
      child->setCameraMask(mask, applyChildren);
  }
}

size_t Node::getCameraMask() const
{
  return m_camera_mask;
}

void Node::setName(std::string_view name)
{
  m_name = name;
}

std::string_view Node::getName() const
{
  return m_name;
}

float Node::getWorldRotation() const
{
  auto rotation = 0.f;
  for (const Node *node = this; node != nullptr; node = node->m_parent)
    rotation += node->getRotation();

  return fmodf(rotation, 360.0f);
}

sf::Vector2f Node::getWorldPosition() const
{
  return getWorldTransform() * sf::Vector2f{};
}

sf::Transform Node::getWorldTransform() const
{
  auto transform = sf::Transform::Identity;
  for (const Node *node = this; node != nullptr; node = node->m_parent)
    transform = node->getTransform() * transform;

  return transform;
}

SceneNode* Node::getScene()
{
  auto current_node = this;
  while(current_node->m_parent && !dynamic_cast<SceneNode*>(current_node))
    current_node = current_node->m_parent;

  return dynamic_cast<SceneNode*>(current_node);
}

const SceneNode* Node::getScene() const
{
  auto current_node = this;
  while(current_node->m_parent && !dynamic_cast<const SceneNode*>(current_node))
    current_node = current_node->m_parent;

  return dynamic_cast<const SceneNode*>(current_node);
}

Node* Node::getParent()
{
  return m_parent;
}

const Node* Node::getParent() const
{
  return m_parent;
}

Node* Node::getRoot()
{
  auto current_node = this;
  while(current_node->m_parent)
    current_node = current_node->m_parent;

  return current_node;
}

const Node* Node::getRoot() const
{
  auto current_node = this;
  while(current_node->m_parent)
    current_node = current_node->m_parent;

  return current_node;
}

NodeIterator Node::begin()
{
  return NodeIterator(this);
}

ConstNodeIterator Node::begin() const
{
  return ConstNodeIterator(this);
}

NodeIterator Node::end() // NOLINT(readability-convert-member-functions-to-static)
{
  return NodeIterator(nullptr);
}

ConstNodeIterator Node::end() const // NOLINT(readability-convert-member-functions-to-static)
{
  return ConstNodeIterator(nullptr);
}

Node* Node::findChildByName(std::string_view name)
{
  std::regex name_regex(name.begin(), name.end());
  for (const auto &child : m_children)
  {
    auto child_name = child->getName();
    if(std::regex_match(child_name.begin(), child_name.end(), name_regex))
      return child.get();
  }

  return nullptr;
}

void Node::update(sf::Time dt)
{
  updateComponents(dt);
  updateCurrent(dt);
  updateChildren(dt);
}

void Node::updateCurrent(sf::Time dt)
{
  m_action_manager->update(dt);
}

void Node::updateChildren(sf::Time dt)
{
  for (const auto &child : m_children)
    child->update(dt);
}

void Node::updateComponents(sf::Time dt)
{
  if(m_components)
    m_components->update(dt);
}

void Node::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();

  if(isVisibleByTarget(target))
    drawCurrent(target, states);

  drawChildren(target, states);
}

void Node::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {}

void Node::drawChildren(sf::RenderTarget &target, sf::RenderStates states) const
{
  for (const auto &child : m_children)
    child->draw(target, states);
}

bool Node::isVisibleByTarget(sf::RenderTarget& target) const
{
  assert(getScene());
  auto target_camera = getScene()->getCameraManager().getActiveCameraNode();
  return target_camera == nullptr || target_camera->getViewFlag() & m_camera_mask;
}

void Node::setParent(Node* parent)
{
  m_parent = parent;
}

void Node::onEnter()
{
  m_components->onEnter();
  for(auto& child : m_children)
    child->onEnter();
}

void Node::onExit()
{
  m_components->onExit();
  for(auto& child : m_children)
    child->onExit();
}

} // namespace egnim::scene
