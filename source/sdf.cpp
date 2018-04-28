
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
	glm::vec3 from,
	glm::vec3 to,
	glm::vec3 up
) {
	glm::vec3 m_forward = glm::normalize(from - to);
	glm::vec3 m_right = glm::normalize(glm::cross(glm::normalize(up), m_forward));
	glm::vec3 m_up = glm::normalize(glm::cross(m_forward, m_right));

	return glm::mat4(
		glm::vec4(m_right, 0.0f),
		glm::vec4(m_up, 0.0f),
		glm::vec4(m_forward, 0.0f),
		glm::vec4(from, 0.0f)
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
SDF::sSphere (
	glm::vec3 point
) {
	return glm::length(point) - 1.0f;
}

float
SDF::usBox (
	glm::vec3 point,
	glm::vec3 boxSize
) {
	glm::vec3 delta = glm::abs(point) - boxSize;

	return glm::length(glm::max(delta, 0.0f));
}

float 
SDF::opUnion (
	float d1, float d2
) {
	return glm::min(d1, d2);
}

float 
SDF::opSubtraction (
	float d1, float d2
) {
	return glm::max(-d1, d2);
}

float 
SDF::opIntersection (
	float d1, float d2
) {
	return glm::max(d1, d2);
}
