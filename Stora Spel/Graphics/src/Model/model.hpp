#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "mesh.hpp"

#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>
#include <glm/gtx/transform.hpp>

#include "glob/Animation.hpp"
#include "glob/joint.hpp"
#include "glob/mesh_data.hpp"
#include "material/material.hpp"
#include "shader.hpp"

namespace glob {

class Model {
 private:
  Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

  GLint TextureFromFile(const char* path, std::string directory,
                        aiTextureType type);

  void LoadModel(std::string path);
  void ProcessNode(aiNode* node, const aiScene* scene);
  std::string PrintArmature(Joint parent, int depth);
  Joint* MakeArmature(aiNode* node);

  std::vector<Texture> texture_loaded_;
  std::vector<Mesh> mesh_;
  std::vector<Texture> LoadMaterielTextures(aiMaterial* material,
                                            aiTextureType type,
                                            std::string type_name,
                                            int tex_slot);

  std::string filepath_;
  std::string directory_;

  glm::mat4 ConvertToGLM(aiMatrix4x4 aiMat) {
    return {aiMat.a1, aiMat.b1, aiMat.c1, aiMat.d1, aiMat.a2, aiMat.b2,
            aiMat.c2, aiMat.d2, aiMat.a3, aiMat.b3, aiMat.c3, aiMat.d3,
            aiMat.a4, aiMat.b4, aiMat.c4, aiMat.d4};
  }

  bool is_loaded_ = false;
  bool humanoid_ = false;

  bool use_gl_ = true;
  bool is_emissive_ = false;
  bool is_transparent_ = false;

  int num_diffuse_textures_ = 1;

  Material material_;
  float normal_map_scale_ = 1.f;
  float metallic_map_scale_= 1.f;
  float roughness_map_scale_ = 1.f;

 public:
  Model();
  Model(const std::string& path);
  ~Model();

  void LoadFromFile(const std::string& path);
  bool IsLoaded() { return is_loaded_; };

  void Draw(ShaderProgram& shader);

  float MaxDistance(glm::mat4 transform, glm::vec3 point);

  int GetNumDiffuseTextures() { return num_diffuse_textures_; }

  std::vector<Joint*> bones_;
  std::vector<Animation*> animations_;
  glm::mat4 globalInverseTransform_;

  glob::MeshData GetMeshData();

  bool IsEmissive() { return is_emissive_; }
  void SetTransparent(bool is_transparent) { is_transparent_ = is_transparent; }
  bool IsTransparent() { return is_transparent_; }
};

}  // namespace glob

#endif  // MODEL_HPP_
