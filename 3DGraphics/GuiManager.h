#pragma once

struct GLFWwindow;

class GuiManager {
public:
	static void Init(GLFWwindow* woindow);
	static void Begin();
	static void End();
	static void Shutdown();
};

