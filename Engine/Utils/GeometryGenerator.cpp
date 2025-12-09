#include "GeometryGenerator.h"

#include <vector>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

std::shared_ptr<Mesh> GeometryGenerator::CreatePyramid() {
    std::vector<Vertex> vertices = {
        { {0.0f,  0.5f,  0.0f},  {0.0f, 0.5f,  0.8f}, {0.5f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f},  {0.0f, 0.5f,  0.8f}, {0.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.0f, 0.5f,  0.8f}, {1.0f, 0.0f} },

        { { 0.0f,  0.5f,  0.0f},  {0.8f, 0.5f, -0.5f}, {0.5f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.8f, 0.5f, -0.5f}, {0.0f, 0.0f} },
        { { 0.0f, -0.5f, -0.5f},  {0.8f, 0.5f, -0.5f}, {1.0f, 0.0f} },

        { { 0.0f,  0.5f,  0.0f},  {-0.8f, 0.5f, -0.5f}, {0.5f, 1.0f} },
        { { 0.0f, -0.5f, -0.5f},  {-0.8f, 0.5f, -0.5f}, {0.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f},  {-0.8f, 0.5f, -0.5f}, {1.0f, 0.0f} },

        { {-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
        { { 0.0f, -0.5f, -0.5f},  {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f} },

        { {-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f} },
        { { 0.0f, -0.5f, -0.5f},  {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f} }
    };

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size(); i++) indices.push_back(i);

    std::vector<Texture> textures;

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}

std::shared_ptr<Mesh> GeometryGenerator::CreateCube() {
    std::vector<Vertex> vertices = {
        { {-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f} },
        { {-0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f} },

        { {-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {1.0f, 1.0f} },
        { {-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f,  1.0f},  {0.0f, 0.0f} },

        { {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 0.0f} },
        { {-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 1.0f} },
        { {-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 1.0f} },
        { {-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {0.0f, 0.0f} },
        { {-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f},  {1.0f, 0.0f} },

        { { 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f} },
        { { 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f} },
        { { 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f} },
        { { 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f} },

        { {-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f} },
        { { 0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f} },
        { { 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f} },
        { {-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f} },
        { {-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f} },

        { {-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f} },
        { {-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f} },
        { { 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f} },
        { { 0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f} },
        { {-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f} }
    };

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < vertices.size(); i++) indices.push_back(i);

    std::vector<Texture> textures;

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}

std::shared_ptr<Mesh> GeometryGenerator::CreateSphere(float radius, int sectors, int stacks) {
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    float x, y, z, xy;                              
    float nx, ny, nz, lengthInv = 1.0f / radius;    
    float s, t;                                     

    float sectorStep = 2 * M_PI / sectors;
    float stackStep = M_PI / stacks;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stacks; ++i) {
        stackAngle = M_PI / 2 - i * stackStep;        
        xy = radius * cosf(stackAngle);             
        z = radius * sinf(stackAngle);              

        for (int j = 0; j <= sectors; ++j) {
            sectorAngle = j * sectorStep;           

            x = xy * cosf(sectorAngle);             
            y = xy * sinf(sectorAngle);            
            vertices.push_back(Vertex{ glm::vec3(x, y, z) });

            nx = x * lengthInv;
            ny = y * lengthInv;
            nz = z * lengthInv;
            vertices.back().Normal = glm::vec3(nx, ny, nz);

            s = (float)j / sectors;
            t = (float)i / stacks;
            vertices.back().TexCoords = glm::vec2(s, t);
        }
    }

    int k1, k2;
    for (int i = 0; i < stacks; ++i) {
        k1 = i * (sectors + 1);    
        k2 = k1 + sectors + 1;   

        for (int j = 0; j < sectors; ++j, ++k1, ++k2) {
            if (i != 0) {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1)) {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

    std::vector<Texture> textures;

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices), std::move(textures));
}