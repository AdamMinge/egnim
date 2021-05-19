#ifndef PHYSICS_BODY_H
#define PHYSICS_BODY_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <memory>
#include <list>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
/* -------------------------------------------------------------------------- */

class b2Body;
class b2Fixture;
struct b2FixtureDef;

namespace egnim::physics
{

  class PhysicsWorld;
  class PhysicsShape;
  class PhysicsJoint;

  class EGNIM_UTILITY_API PhysicsBody : public scene::Node
  {
    EGNIM_CLASS(PhysicsBody, Node)

    friend PhysicsWorld;
    friend PhysicsShape;
    friend PhysicsJoint;

  public:
    enum class Type;

  public:
    explicit PhysicsBody(Type type);
    ~PhysicsBody() override;

    PhysicsBody(const PhysicsBody&) = delete;
    PhysicsBody(PhysicsBody&&) = delete;

    PhysicsBody& operator=(const PhysicsBody&) = delete;
    PhysicsBody& operator=(PhysicsBody&&) = delete;

    [[nodiscard]] PhysicsWorld* getPhysicsWorld();
    [[nodiscard]] const PhysicsWorld* getPhysicsWorld() const;

    void setLinearVelocity(const sf::Vector2f& linear_velocity);
    [[nodiscard]] sf::Vector2f getLinearVelocity() const;

    void setAngularVelocity(float omega);
    [[nodiscard]] float getAngularVelocity() const;

    void applyForce(const sf::Vector2f& force, const sf::Vector2f& point, bool awake = true);
    void applyForceToCenter(const sf::Vector2f& force, bool awake = true);

    void applyTorque(float torque, bool awake = true);
    void applyLinearImpulse(const sf::Vector2f& impulse, const sf::Vector2f& point, bool awake = true);
    void applyLinearImpulseToCenter(const sf::Vector2f& impulse, bool awake = true);
    void applyAngularImpulse(float impulse, bool awake = true);

    [[nodiscard]] float getMass() const;
    [[nodiscard]] float getInertia() const;

    void setType(Type type);
    [[nodiscard]] Type getType() const;

    void setLinearDamping(float linear_damping);
    [[nodiscard]] float getLinearDamping() const;

    void setAngularDamping(float angular_damping);
    [[nodiscard]] float getAngularDamping() const;

    void setBullet(bool bullet = true);
    [[nodiscard]] bool isBullet() const;

    void setGravityScale(float gravity_scale);
    [[nodiscard]] float getGravityScale() const;

    void attachPhysicsShape(std::unique_ptr<PhysicsShape> physics_shape);
    std::unique_ptr<PhysicsShape> detachPhysicsShape(const PhysicsShape& physics_shape);
    [[nodiscard]] const std::list<std::unique_ptr<PhysicsShape>>& getPhysicsShapes() const;
    [[nodiscard]] const std::list<PhysicsJoint*>& getPhysicsJoints() const;

    void setAwake(bool awake);
    [[nodiscard]] bool isAwake() const;

    void setEnabled(bool enabled);
    [[nodiscard]] bool isEnabled() const;

    void accept(scene::SceneVisitor& visitor) override;

  private:
    void onEnter() override;
    void onExit() override;

    void attachPhysicsJoint(PhysicsJoint* physics_joint);
    void detachPhysicsJoint(PhysicsJoint* physics_joint);

    void createInternalBody(Type type);
    void destroyInternalBody();

    void beforeSimulation();
    void afterSimulation();

    [[nodiscard]] b2Fixture* createInternalFixture(const b2FixtureDef* b2_fixture_def);
    void destroyInternalFixture(b2Fixture* b2_fixture);

    [[nodiscard]] const b2Body* getInternalBody() const;
    [[nodiscard]] b2Body* getInternalBody();

  private:
    Type m_type;
    PhysicsWorld* m_physics_world;
    b2Body* m_b2_body;
    std::list<std::unique_ptr<PhysicsShape>> m_physics_shapes;
    std::list<PhysicsJoint*> m_physics_joints;
  };

  enum class PhysicsBody::Type
  {
    StaticBody = 0,
    KinematicBody = 1,
    DynamicBody = 2
  };

}

#endif //PHYSICS_BODY_H
