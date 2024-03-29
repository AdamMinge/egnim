#ifndef SOUND_NODE_H
#define SOUND_NODE_H

/* ----------------------------------- SFML --------------------------------- */
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
/* --------------------------------- Standard ------------------------------- */
#include <string_view>
#include <functional>
#include <list>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/node.h>
#include <egnim/engine/core/resource_holder.h>
#include <egnim/engine/scene/node_factory.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene
{

  class EGNIM_UTILITY_API SoundNode : public Node, public RegisteredInNodeFactory<SoundNode>
  {
    EGNIM_CLASS(SoundNode, Node)

  public:
    struct Settings
    {
      float attenuation = 1.f;
      float min_distance = 1.f;
      float pitch = 1.f;
      float volume = 100.f;
    };

  public:
    [[nodiscard]] static std::unique_ptr<SoundNode> create();

  public:
    ~SoundNode() override;

    void setDefaultSettings(const Settings& settings);
    const Settings& getDefaultSettings() const;

    bool play(std::string_view id, sf::Vector2f position = sf::Vector2f(0.f, 0.f));
    bool play(std::string_view id, const Settings& settings, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

    bool playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                   sf::Vector2f position = sf::Vector2f(0.f, 0.f));
    bool playLoop(std::string_view id, const std::function<bool()>& stop_condition,
                   const Settings& settings, sf::Vector2f position = sf::Vector2f(0.f, 0.f));

    void stopAllSounds();
    void pauseAllSounds();
    void startAllSounds();

    void accept(SceneVisitor& visitor) override;

  protected:
    explicit SoundNode();

    void updateCurrent(sf::Time dt) override;

  private:
    void checkStopConditions();
    void removeStoppedSounds();
    void setAllSounds(sf::Sound::Status status);

  private:
    std::list<std::pair<sf::Sound, std::function<bool()>>> m_sounds;
    Settings m_default_settings;
  };

} // namespace egnim::scene

#endif //SOUND_NODE_H
