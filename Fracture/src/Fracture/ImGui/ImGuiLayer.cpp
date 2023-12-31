#include "frpch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "Fracture\Core\Core.h"
#include "Fracture\Core\Application.h"

#define IMGUI_IMPL_API
#include "backends\imgui_impl_glfw.h"
#include "backends\imgui_impl_opengl3.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>

namespace Fracture {

	ImGuiLayer::ImGuiLayer() :
		Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		/*io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;*/

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

    void ImGuiLayer::Begin()
    {
		FR_PROFILE_SCOPE("ImGuiLayer::Begin");
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
		FR_PROFILE_SCOPE("ImGuiLayer::End");
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();

		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());
		
		{
			FR_PROFILE_SCOPE("ImGuiLayer::End::Render");
			ImGui::Render();
		}
		{
			FR_PROFILE_SCOPE("ImGuiLayer::End::DrawData");
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}
		{
			FR_PROFILE_SCOPE("ImGuiLayer::End::Viewport");
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		}
    }

	void ImGuiLayer::OnImGuiRender()
	{
		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);*/
	}

}