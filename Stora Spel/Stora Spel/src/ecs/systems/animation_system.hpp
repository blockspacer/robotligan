#ifndef ANIMATION_SYSTEM_HPP_
#define ANIMATION_SYSTEM_HPP_

#include <entt.hpp>

#include <iostream>

#include "glob/Animation.hpp"
#include "glob/joint.hpp"

#include "ecs/components.hpp"
#include "shared/shared.hpp"

#include <math.h>
#include "glm/gtx/matrix_interpolation.hpp"
#include "glm/gtx/perpendicular.hpp"

class Engine;

class AnimationSystem {
 private:
  glm::vec3 front = glm::vec3(1.f, 0.f, 0.f);
  glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
  glm::vec3 left = glm::vec3(0.f, 0.f, 1.f);

  float time_ = 0;
  std::string slide_anims_[4] = {"SlideF", "SlideB", "SlideR", "SlideL"};
  std::string look_anims_[4] = {"LookUp", "LookDown", "LookRight", "LookLeft"};

  Engine* engine_;

 public:
  void Init(Engine* engine);

  void GetDefaultPose(glm::mat4 parent, glob::Joint* bone,
                      std::vector<glob::Joint>* armature,
                      glm::mat4 globalInverseTransform);

  bool IsAChildOf(int parent, int lookFor, AnimationComponent* ac);

  bool IsIncluded(int bone, std::vector<int>* included,
                  std::vector<int>* excluded);
  bool IsExcluded(int bone, std::vector<int>* excluded);

  int GetAnimationByName(std::string name, AnimationComponent* ac);

  int GetActiveAnimationByName(std::string name, AnimationComponent* ac);

  void PlayAnimation(std::string name, float speed, AnimationComponent* ac,
                     char priority, float strength, int mode,
                     std::vector<int>* bodyInclude = nullptr,
                     std::vector<int>* bodyExclude = nullptr);

  void StopAnimation(std::string name, AnimationComponent* ac);

  void StrengthModulator(AnimationComponent* ac);

  void UpdateEntities(entt::registry& registry, float dt);

  void ReceiveGameEvent(GameEvent event);

  void UpdateAnimations(entt::registry& registry, float dt);

  glm::vec3 InterpolateVector(float time, std::vector<aiVectorKey>* keys);
  glm::quat InterpolateQuat(float time, std::vector<aiQuatKey>* keys);

  void interpolatePRS(glm::vec3& j_pos, glm::quat& j_rot, glm::vec3& j_scale,
                      glm::vec3 pos, glm::quat rot, glm::vec3 scale, float str);

  void setPRS(glm::vec3& j_pos, glm::quat& j_rot, glm::vec3& j_scale,
              glm::vec3 pos, glm::quat rot, glm::vec3 scale);

  void Reset(entt::registry& registry);

  enum ANIM_MODES { LOOP, MUTE_ALL, PARTIAL_MUTE };
};

#endif  // ANIMATION_SYSTEM_HPP_
