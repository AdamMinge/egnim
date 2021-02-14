#ifndef COMPONENT_H
#define COMPONENT_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */

namespace egnim::core
{
  class Node;
  class ComponentContainer;

  class Component
  {
    friend ComponentContainer;

  public:
    explicit Component();
    virtual ~Component();

    virtual void update(sf::Time dt) = 0;

  protected:
    void setOwner(Node* owner);
    Node* getOwner();

  private:
    Node* m_owner;
  };

} // namespace egnim::core

#endif //COMPONENT_H
