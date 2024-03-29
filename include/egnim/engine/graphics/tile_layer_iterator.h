#ifndef TILE_LAYER_ITERATOR_H
#define TILE_LAYER_ITERATOR_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <iterator>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
/* -------------------------------------------------------------------------- */

namespace egnim::graphics
{

  class TileLayer;
  class Cell;

  class EGNIM_UTILITY_API TileLayerIterator
  {
    friend class TileLayer;

  public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using pointer           = const Cell*;
    using reference         = const Cell&;

    enum class IterationOrder;

  public:
    ~TileLayerIterator();

    TileLayerIterator(const TileLayerIterator&) = default;
    TileLayerIterator(TileLayerIterator&&) = default;

    TileLayerIterator& operator=(const TileLayerIterator&) = default;
    TileLayerIterator& operator=(TileLayerIterator&&) = default;

    [[nodiscard]] IterationOrder getIterationOrder() const;
    [[nodiscard]] sf::Vector2u getCurrentPoint() const;

    reference operator*() const;
    pointer operator->();

    TileLayerIterator& operator++();
    TileLayerIterator operator++(int); // NOLINT(cert-dcl21-cpp)

    bool operator==(const TileLayerIterator& other) const;
    bool operator!=(const TileLayerIterator& other) const;

  private:
    explicit TileLayerIterator(const TileLayer* tile_layer, IterationOrder iteration_order);
    explicit TileLayerIterator(const TileLayer* tile_layer, const sf::Vector2u& start_point, IterationOrder iteration_order);

    void advance();
    void setToPoint(const sf::Vector2u& point);
    void setToStart();
    void setToEnd();

    [[nodiscard]] sf::Vector2u getFirstPoint() const;
    [[nodiscard]] sf::Vector2u getLastPoint() const;

  private:
    const TileLayer* m_tile_layer;
    const Cell* m_current_cell;
    sf::Vector2u m_current_point;
    IterationOrder m_iteration_order;
  };

  enum class TileLayerIterator::IterationOrder
  {
    RightDown,
    RightUp,
    LeftDown,
    LeftUp
  };

} // namespace egnim::graphics

#endif //TILE_LAYER_ITERATOR_H
