#ifndef PARTICLE_COMPONENT_HPP_
#define PARTICLE_COMPONENT_HPP_

#include <glob/graphics.hpp>
#include <vector>

struct ParticleComponent {
  std::vector<glob::ParticleSystemHandle> handles;
  std::vector<glm::vec3> offsets;
};

#endif  // PARTICLE_COMPONENT_HPP_