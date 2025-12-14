#pragma once
#include <memory>
#include "../Core/Component.h"
#include "../Core/GameObject.h"

class Mesh;

class MeshRendererComponent : public Component {
	std::shared_ptr<Mesh> mesh;
public:

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	MeshRendererComponent(GameObject* owner) : Component(owner) {}
	std::shared_ptr<Mesh> GetMesh() const { return mesh; }
	void SetMesh(std::shared_ptr<Mesh> newMesh) {
		this->mesh = newMesh;
	}
};