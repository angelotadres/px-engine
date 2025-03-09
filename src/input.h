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
#include <functional>
#include <unordered_map>
#include "openGLContext.h"
#include "window.h"

namespace pxe {
	/**
	 * @brief Manages user input (keyboard & mouse).
	 *
	 * This class tracks input states and provides event callbacks.
	 */
	class Input {
	public:
		/**
		 * @brief Constructs an Input system object.
		 * @param window The window handle.
		 */
		explicit Input(Window *window);

		/**
		 * @brief Checks if a key is currently pressed.
		 * @param key The GLFW key code (e.g., GLFW_KEY_W).
		 * @return True if the key is pressed.
		 */
		bool isKeyPressed(int key) const noexcept;

		/**
		 * @brief Checks if a mouse button is pressed.
		 * @param button The GLFW mouse button (e.g., GLFW_MOUSE_BUTTON_LEFT).
		 * @return True if the button is pressed.
		 */
		bool isMousePressed(int button) const noexcept;

		/**
		 * @brief Gets the current mouse position.
		 * @return A pair (x, y) of the mouse coordinates.
		 */
		std::pair<double, double> getMousePosition() const noexcept;

		/**
		 * @brief Sets a callback function for key events.
		 * @param callback The function to be called on key events.
		 */
		void setKeyCallback(std::function<void(int key, int action)> callback) noexcept;

	private:
		std::unordered_map<int, bool> keyState;
		std::unordered_map<int, bool> mouseState;
		double mouseX = 0;
		double mouseY = 0;

		std::function<void(int, int)> keyCallback = nullptr;

		static void keyCallbackGLFW(GLFWwindow *window, int key, int scancode, int action, int mods);
		static void mouseButtonCallbackGLFW(GLFWwindow *window, int button, int action, int mods);
		static void cursorPositionCallbackGLFW(GLFWwindow *window, double xpos, double ypos);
	};
} // namespace pxe
