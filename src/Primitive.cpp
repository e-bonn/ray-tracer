#include "Primitive.hpp"
#include <algorithm>
#include <iostream>
#include "polyroots.hpp"

using namespace glm;
using namespace std;

Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
	delete nonhier;
}

float Sphere::intersection(Ray *ray)
{
	return nonhier->intersection(ray);
}

glm::vec3 Sphere::getNormal(vec3 pt)
{
	return nonhier->getNormal(pt);
}

Cube::~Cube()
{
	delete nonhier;
}

float Cube::intersection(Ray *ray)
{
	return nonhier->intersection(ray);
}

glm::vec3 Cube::getNormal(vec3 pt)
{
	return nonhier->getNormal(pt);
}

NonhierSphere::~NonhierSphere()
{
}

float NonhierSphere::intersection(Ray *ray)
{
	glm::vec3 look = (ray->eye - m_pos);

	float a = glm::dot(ray->direction, ray->direction);
	float b = 2*(glm::dot(ray->direction, look));
	float c = glm::dot(look,look) - m_radius*m_radius;

	double roots[2];
	
	float epsilon = 0.001f;

	int num = quadraticRoots(a,b,c,roots);

	if(num == 0)
		return INT_MAX;
	else if (num == 1)
	{
		if(roots[0] > 0) return roots[0];
		else return INT_MAX;
	}
	else if(num == 2)
	{
		if(roots[0] > 0 && roots[1] > 0) return std::min(roots[0], roots[1]);
		else if(roots[0] > 0) return roots[0];
		else if(roots[1] > 0) return roots[1];
		else return INT_MAX;
	}
}

glm::vec3 NonhierSphere::getNormal(vec3 pt)
{
	intersectionFaceNormal = pt - m_pos;
	intersectionFaceNormal = vec3(2*intersectionFaceNormal.x, 2*intersectionFaceNormal.y, 2*intersectionFaceNormal.z);
	return intersectionFaceNormal;
}

NonhierBox::~NonhierBox()
{
}

float NonhierBox::intersection(Ray *ray)
{
	glm::vec3 plane_normals[6];
	glm::vec3 plane_pts[6];
	float plane_t[6];
	float min = INT_MAX;
	
	plane_normals[0] = vec3(0,0,-ray->direction.z);
	plane_pts[0] = bounds[0];
	
	plane_normals[1] = vec3(-ray->direction.x,0,0);
	plane_pts[1] = bounds[3];
	
	plane_normals[2] = vec3(0,-ray->direction.y,0);
	plane_pts[2] = bounds[3];
	
	plane_normals[3] = vec3(0,-ray->direction.y,0);
	plane_pts[3] = bounds[6];
	
	plane_normals[4] = vec3(-ray->direction.x,0,0);
	plane_pts[4] = bounds[1];
	
	plane_normals[5] = vec3(0,0,-ray->direction.z);
	plane_pts[5] = bounds[5];
	
	for(int i = 0; i < 6; i++)
	{
		float epsilon = 0.0001f;
		plane_t[i] = dot(plane_normals[i],plane_pts[i]-ray->eye)/dot(plane_normals[i],ray->direction);
		glm::vec3 intersectionPt = ray->eye + (plane_t[i] * ray->direction);
		if(plane_t[i] < min && plane_t[i] > 0 && 
			intersectionPt.x >= bounds[0].x-epsilon && intersectionPt.y >= bounds[0].y-epsilon && intersectionPt.z >= bounds[0].z-epsilon &&
			intersectionPt.x <= bounds[7].x+epsilon && intersectionPt.y <= bounds[7].y+epsilon && intersectionPt.z <= bounds[7].z+epsilon)
		{
			min = plane_t[i];
			intersectionFaceNormal = plane_normals[i];
		}
	}
	
	return min;
}

glm::vec3 NonhierBox::getNormal(vec3 pt)
{
	return intersectionFaceNormal;
}



