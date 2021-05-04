#ifndef SCENE_SERIALIZER_H
#define SCENE_SERIALIZER_H

/* --------------------------------- Standard ------------------------------- */
#include <variant>
#include <memory>
#include <ios>
/* ----------------------------------- Local -------------------------------- */
#include <egnim/engine/export.h>
#include <egnim/engine/scene/scene_visitor.h>
/* -------------------------------------------------------------------------- */

namespace egnim::scene::priv
{
  class SceneSerializerImpl;
}

namespace egnim::scene
{

  class EGNIM_UTILITY_API SceneSerializer : public SceneVisitor
  {
    using istream = std::reference_wrapper<std::istream>;
    using ostream = std::reference_wrapper<std::ostream>;

  public:
    enum class Action;
    enum class Format;

  public:
    explicit SceneSerializer(Format format, std::ostream& stream);
    explicit SceneSerializer(Format format, std::istream& stream);
    ~SceneSerializer();

    void visitAnimatedSpriteNode(AnimatedSpriteNode& animated_sprite_node) override;
    void visitLabelNode(LabelNode& label_node) override;
    void visitMusicNode(MusicNode& music_node) override;
    void visitSceneNode(SceneNode& scene_node) override;
    void visitSoundNode(SoundNode& sound_node) override;
    void visitSpriteNode(SpriteNode& sprite_node) override;
    void visitCameraNode(CameraNode& camera_node) override;

    Format getFormat();
    Action getAction();

  protected:
    priv::SceneSerializerImpl& getImpl();

  private:
    Format m_format;
    Action m_action;

    std::variant<istream, ostream> m_stream;
    std::unique_ptr<priv::SceneSerializerImpl> m_impl;
  };

  enum class SceneSerializer::Format
  {
    Json,
  };

  enum class SceneSerializer::Action
  {
    Serialize,
    Deserialize,
  };

} // namespace egnim::scene

#endif //SCENE_SERIALIZER_H