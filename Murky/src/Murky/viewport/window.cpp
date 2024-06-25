#include "mkpch.h"

#include "window.hpp"
#include "../math/vec2Int.h"
#include "../rendering/shader.h"
#include "../rendering/model.h"

#include "../events/ApplicationEvent.h"
#include "../events/KeyEvent.h"
#include "../events/MouseEvent.h"

#include <GLFW/glfw3.h>
#include "../core/Log.h"

namespace Murky
{
	// Handles resizing the glViewport to match the Window's width and height
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void GLFWErrorCallback(int error, const char* description)
	{
		MK_ENG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window::~Window()
	{
		OnDestroy();
		glfwDestroyWindow(m_wnd);
		glfwTerminate();
	}

	bool Window::Init(int width, int height, const std::string& title)
	{
		// Initialise GLFW Windows flags
		int success = glfwInit();
		MK_ENG_ASSERT(success, "Could not initialise GLFW!");
		glfwSetErrorCallback(GLFWErrorCallback);

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

		m_data.Width = width;
		m_data.Height = height;
		m_data.Title = title;

		glfwMakeContextCurrent(m_wnd);
		glfwSetWindowUserPointer(m_wnd, &m_data);
		/// TODO: Set VSync here


		// Initialise GLAD to manage function pointers before calling any OpenGL functions
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			MK_ENG_ERROR("Failed to initialie GLAD!");
			return false;
		}

		// ----- Initialise Viewport -----
		// Define the bounds in which to draw pixels in the rendering window
		glViewport(0, 0, GetWidth(), GetHeight());



		// Register callback to resize viewport when window size is changed
		glfwSetFramebufferSizeCallback(m_wnd, framebuffer_size_callback);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(m_wnd, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
		});

		glfwSetWindowCloseCallback(m_wnd, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_wnd, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS: 
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE: 
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT: 
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_wnd, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_wnd, [](GLFWwindow* window, double xOffset, double yOffset) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_wnd, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		SetEventCallback(BIND_EVENT_FN(Window::OnEvent));


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

	void Window::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Window::OnWindowClose));

		MK_ENG_TRACE("evebt {0}", e.ToString());
	} 

	bool Window::OnWindowClose(WindowCloseEvent& e)
	{
		setShouldWindowClose(true);
		return true;
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
}