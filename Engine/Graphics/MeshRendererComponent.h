#pragma once
#include <memory>
#include "../Core/Component.h"
#include "../Core/GameObject.h"

class Mesh;

class MeshRendererComponent : public Component {
public:
	std::shared_ptr<Mesh> mesh;

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	MeshRendererComponent(GameObject* owner) : Component(owner) {}
};