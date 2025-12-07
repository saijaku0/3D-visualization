#pragma once
#include <memory>
#include "Component.h"
#include "GameObject.h"

class Mesh;

class MeshRendererComponent : public Component {
public:
	std::shared_ptr<Mesh> mesh;

	MeshRendererComponent(GameObject* owner) : Component(owner) {}
};