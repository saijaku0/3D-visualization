#include "GameObject.h"

GameObject::GameObject()
{ }

void GameObject::AddComponent(std::unique_ptr<Component> component) {
	m_component.push_back(std::move(component));
}