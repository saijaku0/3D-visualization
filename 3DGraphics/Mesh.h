#pragma once
#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glad/glad.h>

class Shader;

struct Mesh {
    unsigned int VBO, VAO;
    int vertexCount;

    Mesh(const std::vector<float>& vertices) {
        vertexCount = vertices.size() / 6;

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
    }

    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    Mesh(Mesh&& other) noexcept : VBO(other.VBO), VAO(other.VAO), vertexCount(other.vertexCount) {
        other.VBO = 0;
        other.VAO = 0;
    }

    void Draw(const Shader& shader) const {
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, vertexCount);
        glBindVertexArray(0);
    }
};

#endif // MESH_H