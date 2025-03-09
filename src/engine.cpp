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

#include "engine.h"
#include <chrono>
#include <iostream>
#include "graphics.h"
#include "input.h"
#include "window.h"

namespace pxe {
	Engine::Engine(int width, int height, const std::string &title, const int pixelSize) {
		this->pixelSize = pixelSize;
		window = std::make_unique<Window>(width * pixelSize, height * pixelSize, title);
		graphics = std::make_unique<Graphics>(width, height);
		input = std::make_unique<Input>(&*window);
	}

	Engine::~Engine() = default;

	void Engine::run() {
		using clock = std::chrono::steady_clock;
		auto previousTime = clock::now();

		onSetup();
		while (!window->shouldClose()) {
			auto currentTime = clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - previousTime).count();
			previousTime = currentTime;

			graphics->beginFrame();
			onUpdate(deltaTime); // Pass computed deltaTime here.
			graphics->endFrame();
			window->swapBuffers();
			window->pollEvents();
		}
		onDestroy();
	}

	void Engine::onDestroy() { std::cout << "Cleaning up resources..." << std::endl; }

	bool Engine::isKeyPressed(KeyCode key) const { return input->isKeyPressed(static_cast<int>(key)); }

	bool Engine::isMousePressed(MouseButton button) const { return input->isMousePressed(static_cast<int>(button)); }

	std::pair<double, double> Engine::getMousePosition() const { return input->getMousePosition(); }

	void Engine::drawPixel(const int x, const int y, const int r, const int g, const int b) {
		graphics->setPixel(x, y, r, g, b);
	}

	void Engine::drawPixel(const int x, const int y, Color c) { graphics->setPixel(x, y, c.r(), c.g(), c.b()); }

	int Engine::getWindowWidth() const { return window->getWidth(); }

	int Engine::getWindowHeight() const { return window->getHeight(); }

	int Engine::getWidth() const { return graphics->getWidth(); }

	int Engine::getHeight() const { return graphics->getHeight(); }

	int Engine::getPixelSize() const { return pixelSize; }
} // namespace pxe
