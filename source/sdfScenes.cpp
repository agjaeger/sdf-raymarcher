
#include "sdf.hpp"

float
SDF::scene (
	glm::vec3 point,
	SDF::Config c
) {
	float scaleFactor = 0.5f;
	return 
		SDF::opIntersection(
			SDF::usBox(SDF::opRep(point, glm::vec3(0.5, 0.5, 0.5)), glm::vec3(0.1f, 0.1f, 0.1f)),
			SDF::sSphere(point)
		);
}
