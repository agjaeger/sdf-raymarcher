
#include "sdf.hpp"

float
boxMinusCylinder (
	glm::vec3 point,
	SDF::Config c
) {
	return SDF::opSubtraction(
		SDF::opUnion(
			SDF::opUnion(
				SDF::sCylinder (
					SDF::opTx(point, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 90.0f)),
					glm::vec2(0.3, 1.0)
				),
				SDF::sCylinder (
					SDF::opTx(point, glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 0.0f)),
					glm::vec2(0.3, 1.0)
				)
			),
			SDF::sCylinder (
				SDF::opTx(point, glm::vec3(0.0f), glm::vec3(90.0f, 0.0f, 0.0f)),
				glm::vec2(0.3, 1.0)
			)
		),		
		SDF::usBox(point, glm::vec3(0.5, 0.5, 0.5))		
	);
}

float
boxMinusCylinderMinusCorners (
	glm::vec3 point,
	SDF::Config c
) {
	return 
	SDF::opSubtraction(
		SDF::opUnion(
			SDF::opUnion(
				SDF::opUnion(
					SDF::opUnion(
						SDF::opUnion(
							SDF::opUnion(
								SDF::opUnion(
									SDF::sCylinder(
										SDF::opTx(point, glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f)),
										glm::vec2(0.1f, 1.0f)
									),
									SDF::sCylinder(
										SDF::opTx(point, glm::vec3(-0.5f, 0.0f, 0.5f), glm::vec3(0.0f, 0.0f, 0.0f)),
										glm::vec2(0.1f, 1.0f)
									)
								),
								SDF::sCylinder(
									SDF::opTx(point, glm::vec3(0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)),
									glm::vec2(0.1f, 1.0f)
								)
							),
							SDF::sCylinder(
								SDF::opTx(point, glm::vec3(-0.5f, 0.0f, -0.5f), glm::vec3(0.0f, 0.0f, 0.0f)),
								glm::vec2(0.1f, 1.0f)
							)
						),
						SDF::sCylinder(
							SDF::opTx(point, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(90.0f, 0.0f, 0.0f)),
							glm::vec2(0.1f, 1.0f)
						)
					),
					SDF::sCylinder(
						SDF::opTx(point, glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(90.0f, 0.0f, 0.0f)),
						glm::vec2(0.1f, 1.0f)
					)
				),
				SDF::sCylinder(
					SDF::opTx(point, glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 90.0f)),
					glm::vec2(0.1f, 1.0f)
				)
			),
			SDF::sCylinder(
				SDF::opTx(point, glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 90.0f)),
				glm::vec2(0.1f, 1.0f)
			)
		),	
		boxMinusCylinder(point, c)
	);
}


float
SDF::scene (
	glm::vec3 point,
	SDF::Config c
) {
	return boxMinusCylinderMinusCorners(SDF::opRep(point, glm::vec3(1, 1, 1)), c);
}
