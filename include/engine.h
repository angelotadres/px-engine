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
#include <memory>
#include <string>
#include "color.h"
#include "keyCodes.h"

namespace pxe {
	/**
	 * @brief The Engine class provides a high-level interface for creating applications.
	 *
	 * Users should inherit from Engine and override `onSetup` and `onUpdate`.
	 */
	class Engine {
	public:
		/**
		 * @brief Creates an instance of the Pixel Engine.
		 *
		 * Initializes the engine with a specified resolution, window title, and optional pixel scaling.
		 * The pixel size determines how many screen pixels represent a single logical pixel.
		 * A value of 1 means each logical pixel is mapped to one screen pixel, while higher values
		 * enlarge each pixel (e.g., 2 makes each logical pixel a 2×2 block on screen).
		 *
		 * @param width The logical width of the engine's drawing surface.
		 * @param height The logical height of the engine's drawing surface.
		 * @param title The title of the application window.
		 * @param pixelSize The scaling factor for rendering pixels (default is 1:1 mapping).
		 */
		Engine(int width, int height, const std::string &title, int pixelSize = 1);

		/**
		 * @brief Virtual destructor for Engine.
		 *
		 * Ensures proper cleanup of resources.
		 */
		virtual ~Engine();

		/**
		 * @brief Starts the main engine loop.
		 *
		 * Calls `onSetup()`, then enters the update loop, calling `onUpdate(deltaTime)`
		 * each frame. Stops when the window is closed, then calls `onDestroy()`.
		 */
		void run();

	protected:
		/**
		 * @brief Called once when the engine starts.
		 *
		 * Override this function to initialize game objects and resources.
		 */
		virtual void onSetup() = 0;

		/**
		 * @brief Called every frame with the delta time in seconds.
		 *
		 * Override this function to update game logic.
		 * @param deltaTime The time in seconds since the last frame.
		 */
		virtual void onUpdate(float deltaTime) = 0;

		/**
		 * @brief Called when the engine is shutting down.
		 *
		 * Override this function to clean up resources.
		 */
		virtual void onDestroy();

		/**
		 * @brief Checks if a key is currently pressed.
		 *
		 * @param key The key to check (based on `KeyCode`).
		 * @return True if the key is pressed, false otherwise.
		 */
		[[nodiscard]] bool isKeyPressed(KeyCode key) const;

		/**
		 * @brief Checks if a mouse button is pressed.
		 *
		 * @param button The mouse button to check (based on `MouseButton`).
		 * @return True if the button is pressed, false otherwise.
		 */
		[[nodiscard]] bool isMousePressed(MouseButton button) const;

		/**
		 * @brief Gets the current mouse cursor position.
		 *
		 * @return A pair representing the (x, y) position of the cursor in window coordinates.
		 */
		[[nodiscard]] std::pair<double, double> getMousePosition() const;

		/**
		 * @brief Draws a pixel on the screen using a `Color` object.
		 *
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param color The color of the pixel.
		 */
		void drawPixel(int x, int y, Color color);

		/**
		 * @brief Draws a pixel on the screen using separate RGB components.
		 *
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param r Red component (0-255).
		 * @param g Green component (0-255).
		 * @param b Blue component (0-255).
		 */
		void drawPixel(int x, int y, int r, int g, int b);

		/**
		 * @brief Draws a line on the screen using a `Color` object.
		 *
		 * @param x1 X-coordinate of the pixel representing the start of the line.
		 * @param y1 Y-coordinate of the pixel representing the start of the line.
		 * @param x2 X-coordinate of the pixel representing the end of the line.
		 * @param y2 Y-coordinate of the pixel representing the end of the line.
		 * @param color The color of the line.
		 */
		void drawLine(int x1, int y1, int x2, int y2, Color color);

		/**
		 * @brief Draws a line on the screen using separate RGB components.
		 *
		 * @param x1 X-coordinate of the pixel representing the start of the line.
		 * @param y1 Y-coordinate of the pixel representing the start of the line.
		 * @param x2 X-coordinate of the pixel representing the end of the line.
		 * @param y2 Y-coordinate of the pixel representing the end of the line.
		 * @param r Red component (0-255).
		 * @param g Green component (0-255).
		 * @param b Blue component (0-255).
		 */
		void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);

		/**
		 * @brief Gets the width of the window.
		 *
		 * @return The width of the window in pixels.
		 */
		[[nodiscard]] int getWindowWidth() const;

		/**
		 * @brief Gets the height of the window.
		 *
		 * @return The height of the window in pixels.
		 */
		[[nodiscard]] int getWindowHeight() const;

		/**
		 * @brief Gets the width of the target rendering surface in pixel size units.
		 *
		 * @return The width of the target rendering surface in pixel size units.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Gets the height of the target rendering surface in pixel size units.
		 *
		 * @return The height of the target rendering surface in pixel size units.
		 */
		[[nodiscard]] int getHeight() const;

		/**
		 * @brief Gets the pixel size scaling factor.
		 *
		 * The pixel size determines how many screen pixels represent a single logical pixel.
		 * A value of 1 means a 1:1 ratio (default behavior), while a value of 2 means each
		 * logical pixel is rendered as a 2×2 block on screen.
		 *
		 * @return The pixel size scaling factor.
		 */
		[[nodiscard]] int getPixelSize() const;

	private:
		int pixelSize = 0;
		std::unique_ptr<class Window> window; ///< Smart pointer for managing window lifecycle.
		std::unique_ptr<class Graphics> graphics; ///< Smart pointer for managing graphics lifecycle.
		std::unique_ptr<class Input> input; ///< Smart pointer for managing graphics lifecycle.
	};
} // namespace pxe
