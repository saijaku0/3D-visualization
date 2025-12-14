#include "EditorManager.h"
#include "GuiManager.h" 
#include <imgui.h>

void EditorManager::Init(GLFWwindow* window) {
    GuiManager::Init(window);
}

void EditorManager::Draw(Scene* scene) {
    GuiManager::Begin();
    
    const ImGuiViewport* viewPort = ImGui::GetMainViewport();
    ImGui::DockSpaceOverViewport(0, viewPort);

    ImGui::Begin("Scene Hierarchy");
    if (scene) {
        ImGui::Text("Player");
        ImGui::Text("Sphere");
        ImGui::Text("Light");
    }
    ImGui::End();

    ImGui::Begin("Inspector");
    ImGui::Text("Object Properties");
    ImGui::End();

    ImGui::Begin("Logs");
    ImGui::Text("System initialized...");

    if (scene) {
        ImGui::Text("Scene is active");
    }

    ImGui::End();

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Viewport");

    if (scene) {
        ImVec2 viewportSize = ImGui::GetContentRegionAvail();

        if (viewportSize.x != scene->GetWidth() || viewportSize.y != scene->GetHeight()) {
            scene->OnResize(viewportSize.x, viewportSize.y);
        }

        unsigned int glTextureID = scene->GetSceneTexture();       

        ImGui::Image(
            (ImTextureID)glTextureID,
            viewportSize,
            ImVec2(0, 1),
            ImVec2(1, 0)
        );
    }

    ImGui::End();
    ImGui::PopStyleVar();

    GuiManager::End();
}

void EditorManager::Shutdown() {
    GuiManager::Shutdown();
}