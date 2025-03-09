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

#include "input.h"
#include <iostream>

namespace pxe {
	Input::Input(Window *window) {
		// Store 'this' pointer in the GLFW window's user pointer
		glfwSetWindowUserPointer(window->getGlfwWindow(), this);

		// Set GLFW callbacks
		glfwSetKeyCallback(window->getGlfwWindow(), keyCallbackGLFW);
		glfwSetMouseButtonCallback(window->getGlfwWindow(), mouseButtonCallbackGLFW);
		glfwSetCursorPosCallback(window->getGlfwWindow(), cursorPositionCallbackGLFW);
	}

	bool Input::isKeyPressed(int key) const noexcept {
		auto it = keyState.find(key);
		return it != keyState.end() && it->second;
	}

	bool Input::isMousePressed(int button) const noexcept {
		auto it = mouseState.find(button);
		return it != mouseState.end() && it->second;
	}

	std::pair<double, double> Input::getMousePosition() const noexcept { return {mouseX, mouseY}; }

	void Input::setKeyCallback(std::function<void(int key, int action)> callback) noexcept {
		keyCallback = std::move(callback);
	}

	void Input::keyCallbackGLFW(GLFWwindow *window, int key, int scancode, int action, int mods) {
		Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
		if (action == GLFW_PRESS) {
			input->keyState[key] = true;
		} else if (action == GLFW_RELEASE) {
			input->keyState[key] = false;
		}

		// Call user-defined key callback if set.
		if (input->keyCallback) {
			input->keyCallback(key, action);
		}
	}

	void Input::mouseButtonCallbackGLFW(GLFWwindow *window, int button, int action, int mods) {
		Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
		if (action == GLFW_PRESS) {
			input->mouseState[button] = true;
		} else if (action == GLFW_RELEASE) {
			input->mouseState[button] = false;
		}
	}

	void Input::cursorPositionCallbackGLFW(GLFWwindow *window, double xpos, double ypos) {
		Input *input = static_cast<Input *>(glfwGetWindowUserPointer(window));
		input->mouseX = xpos;
		input->mouseY = ypos;
	}
} // namespace pxe
