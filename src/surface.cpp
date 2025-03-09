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

#include "surface.h"
#include <algorithm>

namespace pxe {
	Surface::Surface(int width, int height) :
		width(width), height(height), pixelBuffer(static_cast<size_t>(width * height), 0xFF000000) {
		// 0xFF000000 represents opaque black in 0xAARRGGBB format.
	}

	void Surface::clear() { std::ranges::fill(pixelBuffer, 0xFF000000); }

	void Surface::setPixel(int x, int y, Color color) {
		if (x < 0 || x >= width || y < 0 || y >= height)
			return;
		const int index = y * width + x;
		// Build a 32-bit pixel from the Color's channels.
		pixelBuffer[index] = (static_cast<uint32_t>(color.a()) << 24) | (static_cast<uint32_t>(color.r()) << 16) |
							 (static_cast<uint32_t>(color.g()) << 8) | static_cast<uint32_t>(color.b());
	}

	void Surface::setPixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
		if (x < 0 || x >= width || y < 0 || y >= height)
			return;
		const int index = y * width + x;
		// Default alpha is set to 255 (opaque).
		pixelBuffer[index] = (0xFFu << 24) | (static_cast<uint32_t>(r) << 16) | (static_cast<uint32_t>(g) << 8) |
							 static_cast<uint32_t>(b);
	}

	Color Surface::getPixel(int x, int y) const {
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return Color::Black;
		}
		const int index = y * width + x;
		const uint32_t pixel = pixelBuffer[index];
		// Extract channels from the 32-bit pixel.
		const uint8_t a = (pixel >> 24) & 0xFF;
		const uint8_t r = (pixel >> 16) & 0xFF;
		const uint8_t g = (pixel >> 8) & 0xFF;
		const uint8_t b = pixel & 0xFF;
		return Color(r, g, b, a);
	}

	const std::vector<uint32_t> &Surface::getBuffer() const { return pixelBuffer; }

	int Surface::getWidth() const { return width; }

	int Surface::getHeight() const { return height; }

	Surface::Surface(Surface &&other) noexcept :
		width(other.width), height(other.height), pixelBuffer(std::move(other.pixelBuffer)) {
		other.width = 0;
		other.height = 0;
	}

	Surface &Surface::operator=(Surface &&other) noexcept {
		if (this != &other) {
			width = other.width;
			height = other.height;
			pixelBuffer = std::move(other.pixelBuffer);
			other.width = 0;
			other.height = 0;
		}
		return *this;
	}
} // namespace pxe
