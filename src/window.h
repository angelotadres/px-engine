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

#pragma once
#include <string>
#include "openGLContext.h"

namespace pxe {
	/**
	 * @brief Manages the application window and OpenGL context.
	 */
	class Window {
	public:
		/**
		 * @brief Constructs a window and initializes GLFW.
		 */
		Window(int width, int height, const std::string &title);

		/**
		 * @brief Destructor for Window.
		 */
		~Window();

		/**
		 * @brief Checks if the window should close.
		 */
		[[nodiscard]] bool shouldClose() const;

		/**
		 * @brief Swaps buffers to display the next frame.
		 */
		void swapBuffers() const;

		/**
		 * @brief Polls window events.
		 */
		void pollEvents() const;

		/**
		 * @brief Returns a pointer to the GLFW window handle.
		 */
		[[nodiscard]] GLFWwindow *getGlfwWindow() const;

		/**
		 * @brief Gets the window width.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Gets the window height.
		 */
		[[nodiscard]] int getHeight() const;

	private:
		GLFWwindow *window;
		int width;
		int height;
	};
} // namespace pxe
