#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <utility>
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
    unsigned int VBO, VAO, EBO;

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
public:
    Mesh(std::vector<Vertex>&& vertices, std::vector<unsigned int>&& indices, std::vector<Texture>&& textures);
    Mesh(Mesh&& other) noexcept;

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void Draw(const Shader& shader) const;
    unsigned int GetVAO() const;
private: 
    void SetupMesh();
};

#endif // MESH_H