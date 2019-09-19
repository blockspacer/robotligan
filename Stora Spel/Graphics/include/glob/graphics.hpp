#ifndef GLOB_GRAPHICS_HPP_
#define GLOB_GRAPHICS_HPP_

#ifdef MAKEDLL
#define EXPORT __declspec(dllexport)
#else
#define EXPORT __declspec(dllimport)
#endif

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>

namespace glob {

typedef unsigned long ModelHandle;
typedef unsigned long Font2DHandle;
//typedef unsigned long TextureHandle;

/*
 * Initialize renderer.
 * Must be called before other functions.
 */
EXPORT void Init();

/*
 * Returns a model handle for the specified model file.
 * Skips loading if model is loaded.
 */
EXPORT ModelHandle GetModel(const std::string& filepath);



EXPORT Font2DHandle GetFont(const std::string& filepath);

/*
 * Returns a texture handle for the specified image file.
 * Skips loading if image is loaded.
EXPORT TextureHandle GetTexture(const std::string& filepath);
 */

/*
 * Submit a model to be rendered.
 */
EXPORT void Submit(ModelHandle model_h, glm::vec3 pos);
EXPORT void Submit(ModelHandle model_h, glm::mat4 transform);

EXPORT void Submit(Font2DHandle font_h, glm::vec2 pos, unsigned int size,
                   std::string text, glm::vec4 color = glm::vec4(1,1,1,1));

/*
 * Render all items submitted this frame
 */
EXPORT void Render();

}  // namespace glob

#endif  // GLOB_GRAPHICS_HPP_