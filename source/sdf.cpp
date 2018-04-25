
#include "sdf.hpp"

float 
SDF::rayMarch (
	glm::vec3 rayOrigin, 
	glm::vec3 rayDir,
	float u,
	float v, 
	SDF::Config c
) {	
	float dist = c.rayMin;
			
	for (int i = 0; i < c.rayMaxSteps; ++i) {
		float depth = SDF::sdfScene(rayOrigin + rayDir * dist);
		
		if (depth < c.epsilon) {
			return dist;
		}
	
		dist += depth;
		
		if (dist >= c.rayMax) {
			return c.rayMax;
		}
	}
	
	return c.rayMax;
}

float 
SDF::sphere (
	glm::vec3 point
) {
	return glm::length(point) - 1.0f;
}

