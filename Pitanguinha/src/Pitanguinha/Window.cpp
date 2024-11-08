#include "pch.h"
#include "Window.h"

#include "Log.h"

#include "Events/Event.h"
#include "Events/WindowEvent.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Ptg {

	Window::~Window()
	{
		Shutdown(); 
	}

	Window* Window::Create(unsigned int width, unsigned int height, const char* name)
	{
		m_Data.Width = width;
		m_Data.Height = height;
		m_Data.App_name = name;

		return new Window();
	}

	void Window::Init()
	{
		if (!glfwInit())
			PTG_DEBUG("Error: glfwInit()");

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.App_name, nullptr, nullptr);
		if(m_Window == nullptr)
			PTG_DEBUG("Error: glfwCreateWindow()");

		// Carregar a imagem do �cone
		int width, height, channels;
		unsigned char* pixels = stbi_load("logo/pitanguinha.png", &width, &height, &channels, 4); // Carregar como RGBA
		if (pixels) {
			GLFWimage icon;
			icon.width = width;
			icon.height = height;
			icon.pixels = pixels;

			// Definir o �cone da janela
			glfwSetWindowIcon(m_Window, 1, &icon);

			// Liberar a imagem do �cone ap�s us�-la
			stbi_image_free(pixels);
		}

		glfwMakeContextCurrent(m_Window);

		int status = gladLoadGL((GLADloadfunc)glfwGetProcAddress);

		// setup imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		glfwSetWindowUserPointer(m_Window, &m_Data);

		PTG_DEBUG("Listening callbacks...");

		glfwSetErrorCallback([](int error_code, const char* description)
		{
			PTG_DEBUG("Error (" << error_code << ") " << description);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			if (data)
			{
				PTG_DEBUG("Framebuffer size callback!");
			}
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			PTG_DEBUG("Cursor moved callback!");
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				PTG_DEBUG("Key " << key << " Pressed");
				break;
			case GLFW_RELEASE:
				PTG_DEBUG("Key " << key << " Released");
				break;
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
				PTG_DEBUG("Mouse button " << button << " Pressed");
				break;
			case GLFW_RELEASE:
				PTG_DEBUG("Mouse button " << button << " Released");
				break;
			}
		});
	}

	void Window::Update()
	{
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(m_Window);
	}

	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}