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
    std::vector<T*> GetComponents() const;

    Transform* GetTransformPtr() const;
    void AddComponent(std::unique_ptr<Component> component);
    
};

template<typename T>
T* GameObject::GetComponent() const {
    for (const auto& component : m_component) {
        if (T* specificComponent = dynamic_cast<T*>(component.get()))
            return specificComponent;
    }
    return nullptr;
}

template<typename T>
std::vector<T*> GameObject::GetComponents() const {
    std::vector<T*> components;
    for (const auto& component : m_component) {
        if (T* specificComponent = dynamic_cast<T*>(component.get())) {
            components.push_back(specificComponent);
        }
    }
    return components;
}

#endif