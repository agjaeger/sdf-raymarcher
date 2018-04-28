
#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/component_wise.hpp>

namespace SDF {
	struct Config {
		glm::vec3 skyColor = glm::vec3(0,0,0);
		
		glm::mat4 camera;
		
		int renderWidth = 480;
		int renderHeight = 480;
		float epsilon =  0.001f;
		float rayMax = 1000.0f;
		float rayMin = 0.001f;
		int rayMaxSteps = 100;
		int fov = 90;
	};
	
	struct Intersection {
		float dist;
		glm::vec3 color;
	};
	
	// implement this
	float scene (glm::vec3 point);
	
	// helper functions
	Intersection rayMarch (
		glm::vec3 rayOrigin, 
		glm::vec3 rayDir,
		SDF::Config c
	);
	
	glm::mat4 lookAt (
		glm::vec3 from,
		glm::vec3 to,
		glm::vec3 up
	);
	
	glm::vec3 estimateNormal (glm::vec3 point, Config c);

	// sdf object definitions
	float sSphere (glm::vec3 point);
	float usBox (glm::vec3 point, glm::vec3 boxSize);	
	
	// sdf object op definitions
	float opUnion (float d1, float d2);
	float opSubtraction (float d1, float d2);
	float opIntersection (float d1, float d2);
	glm::vec3 opTx (glm::vec3 p, glm::vec3 t);
	glm::vec3 opRep (glm::vec3 p, glm::vec3 c);
};
