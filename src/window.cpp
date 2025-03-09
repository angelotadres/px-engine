/*
 * Part of the PX-Engine project - https://github.com/angelotadres/px-engine
 *
 * Copyright 2025 Angelo Tadres
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "window.h"
#include <stdexcept>
#include "input.h"

namespace pxe {
	Window::Window(const int width, const int height, const std::string &title) : width(width), height(height) {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (!window) {
			glfwTerminate();
			throw std::runtime_error("Failed to create GLFW window");
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1); // Enable VSync.
	}

	Window::~Window() {
		if (window) {
			glfwDestroyWindow(window);
		}
		glfwTerminate();
	}

	bool Window::shouldClose() const { return glfwWindowShouldClose(window); }

	void Window::swapBuffers() const { glfwSwapBuffers(window); }

	void Window::pollEvents() const { glfwPollEvents(); }

	GLFWwindow *Window::getGlfwWindow() const { return window; }

	int Window::getWidth() const { return width; }

	int Window::getHeight() const { return height; }
} // namespace pxe
