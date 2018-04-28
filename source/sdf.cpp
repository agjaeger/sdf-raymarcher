
#include "sdf.hpp"

SDF::Intersection 
SDF::rayMarch (
	glm::vec3 rayOrigin, 
	glm::vec3 rayDir,
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
 * Given a camera position (eye), target position (center), and a up vector (up)
 * produce a 4x4 matrix that represents the camera
 */
glm::mat4
SDF::lookAt (
	glm::vec3 eye,
	glm::vec3 center,
	glm::vec3 up
) {
	glm::vec3 Z = glm::normalize(center - eye);
	glm::vec3 X = glm::normalize(glm::cross(Z, glm::normalize(up)));
	glm::vec3 Y = glm::normalize(glm::cross(X, Z));

	return glm::mat4(
		glm::vec4(X, 0.0f),
		glm::vec4(Y, 0.0f),
		glm::vec4(-Z, 0.0f),
		glm::vec4(
			-glm::dot(X, eye), 
			-glm::dot(Y, eye), 
			glm::dot(Z, eye), 
			0.0f
		)
	);
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
	return glm::normalize (
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
