#pragma once

class GameObject;

class Component {
	GameObject* m_owner;
public:
	Component(GameObject* owner) : m_owner(owner) {}
	virtual ~Component() = default;
};

