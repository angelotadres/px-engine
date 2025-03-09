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

namespace pxe {
	/**
	 * @brief Represents an RGBA color using a compact 32-bit storage.
	 *
	 * The color is stored in 0xAARRGGBB format, where the alpha channel occupies the most
	 * significant 8 bits. By default, the alpha channel is set to 255 (fully opaque).
	 */
	struct Color {
	private:
		uint32_t value; // Stores color in 0xAARRGGBB format

	public:
		/**
		 * @brief Constructs a color with the given RGBA components.
		 *
		 * @param red Red component (0-255).
		 * @param green Green component (0-255).
		 * @param blue Blue component (0-255).
		 * @param alpha Alpha component (0-255, default is 255 for fully opaque).
		 */
		explicit constexpr Color(const uint8_t red = 0, const uint8_t green = 0, const uint8_t blue = 0, const uint8_t alpha = 255)
			: value((static_cast<uint32_t>(alpha) << 24) | (red << 16) | (green << 8) | blue) {}

		/**
		 * @brief Retrieves the red component.
		 *
		 * @return The red component (0-255).
		 */
		[[nodiscard]] constexpr uint8_t r() const { return (value >> 16) & 0xFF; }

		/**
		 * @brief Retrieves the green component.
		 *
		 * @return The green component (0-255).
		 */
		[[nodiscard]] constexpr uint8_t g() const { return (value >> 8) & 0xFF; }

		/**
		 * @brief Retrieves the blue component.
		 *
		 * @return The blue component (0-255).
		 */
		[[nodiscard]] constexpr uint8_t b() const { return value & 0xFF; }

		/**
		 * @brief Retrieves the alpha component.
		 *
		 * @return The alpha component (0-255).
		 */
		[[nodiscard]] constexpr uint8_t a() const { return (value >> 24) & 0xFF; }

		// Predefined Colors (Fully opaque by default)
		static const Color Black;
		static const Color White;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Cyan;
		static const Color Magenta;
	};

	// Define static color constants **outside** the class body
	inline constexpr Color Color::Black{0, 0, 0};
	inline constexpr Color Color::White{255, 255, 255};
	inline constexpr Color Color::Red{255, 0, 0};
	inline constexpr Color Color::Green{0, 255, 0};
	inline constexpr Color Color::Blue{0, 0, 255};
	inline constexpr Color Color::Yellow{255, 255, 0};
	inline constexpr Color Color::Cyan{0, 255, 255};
	inline constexpr Color Color::Magenta{255, 0, 255};

} // namespace pxe
