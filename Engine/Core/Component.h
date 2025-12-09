#pragma once

#include <cstdint>
#include <iostream>


class GameObject;

class Component {
	GameObject* m_owner = nullptr;
public:
	Component(GameObject* owner) : m_owner(owner) {}

	virtual ~Component() = default;
	virtual void Initialize() {}
	virtual void Update(float deltaTime) {}

	GameObject* GetOwner() const;
};

