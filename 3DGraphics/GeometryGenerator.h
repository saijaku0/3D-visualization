#ifndef GEOMETRY_GENERATOR_H
#define GEOMETRY_GENERATOR_H

#include "Mesh.h"
#include <vector>

class GeometryGenerator {
public: 
    static Mesh* CreateCube() {
        std::vector<float> vertices = {
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        return new Mesh(vertices);
    }

    static Mesh* CreatePyramid() {
        std::vector<float> vertices = {
            0.0f,  0.5f,  0.0f,     0.0f, 0.5f,  0.8f, 
           -0.5f, -0.5f,  0.5f,     0.0f, 0.5f,  0.8f, 
            0.5f, -0.5f,  0.5f,     0.0f, 0.5f,  0.8f, 

            0.0f,  0.5f,  0.0f,     0.8f, 0.5f, -0.5f, 
            0.5f, -0.5f,  0.5f,     0.8f, 0.5f, -0.5f, 
            0.0f, -0.5f, -0.5f,     0.8f, 0.5f, -0.5f, 

            0.0f,  0.5f,  0.0f,    -0.8f, 0.5f, -0.5f, 
            0.0f, -0.5f, -0.5f,    -0.8f, 0.5f, -0.5f, 
           -0.5f, -0.5f,  0.5f,    -0.8f, 0.5f, -0.5f, 

           -0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f,
            0.0f, -0.5f, -0.5f,     0.0f, -1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,     0.0f, -1.0f, 0.0f
        };
        return new Mesh(vertices);
    }

    static Mesh* CreateSphere(float radius = 1.0f, int sectorCount = 36, int stackCount = 18) {
        std::vector<float> vertices;

        float x, y, z, xy;
        float nx, ny, nz;
        float s, t;

        float sectorStep = 2 * 3.14159f / sectorCount;
        float stackStep = 3.14159f / stackCount;
        float sectorAngle, stackAngle;

        for (int i = 0; i <= stackCount; ++i) {
            stackAngle = 3.14159f / 2 - i * stackStep;
            xy = radius * cosf(stackAngle);
            z = radius * sinf(stackAngle);

            for (int j = 0; j <= sectorCount; ++j) {
                sectorAngle = j * sectorStep;

                x = xy * cosf(sectorAngle);
                y = xy * sinf(sectorAngle);

                nx = x / radius;
                ny = y / radius;
                nz = z / radius;

                s = (float)j / sectorCount;
                t = (float)i / stackCount;

                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(nx);
                vertices.push_back(ny);
                vertices.push_back(nz);
                vertices.push_back(s);
                vertices.push_back(t);
            }
        }

        return new Mesh(vertices);
    }
};

#endif // GEOMETRY_GENERATOR_H
