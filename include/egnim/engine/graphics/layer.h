#ifndef LAYER_H
#define LAYER_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <list>
#include <memory>
/* ---------------------------------- Local --------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class Tileset;
  class GroupLayer;

  class EGNIM_UTILITY_API Layer
  {
    friend GroupLayer;

  public:
    enum class Type;

  public:
    explicit Layer(Type type);
    virtual ~Layer();

    [[nodiscard]] Type getType() const;

    void setVisible(bool visible);
    [[nodiscard]] bool isVisible() const;
    [[nodiscard]] bool isHidden() const;

    [[nodiscard]] GroupLayer* parent();
    [[nodiscard]] const GroupLayer* parent() const;

    [[nodiscard]] std::list<const Layer*> getSiblings() const;

    [[nodiscard]] virtual bool isEmpty() const = 0;
    [[nodiscard]] virtual std::list<const Tileset*> getUsedTilesets() const = 0;
    [[nodiscard]] virtual bool isUsedTileset(const Tileset& tileset) const = 0;

    [[nodiscard]] virtual bool canMerge(const Layer& layer) const = 0;
    virtual bool merge(const sf::Vector2u& point, const Layer& layer) = 0;
    bool merge(const Layer& layer);

    [[nodiscard]] virtual std::unique_ptr<Layer> clone() const = 0;

  protected:
    void setParent(GroupLayer* parent);

    void initializeClone(Layer& node) const;

  private:
    Type m_type;
    GroupLayer* m_parent;
    bool m_visible;
  };

  enum class Layer::Type
  {
    TileLayer,
    GroupLayer
  };

} // namespace egnim::graphics

#endif //LAYER_H
