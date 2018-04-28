
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
	
	c.camera = SDF::lookAt (
		glm::vec3 (0.0f, 0.0f, -2.0f),
		glm::vec3 (0.0f, 0.0f, 0.0f),
		glm::vec3 (0.0f, 1.0f, 0.0f)
	);
	
	std::ostringstream headerStream;
	headerStream << "P6\n";
    headerStream << c.renderWidth << ' ' << c.renderHeight << '\n';
    headerStream << "255\n";
    std::ofstream fileStream("out.ppm", std::ios::out | std::ios::binary);
	
	fileStream << headerStream.str();
	
	float renderAspectRatio  = c.renderWidth / c.renderHeight;
	float fovScale = glm::tan(glm::radians(c.fov * 0.5));	
	
	for (int rsY = 0; rsY < c.renderHeight; rsY++) {
		for (int rsX = 0; rsX < c.renderWidth; rsX++) {
			float ndcX = (rsX + 0.5) / c.renderWidth;
			float ndcY = (rsY + 0.5) / c.renderHeight;
			float ssX = (2 * ndcX - 1) * fovScale * renderAspectRatio;
			float ssY = (1 - 2 * ndcY) * fovScale;
			
			glm::vec3 ssRayOrigin (ssX, ssY, -1);
			
			// useful for calculating ws rayDirection
			glm::vec3 wsCameraOrigin = c.camera * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);		
			
			glm::vec3 wsRayOrigin = c.camera * glm::vec4(ssRayOrigin, 1.0f);
			glm::vec3 wsRayDir = wsRayOrigin - wsCameraOrigin;
			wsRayDir = glm::normalize(wsRayDir);
			
			SDF::Intersection rayCollision = SDF::rayMarch(wsRayOrigin, wsRayDir, c);
			
			// Get 24-bit pixel sample and write it out
            unsigned char r, g, b;
            r = static_cast<unsigned char>(rayCollision.color.r * 255.0f);
            g = static_cast<unsigned char>(rayCollision.color.g * 255.0f);
            b = static_cast<unsigned char>(rayCollision.color.b * 255.0f);
           
            fileStream << r << g << b;
		}
	}
}
