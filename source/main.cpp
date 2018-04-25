
#include <iostream>
#include <fstream>
#include <sstream>

#include "sdf.hpp"

float
SDF::scene (
	glm::vec3 point
) {
	return SDF::sphere(point);
}

int main() {
	SDF::Config c;
	
	std::ostringstream headerStream;
	headerStream << "P6\n";
    headerStream << c.renderWidth << ' ' << c.renderHeight << '\n';
    headerStream << "255\n";
    std::ofstream fileStream("out.ppm", std::ios::out | std::ios::binary);
	
	fileStream << headerStream.str();
	
	for (int h = 0; h < c.renderHeight; h++) {
		for (int w = 0; w < c.renderWidth; w++) {
			float u = ((w * 2.0f) / c.renderWidth) - 1.0f;
			float v = ((h * 2.0f) / c.renderHeight) - 1.0f;
			
			glm::vec3 rayOrigin = c.eye + u * c.right + v * c.up;
			glm::vec3 rayDir = glm::cross(c.up, c.right) * 1.0f;
			
			SDF::Intersection rayCollision = rayMarch(rayOrigin, rayDir, u, v, c);
			
			// Get 24-bit pixel sample and write it out
            unsigned char r, g, b;
            r = static_cast<unsigned char>(rayCollision.color.r * 255.0f);
            g = static_cast<unsigned char>(rayCollision.color.g * 255.0f);
            b = static_cast<unsigned char>(rayCollision.color.b * 255.0f);
           
            fileStream << r << g << b;
		}
	}
}
