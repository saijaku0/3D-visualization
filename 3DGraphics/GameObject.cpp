#include "GameObject.h"

GameObject::GameObject()
{ }

Transform* GameObject::GetTransformPtr() { return &m_transform; }

void GameObject::AddComponent(std::unique_ptr<Component> component) {
	m_component.push_back(std::move(component));
}