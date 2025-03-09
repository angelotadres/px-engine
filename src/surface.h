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
#include <cstdint>
#include <vector>
#include "color.h"

namespace pxe {
	/**
	 * @brief The Surface class represents an off-screen pixel buffer for rendering.
	 *
	 * This class encapsulates a 2D pixel array stored as a linear buffer.
	 * Each pixel is stored as a 32-bit value in 0xAARRGGBB format.
	 */
	class Surface {
	public:
		/**
		 * @brief Constructs a Surface with the given width and height.
		 *
		 * Initializes a pixel buffer with all pixels set to opaque black (0,0,0,255).
		 * @param width Width of the surface in pixels.
		 * @param height Height of the surface in pixels.
		 */
		Surface(int width, int height);

		/**
		 * @brief Clears the surface by setting all pixels to opaque black (0,0,0,255).
		 */
		void clear();

		/**
		 * @brief Sets a pixel to a specific color.
		 *
		 * Uses the full RGBA value from the Color object.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param color The color to set.
		 */
		void setPixel(int x, int y, Color color);

		/**
		 * @brief Sets a pixel using separate RGB values.
		 *
		 * The alpha channel is set to 255 (opaque) by default.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param r Red component.
		 * @param g Green component.
		 * @param b Blue component.
		 */
		void setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

		/**
		 * @brief Gets the color of a pixel at a given coordinate.
		 *
		 * Returns Color::Black if the coordinates are out of bounds.
		 * @param x X-coordinate.
		 * @param y Y-coordinate.
		 * @return The color of the pixel.
		 */
		[[nodiscard]] Color getPixel(int x, int y) const;

		/**
		 * @brief Retrieves the underlying pixel buffer.
		 *
		 * The buffer stores one 32-bit value per pixel.
		 * @return A constant reference to the pixel buffer.
		 */
		[[nodiscard]] const std::vector<uint32_t> &getBuffer() const;

		/**
		 * @brief Gets the width of the surface.
		 * @return The width in pixels.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Gets the height of the surface.
		 * @return The height in pixels.
		 */
		[[nodiscard]] int getHeight() const;

		Surface(const Surface &) = delete;
		Surface &operator=(const Surface &) = delete;
		Surface(Surface &&other) noexcept;
		Surface &operator=(Surface &&other) noexcept;

	private:
		int width, height;
		std::vector<uint32_t> pixelBuffer;
	};
} // namespace pxe
