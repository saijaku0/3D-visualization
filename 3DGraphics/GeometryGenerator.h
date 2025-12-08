#ifndef GEOMETRY_GENERATOR_H
#define GEOMETRY_GENERATOR_H

#include "Mesh.h"

#include <memory> 
#include <glm/glm.hpp>

class GeometryGenerator {
public:
    static std::shared_ptr<Mesh> CreateCube();

    static std::shared_ptr<Mesh> CreatePyramid();

    static std::shared_ptr<Mesh> CreateSphere(float radius = 0.5f, int sectors = 36, int stacks = 18);
};

#endif // GEOMETRY_GENERATOR_H