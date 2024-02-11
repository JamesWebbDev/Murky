#include "mkpch.h"

#include "window.hpp"
#include "../math/vec2Int.h"
#include "../rendering/shader.h"
#include "../rendering/model.h"

#include <GLFW/glfw3.h>
#include "../core/Log.h"

namespace Murky
{
	// Handles resizing the glViewport to match the Window's width and height
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	Window::~Window()
	{
		OnDestroy();
		glfwDestroyWindow(m_wnd);
		glfwTerminate();
	}

	bool Window::Init(int width, int height, const std::string& title)
	{
		// Initialise GLFW Windows flags
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		// CREATE the Window
		m_wnd = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

		if (m_wnd == NULL)
		{
			MK_ENG_ERROR("Failed to create new glfw Window!");
			return false;
		}

		glfwMakeContextCurrent(m_wnd);

		// Initialise GLAD to manage function pointers before calling any OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			MK_ENG_ERROR("Failed to initialie GLAD!");
			return false;
		}

		// ----- Initialise Viewport -----
		Vec2Int size = GetWindowSize();
		// Define the bounds in which to draw pixels in the rendering window
		glViewport(0, 0, size.x, size.y);
		// Register callback to resize viewport when window size is changed
		glfwSetFramebufferSizeCallback(m_wnd, framebuffer_size_callback);

		// Virtual call for child implementation
		OnInit();

		return true;
	}

	void Window::Tick()
	{
	}

	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {	
		glViewport(0, 0, width, height);
	}

	void Window::Render() // Default
	{
		// Pre render OpenGL
		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		// Generate Mesh
		std::vector<Vertex> vertices = {
			Vertex {
				glm::vec3(-0.5, -0.5, 0.0f)
			},
			Vertex {
				glm::vec3(0.5, -0.5, 0.0f)
			},
			Vertex {
				glm::vec3(0.0f, 0.5f, 0.0f)
			}
		};
		std::vector<unsigned int> indices = { 0, 1, 2 };
		Material mat;
		mat.colour = glm::vec3(1.0f, 0.5f, 0.2f);

		Mesh triangleMesh(vertices, indices, mat);

		Shader triangleShader = Shader("#version 460 core", "#version 460 core");
		triangleShader.set_shader_files("default.vs", "default.fs"); 
		triangleShader.use();
		// Draw 
		
		triangleMesh.Draw(triangleShader);

		// Post Render
		swapBuffers();
	}

	void Window::PollInputs() // Default
	{
		pollWindowEvents();
	}

	void Window::setShouldWindowClose(bool shouldClose) const noexcept
	{
		glfwSetWindowShouldClose(m_wnd, shouldClose);
	}

	void Window::setCursorMode(unsigned int newCursorState) const noexcept
	{
		glfwSetInputMode(m_wnd, GLFW_CURSOR, newCursorState);
	}

	bool Window::ShouldWindowClose() const noexcept
	{
		return glfwWindowShouldClose(m_wnd) != 0;;
	}

	void Window::pollWindowEvents()
	{
		glfwPollEvents();
	}

	void Window::swapBuffers() const noexcept { glfwSwapBuffers(m_wnd); }

	double Window::GetTime()
	{
		return glfwGetTime();
	}

	Murky::Vec2Int Murky::Window::GetWindowSize() const noexcept
	{
		Murky::Vec2Int sz{};
		glfwGetWindowSize(m_wnd, &sz.x, &sz.y);
		return sz;
	}
}