/*
* PX-Engine Demo - Mandelbrot Set Visualization
 * -----------------------------------------------
 * This demo showcases a Mandelbrot set visualization using the PX-Engine.
 * The visualization maps each pixel to a point in the complex plane and
 * iterates the Mandelbrot equation to determine its color.
 *
 * Features:
 * - Uses pixel-by-pixel iteration to generate the Mandelbrot set.
 * - Maps the display coordinates to the complex plane.
 * - Allows interactive panning using the AWSD keys.
 * - Enables zoom in and out using the Up and Down arrow keys.
 * - Uses delta time to ensure smooth interaction.
 *
 * Controls:
 * - Use W/A/S/D to move (pan) the view.
 * - Use UP and DOWN arrows to zoom in and out.
 */

#include <cmath>
#include <iostream>
#include "engine.h"
#include "keyCodes.h"

class MandelbrotDemo final : public pxe::Engine {
public:
    MandelbrotDemo(int width, int height, const std::string &title, int pixelSize = 1) :
        Engine(width, height, title, pixelSize),
        offsetX(0.0), offsetY(0.0),
        // Initial scale: mapping one pixel to a small step in the complex plane.
        scale(4.0 / std::min(getWidth(), getHeight()))
    {}

    void onSetup() override {
        // Optionally, any one-time setup can be done here.
    }

    void onUpdate(float deltaTime) override {
        // Adjust panning with AWSD keys.
        // We scale the pan speed relative to the current scale to ensure consistent movement.
        double panSpeed = 200.0 * deltaTime * scale;
        if (isKeyPressed(pxe::KeyCode::W)) { offsetY += panSpeed; }
        if (isKeyPressed(pxe::KeyCode::S)) { offsetY -= panSpeed; }
        if (isKeyPressed(pxe::KeyCode::A)) { offsetX -= panSpeed; }
        if (isKeyPressed(pxe::KeyCode::D)) { offsetX += panSpeed; }

        // Adjust zoom with Up and Down arrow keys.
        // Zooming is done by modifying the scale: decreasing it zooms in, increasing zooms out.
        double zoomSpeed = 1.5 * deltaTime;
        if (isKeyPressed(pxe::KeyCode::UpArrow)) { scale *= (1 - zoomSpeed); }
        if (isKeyPressed(pxe::KeyCode::DownArrow)) { scale *= (1 + zoomSpeed); }

        // Render the Mandelbrot set.
        int width = getWidth();
        int height = getHeight();
        // Loop over each pixel.
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                // Map the pixel to a point in the complex plane.
                // We center the view at (offsetX, offsetY).
                double real = (x - width / 2) * scale + offsetX;
                double imag = (y - height / 2) * scale + offsetY;

                // Mandelbrot iteration.
                const int maxIter = 100;
                int iter = 0;
                double zr = 0.0, zi = 0.0;
                while ((zr * zr + zi * zi <= 4.0) && (iter < maxIter)) {
                    double temp = zr * zr - zi * zi + real;
                    zi = 2.0 * zr * zi + imag;
                    zr = temp;
                    iter++;
                }

                // Choose a color based on the number of iterations.
                int r, g, b;
                if (iter == maxIter) {
                    // Points inside the set are drawn black.
                    r = g = b = 0;
                } else {
                    // Points outside the set are colored using a simple gradient.
                    double t = static_cast<double>(iter) / maxIter;
                    r = static_cast<int>(9 * (1 - t) * t * t * t * 255);
                    g = static_cast<int>(15 * (1 - t) * (1 - t) * t * t * 255);
                    b = static_cast<int>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
                }
                drawPixel(x, y, r, g, b);
            }
        }
    }

private:
    double offsetX, offsetY; // Offsets in the complex plane for panning.
    double scale;          // Scale factor (complex-plane units per pixel).
};

int main() {
    try {
        MandelbrotDemo demo(100, 60, "Mandelbrot Set Demo - PX-Engine", 8);
        demo.run();
    } catch (const std::exception &e) {
        std::cerr << "Application error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
