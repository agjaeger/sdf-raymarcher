
#include "sdf.hpp"

SDF::Intersection 
SDF::rayMarch (
	glm::vec3 rayOrigin, 
	glm::vec3 rayDir,
	float u,
	float v, 
	SDF::Config c
) {	
	SDF::Intersection col;
	float dist = c.rayMin;
			
	for (int i = 0; i < c.rayMaxSteps; ++i) {
		float depth = SDF::scene(rayOrigin + rayDir * dist);
		
		if (depth < c.epsilon) {
			col.dist = dist;
			col.color = SDF::estimateNormal(rayOrigin + rayDir * dist, c);
			
			return col;
		}
	
		dist += depth;
		
		if (dist >= c.rayMax) {
			col.dist = dist;
			col.color = c.skyColor;
			
			return col; 
		}
	}
	
	col.dist = c.rayMax;
	col.color = c.skyColor;
	
	return col;
}


/*
 * Estimates the gradient of the surface and 
 * returns it. This is an approximation of the normal at the point2
 */
glm::vec3 
SDF::estimateNormal (
	glm::vec3 point,
	SDF::Config c
) {
	return glm::normalize(
		glm::vec3(
			SDF::scene(
				glm::vec3(point.x + c.epsilon, point.y, point.z)
			) - SDF::scene(
				glm::vec3(point.x - c.epsilon, point.y, point.z)
			),
			
			SDF::scene(
				glm::vec3(point.x, point.y + c.epsilon, point.z)
			) - SDF::scene(
				glm::vec3(point.x, point.y - c.epsilon, point.z)
			),
			
			SDF::scene(
				glm::vec3(point.x, point.y, point.z + c.epsilon)
			) - SDF::scene(
				glm::vec3(point.x, point.y, point.z - c.epsilon)
			)
		)
	);
}

float 
SDF::sphere (
	glm::vec3 point
) {
	return glm::length(point) - 1.0f;
}
