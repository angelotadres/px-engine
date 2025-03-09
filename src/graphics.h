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
#include "openGLContext.h"
#include "surface.h"

namespace pxe {
	/**
	 * @brief Handles OpenGL-based rendering and manages the rendering pipeline.
	 */
	class Graphics {
	public:
		/**
		 * @brief Constructs a Graphics object and initializes OpenGL resources.
		 * @param width Width of the rendering area.
		 * @param height Height of the rendering area.
		 */
		Graphics(int width, int height);

		/**
		 * @brief Destructor that cleans up OpenGL resources.
		 */
		~Graphics();

		/**
		 * @brief Begins a new frame by clearing the surface.
		 */
		void beginFrame();

		/**
		 * @brief Finalizes the frame and updates the OpenGL texture.
		 */
		void endFrame();

		/**
		 * @brief Places a pixel at the specified coordinates with the given color.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param r Red component (0-255).
		 * @param g Green component (0-255).
		 * @param b Blue component (0-255).
		 */
		void setPixel(int x, int y, int r, int g, int b);

		/**
		 * @brief Places a pixel at the specified coordinates with the given Color.
		 * @param x X-coordinate of the pixel.
		 * @param y Y-coordinate of the pixel.
		 * @param color Color object containing RGBA values.
		 */
		void setPixel(int x, int y, Color color);

		/**
		 * @brief Gets the graphics surface width.
		 */
		[[nodiscard]] int getWidth() const;

		/**
		 * @brief Gets the graphics surface height.
		 */
		[[nodiscard]] int getHeight() const;

	private:
		int width, height; /**< Width and height of the rendering area. */
		std::unique_ptr<Surface> surface; /**< Encapsulated surface that stores pixel data. */
		GLuint textureID{}; /**< OpenGL texture ID used for rendering. */
		GLuint VAO{}; /**< Vertex Array Object. */
		GLuint VBO{}; /**< Vertex Buffer Object. */
		GLuint EBO{}; /**< Element Buffer Object. */
		GLuint shaderProgram{}; /**< OpenGL shader program. */

		/**
		 * @brief Initializes OpenGL settings and resources.
		 */
		void initOpenGL();

		/**
		 * @brief Compiles a shader from source code.
		 * @param shader Reference to the shader ID.
		 * @param type Shader type (e.g., GL_VERTEX_SHADER, GL_FRAGMENT_SHADER).
		 * @param source Shader source code.
		 */
		static void compileShader(GLuint &shader, GLenum type, const char *source);
	};
} // namespace pxe
