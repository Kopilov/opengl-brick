#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;  // we store the path of the texture to compare with other textures
};

class Shader {
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

class Mesh {
    public:
        /*  Mesh Data  */
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        /*  Functions  */
        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader shader);
    private:
        /*  Render data  */
        unsigned int VAO, VBO, EBO;
        /*  Functions    */
        void setupMesh();
};

class Model {
    public:
        /*  Functions   */
        Model(std::string path) {
            loadModel(path);
        }
        void Draw(Shader shader);
    private:
        /*  Model Data  */
        std::vector<Mesh> meshes;
        std::string directory;
        /*  Functions   */
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                             std::string typeName);
};

#endif // LEARNOPENGL_MESH_H
