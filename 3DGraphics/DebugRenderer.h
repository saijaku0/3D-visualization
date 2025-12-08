#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>

class DebugRenderer {
public: 
	static void Init(std::shared_ptr<Shader> shader);

    static void RenderColliders(
        const std::vector<std::unique_ptr<GameObject>>& objects,
        const Camera* camera
    );

private: 
    static std::shared_ptr<Shader> m_shader;
};

