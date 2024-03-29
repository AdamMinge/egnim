/* ----------------------------------- egnim -------------------------------- */
#include <egnim/engine/core/context.h>
#include <egnim/engine/physics/physics_world.h>
#include <egnim/engine/physics/physics_body.h>
#include <egnim/engine/physics/physics_shape.h>
#include <egnim/engine/events/event_dispatcher.h>
#include <egnim/engine/scene/scene_node.h>
#include <egnim/engine/scene/camera_manager.h>
/* ----------------------------------- Local -------------------------------- */
#include "boxes_state.h"
/* -------------------------------------------------------------------------- */

BoxesState::BoxesState(egnim::core::StateStack& state_stack, egnim::core::Context& context) :
  egnim::scene::SceneState(state_stack, context)
{

}

BoxesState::~BoxesState() = default;

std::unique_ptr<egnim::scene::Node> BoxesState::createSpriteNode(const sf::Vector2f& position,
  const sf::Texture& texture, const egnim::physics::PhysicsMaterial& material, egnim::physics::PhysicsBody::Type type)
{
  // get needed values
  auto& scene_node = getSceneNode();
  auto& physics_world = scene_node.getPhysicsWorld();

  // create sprite / physics_body / physics_shape for node
  auto node = egnim::scene::SpriteNode::create();
  auto physics_body = egnim::physics::PhysicsBody::create();
  auto physics_shape = egnim::physics::PhysicsShapeBox::create(
    sf::Vector2f(static_cast<float>(texture.getSize().x),
                 static_cast<float>(texture.getSize().y)), sf::Vector2f(0,0));

  // set shape material
  physics_shape->setPhysicsMaterial(material);

  // attach shape to body and body to node
  physics_body->attachComponent(std::move(physics_shape));

  // set node properties
  node->setTexture(texture);
  physics_body->setOrigin(static_cast<float>(texture.getSize().x) / 2.f, static_cast<float>(texture.getSize().y) / 2.f);
  physics_body->setPosition(position);
  physics_body->setType(type);

  physics_body->attachChild(std::move(node));
  return physics_body;
}

void BoxesState::createBox(const sf::Vector2f& position)
{
  // create box
  auto& scene_node = getSceneNode();
  scene_node.attachChild(createSpriteNode(
    position, scene_node.getContext().getTextureHolder().get("box"),
    egnim::physics::PhysicsMaterial(1.0f, 0.0f, 0.7f, 1.0f),
    egnim::physics::PhysicsBody::Type::DynamicBody
    ));
}

void BoxesState::createFloor(const sf::Vector2f& position)
{
  // create floor
  auto& scene_node = getSceneNode();
  scene_node.attachChild(createSpriteNode(
    position, scene_node.getContext().getTextureHolder().get("floor"),
    egnim::physics::PhysicsMaterial(0.0f, 0.0f, 0.2f, 1.0f),
    egnim::physics::PhysicsBody::Type::StaticBody
  ));
}

void BoxesState::createCamera(const sf::Vector2f& position, const sf::FloatRect& rect, std::string_view name)
{
  // create camera
  auto& scene_node = getSceneNode();
  auto camera_node = egnim::scene::CameraNode::create();
  camera_node->setSize(static_cast<sf::Vector2f>(scene_node.getContext().getRenderWindow().getSize()));
  camera_node->setPosition(position);
  camera_node->setViewport(rect);
  camera_node->setEnabled(true);
  camera_node->setName(name);

  scene_node.attachChild(std::move(camera_node));
}

void BoxesState::mouseButtonPressed(const egnim::events::MouseButtonPressedEvent& pressed_button_event)
{
  auto& scene_node = getSceneNode();

  if(pressed_button_event.getButton() == sf::Mouse::Button::Left)
  {
    // spawn box on left mouse button click
    auto& camera_manager = scene_node.getCameraManager();
    auto coordinate = camera_manager.mapPixelToCoords(pressed_button_event.getPosition(),
                                                      camera_manager.getCameraNode(pressed_button_event.getPosition()));

    createBox(coordinate);
  }
}

void BoxesState::keyboardKeyPressed(const egnim::events::KeyboardKeyPressedEvent& pressed_key_event)
{
  auto& scene_node = getSceneNode();
  auto camera_move = sf::Vector2f(0.0f, 0.0f);

  // move camera depend on second key pressed ( alt / ctrl )
  if(pressed_key_event.getKey() == sf::Keyboard::Up) camera_move.y += 10.0f;
  if(pressed_key_event.getKey() == sf::Keyboard::Down) camera_move.y -= 10.0f;
  if(pressed_key_event.getKey() == sf::Keyboard::Left) camera_move.x += 10.0f;
  if(pressed_key_event.getKey() == sf::Keyboard::Right) camera_move.x -= 10.0f;

  if(pressed_key_event.isAltPressed())
    scene_node.findChildByName("camera_1")->move(camera_move);
  if(pressed_key_event.isControlPressed())
    scene_node.findChildByName("camera_2")->move(camera_move);
}

void BoxesState::windowResized(const egnim::events::WindowResizeEvent& window_resize_event)
{
  auto& scene_node = getSceneNode();
  scene_node.findChildByName<egnim::scene::CameraNode>("camera_1")->setSize(
    static_cast<sf::Vector2f>(window_resize_event.getSize()));
}

void BoxesState::onActive()
{
  // init resources
  getContext().getTextureHolder().loadFromFile("box", "box.png",
                                          sf::IntRect(5, 5, 22, 22));
  getContext().getTextureHolder().loadFromFile("floor", "floor.png",
                                          sf::IntRect(50, 50, 400, 50));

  // connect listener
  m_mouse_listener.setMouseButtonPressedEventCallback([this](auto&& event){ this->mouseButtonPressed(event); });
  getContext().getEventDispatcher().addEventListener(std::addressof(m_mouse_listener), -1);

  m_keyboard_listener.setKeyboardKeyPressedEventCallback([this](auto&& event){ this->keyboardKeyPressed(event); });
  getContext().getEventDispatcher().addEventListener(std::addressof(m_keyboard_listener), -1);

  m_window_listener.setWindowResizeEventCallbackCallback([this](auto&& event){ this->windowResized(event); });
  getContext().getEventDispatcher().addEventListener(std::addressof(m_window_listener), -1);

  // init scene
  auto& scene_node = getSceneNode();
  auto& physics_world = scene_node.getPhysicsWorld();

  physics_world.setGravity(sf::Vector2f(0, 9.8f));

  createFloor(sf::Vector2f(300, 500));

  createCamera(sf::Vector2f(300, 500),
               sf::FloatRect(0.0, 0.0, 0.5, 1.0),"camera_1");
  createCamera(sf::Vector2f(300, 500),
               sf::FloatRect(0.5, 0.0, 0.5, 1.0),"camera_2");
}

void BoxesState::onInactive()
{
  // remove resources
  getContext().getTextureHolder().remove("box");
  getContext().getTextureHolder().remove("floor");

  // disconnect listener
  getContext().getEventDispatcher().removeEventListener(std::addressof(m_mouse_listener));
  getContext().getEventDispatcher().removeEventListener(std::addressof(m_keyboard_listener));
  getContext().getEventDispatcher().removeEventListener(std::addressof(m_window_listener));
}


