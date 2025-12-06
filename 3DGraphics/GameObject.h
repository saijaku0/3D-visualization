#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <memory>

#include "Component.h"
#include "Transform.h"

class GameObject {
    Transform m_transform;
    std::vector<std::unique_ptr<Component>> m_component;

public:
    GameObject();
    virtual ~GameObject() = default;

    template<typename T>
    T* GetComponent() const;
    template<typename T>
    std::vector<T*> getComponents();

    void AddComponent(std::unique_ptr<Component> component);
    
};

template<typename T>
T* GameObject::GetComponent() const {
    for (auto& component : m_component) {
        if (dynamic_cast<T*>(component.get()))
            return dynamic_cast<T*>(component.get());
    }
    return nullptr;
}

template<typename T>
std::vector<T*> GameObject::getComponents() {
    std::vector<T*> components;
    for (auto& component : this->components) {
        if (dynamic_cast<T*>(component)) {
            components.push_back(dynamic_cast<T*>(component));
        }
    }
    return components;
}

#endif