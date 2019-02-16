#pragma once

#include <glm/glm.hpp>

#include "SceneNode.hpp"
#include "Light.hpp"
#include "Image.hpp"
#include "Primitive.hpp"
#include "PhongMaterial.hpp"

void RayTrace(
		// What to render
		SceneNode * root,

		// Image to write to, set to a given width and height
		Image & image,

		// Viewing parameters
		const glm::vec3 & eye,
		const glm::vec3 & view,
		const glm::vec3 & up,
		double fovy,

		// Lighting parameters
		const glm::vec3 & ambient,
		const std::list<Light *> & lights
);

// todo ebonn
class RayTracer
{
public:

	RayTracer(	glm::mat4 trans1, glm::mat4 rot, glm::mat4 scale, 
				glm::mat4 trans2, glm::vec3 ambient, glm::vec3 eye,
				SceneNode *root);
	~RayTracer();

	void shootRay(int x, int y, const std::list<Light *> & lights, Image & image);

	glm::vec4 calculateWorldCoord(glm::vec4 coord);

private:

	glm::mat4 m_trans1;
	glm::mat4 m_rot;
	glm::mat4 m_scale;
	glm::mat4 m_trans2;
	glm::vec3 m_ambient;
	glm::vec3 m_eye;

	SceneNode *m_root;

	void intersectsWithAny(Ray *ray, IntersectionData &idata, IntersectionData exclude);
	double getLightFactorKD(const Light *light, Ray *lightray, const IntersectionData idata);
	double getLightFactorKS(const Light *light, Ray *lightray, Ray *ray, const IntersectionData idata);
	bool lightObstructed(Ray *lightRay, IntersectionData idata);

};
