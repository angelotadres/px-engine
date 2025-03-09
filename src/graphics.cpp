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

#include "graphics.h"
#include <iostream>
#include <stdexcept>
#include "openGLContext.h"
#include "surface.h"

namespace pxe {
	// Shader source strings
	auto vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;
        out vec2 TexCoord;
        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";

	auto fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D screenTexture;
        void main() {
            FragColor = texture(screenTexture, TexCoord);
        }
    )";

	Graphics::Graphics(const int width, const int height) :
		width(width), height(height), surface(std::make_unique<Surface>(width, height)) {
		// Ensure the surface is cleared (all pixels set to opaque black) before first use.
		surface->clear();
		initOpenGL();
	}

	Graphics::~Graphics() {
		// Clean up OpenGL resources. The surface is automatically deleted.
		glDeleteTextures(1, &textureID);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteProgram(shaderProgram);
	}

	void Graphics::initOpenGL() {
		// Initialize GLAD (OpenGL function loader)
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			throw std::runtime_error("Failed to initialize GLAD");
		}


		// Compile vertex and fragment shaders.
		GLuint vertexShader, fragmentShader;
		compileShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource);
		compileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource);

		// Link shaders into a program.
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);
		GLint success;
		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Shader program linking failed: ") + infoLog);
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// Setup full-screen quad geometry (two triangles covering the screen).
		// Corrected vertex data: 4 vertices with 4 floats each (positions and texture coordinates).
		constexpr float vertices[] = {
				// positions       // texture coords
				-1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
				1.0f,  -1.0f, 1.0f, 0.0f, // Bottom-right
				1.0f,  1.0f,  1.0f, 1.0f, // Top-right
				-1.0f, 1.0f,  0.0f, 1.0f // Top-left
		};
		const unsigned int indices[] = {0, 1, 2, 2, 3, 0};

		// Create and bind VAO, VBO, and EBO.
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Configure vertex attributes.
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(0));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void *>(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Create texture to display the surface's pixels.
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		// IMPORTANT: Use GL_RGBA to match the 32-bit RGBA format of the Surface.
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
					 surface->getBuffer().data());
		// Set texture filtering parameters.
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Graphics::compileShader(GLuint &shader, const GLenum type, const char *source) {
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &source, nullptr);
		glCompileShader(shader);
		// Check for compile errors.
		GLint success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			const std::string shaderType = (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT";
			throw std::runtime_error("Shader compilation failed (" + shaderType + "): " + infoLog);
		}
	}

	void Graphics::beginFrame() {
		// Clear the surface (reset pixel buffer for the new frame).
		surface->clear();
	}

	void Graphics::endFrame() {
		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		// Update the texture with the latest pixel data from the Surface.
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Use GL_RGBA here as well.
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, surface->getBuffer().data());
		// Render the textured quad to the screen.
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}

	void Graphics::setPixel(const int x, const int y, const int r, const int g, const int b) {
		// Delegate to Surface: draw the pixel on the off-screen buffer.
		surface->setPixel(x, y, r, g, b);
	}

	void Graphics::setPixel(const int x, const int y, const Color color) {
		// Delegate to Surface: draw the pixel on the off-screen buffer.
		surface->setPixel(x, y, color);
	}

	int Graphics::getWidth() const { return width; }

	int Graphics::getHeight() const { return height; }
} // namespace pxe
