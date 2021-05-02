/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/core/layer.h>
#include <egnim/engine/core/group_layer.h>
/* -------------------------------------------------------------------------- */

namespace egnim::core {

Layer::Layer(Type type) :
  m_type(type),
  m_parent(nullptr),
  m_visible(true)
{

}

Layer::~Layer() = default;

Layer::Type Layer::getType() const
{
  return m_type;
}

void Layer::setVisible(bool visible)
{
  m_visible = visible;
}

bool Layer::isVisible() const
{
  return m_visible;
}

bool Layer::isHidden() const
{
  return !m_visible;
}

GroupLayer* Layer::parent()
{
  return m_parent;
}

const GroupLayer* Layer::parent() const
{
  return m_parent;
}

std::list<const Layer*> Layer::getSiblings() const
{
  auto siblings = std::list<const Layer*>{};
  if(m_parent)
  {
    for(auto& layer : m_parent->getLayers())
      siblings.push_back(layer.get());
  }

  return siblings;
}

void Layer::setParent(GroupLayer* parent)
{
  m_parent = parent;
}

} // namespace egnim::core
