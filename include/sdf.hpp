
#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/component_wise.hpp>

namespace SDF {
	struct Config {
		glm::vec3 skyColor = glm::vec3(0,0,0);
		
		glm::vec3 eye = glm::vec3(0, 0, 1);
		glm::vec3 up = glm::vec3(0, 1, 0);
		glm::vec3 right = glm::vec3(1, 0, 0);
		
		int renderWidth = 480;
		int renderHeight = 480;
		float epsilon =  0.001f;
		float rayMax = 1000.0f;
		float rayMin = 0.001f;
		int rayMaxSteps = 5;
	};
	
	// implement this
	float scene (glm::vec3 point);
	
	// helper functions
	float rayMarch (
		glm::vec3 rayOrigin, 
		glm::vec3 rayDir,
		float u,
		float v, 
		SDF::Config c
	);
	
	glm::vec3 estimateNormal (glm::vec3 point, Config c);
	
	// sdf object definitions
	float sphere (glm::vec3 point);	
};
