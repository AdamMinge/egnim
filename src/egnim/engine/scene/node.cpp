/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/core/command.h>
#include <egnim/engine/scene/component_container.h>
#include <egnim/engine/scene/component.h>
#include <egnim/engine/scene/camera.h>
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
  m_camera_mask(Camera::CameraFlag::DEFAULT),
  m_name("")
{

}

Node::~Node() = default;

void Node::attachChild(std::unique_ptr<Node> node)
{
  node->setParent(this);
  m_children.push_back(std::move(node));
}

std::unique_ptr<Node> Node::detachChild(const Node &node)
{
  auto found = std::find_if(m_children.begin(), m_children.end(), [&node](auto &child)
  {
    return child.get() == &node;
  });

  if (found == m_children.end())
    return nullptr;

  auto child = std::move(*found);
  child->setParent(nullptr);
  m_children.erase(found);
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
  return m_components->take(component);
}

const ComponentContainer& Node::getComponentContainer() const
{
  assert(m_components);
  return *m_components;
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

Node* Node::getParent()
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

void Node::update(core::CommandQueue &command_queue, sf::Time dt)
{
  updateComponents(dt);
  updateCurrent(command_queue, dt);
  updateChildren(command_queue, dt);
}

void Node::onCommand(const core::Command &command, sf::Time dt)
{
  command(*this, dt);
  for (const auto &child : m_children)
    child->onCommand(command, dt);
}

void Node::updateCurrent(core::CommandQueue &command_queue, sf::Time dt)
{}

void Node::updateChildren(core::CommandQueue &command_queue, sf::Time dt)
{
  for (const auto &child : m_children)
    child->update(command_queue, dt);
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
  auto target_camera = Camera::getActiveCamera(target);
  return target_camera == nullptr || target_camera->getViewFlag() & m_camera_mask;
}

void Node::setParent(Node* parent)
{
  m_parent = parent;
}

} // namespace egnim::scene