
#include "sdf.hpp"

float sphereOfCubes (
	glm::vec3 point
) {
	float scaleFactor = 0.5f;
	return 
		SDF::opIntersection(
			SDF::usBox(SDF::opRep(point, glm::vec3(0.5, 0.5, 0.5)), glm::vec3(0.1f, 0.1f, 0.1f)),
			SDF::sSphere(point)
		);
}

float
SDF::scene (
	glm::vec3 point,
	SDF::Config c
) {
	return sphereOfCubes(SDF::opRep(point, glm::vec3(3, 3, 3)));
}
