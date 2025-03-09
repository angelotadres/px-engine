/*
* PX-Engine Demo - Rotating Square
 * ----------------------------------
 * This demo showcases a simple rotating square using the PX-Engine.
 * The square is centered in the window and rotates over time.
 *
 * Features:
 * - Uses Bresenham’s line algorithm to draw lines (provided by the engine).
 * - Applies 2D transformations using GLM (rotation and translation).
 * - Changes color when the space key is pressed.
 * - Uses delta time to ensure smooth rotation.
 *
 * Controls:
 * - Press SPACE to change the square's color.
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "engine.h"

class Demo final : public pxe::Engine {
public:
	Demo(int width, int height, const std::string &title, int pixelSize = 1) :
		Engine(width, height, title, pixelSize) {}

	void onSetup() override {}

	void onUpdate(float deltaTime) override {
		using glm::mat2;
		using glm::vec2;

		// Define rotation matrix
		float angle = rotationAngle;
		mat2 rotationMatrix = {{std::cos(angle), -std::sin(angle)}, {std::sin(angle), std::cos(angle)}};

		// Define square vertices
		vec2 vertices[4] = {{-sideLength / 2, -sideLength / 2},
							{sideLength / 2, -sideLength / 2},
							{sideLength / 2, sideLength / 2},
							{-sideLength / 2, sideLength / 2}};

		// Rotate and translate each vertex
		for (auto &v: vertices) {
			v = rotationMatrix * v + vec2(centerX, centerY);
		}

		// Set color
		pxe::Color c = isKeyPressed(pxe::KeyCode::Space) ? pxe::Color::Magenta : pxe::Color::White;

		// Draw the square edges
		for (int i = 0; i < 4; i++) {
			drawLine(static_cast<int>(vertices[i].x), static_cast<int>(vertices[i].y),
					 static_cast<int>(vertices[(i + 1) % 4].x), static_cast<int>(vertices[(i + 1) % 4].y), c.r(), c.g(),
					 c.b());
		}

		// Increase rotation angle
		rotationAngle += velocity * deltaTime;
	}

private:
	float rotationAngle = 0.0f;
	const int centerX = getWidth() / 2;
	const int centerY = getHeight() / 2;
	const float velocity = 2.0f;
	const float sideLength = std::min(getWidth(), getHeight()) / 3.0f;

	void onDestroy() override { std::cout << "Sandbox cleanup.\n"; }
};

int main() {
	try {
		Demo demo(100, 100, "PX Engine Demo", 8);
		demo.run();
	} catch (const std::exception &e) {
		std::cerr << "Application error: " << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
