#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"

void GameObject::Draw(const Shader& shader) const {
    if (!mesh) {
        return;
    }

    glm::mat4 modelMatrix = transform.GetModelMatrix();

    shader.setMat4("model", modelMatrix);

    shader.setVec3("objectColor", color);

    mesh->Draw(shader);
}