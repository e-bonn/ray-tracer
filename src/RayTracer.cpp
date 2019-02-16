#include <glm/ext.hpp>
#include "cs488-framework/MathUtils.hpp"

#include "GeometryNode.hpp"
#include <math.h>
#include <thread>
#include <vector>
#include "RayTracer.hpp"

using namespace std;
using namespace glm;

static const int MAX_DEPTH = 4;

RayTracer::RayTracer(	glm::mat4 trans1, glm::mat4 rot, glm::mat4 scale, 
						glm::mat4 trans2, glm::vec3 ambient, glm::vec3 eye,
						SceneNode* root)
	: 	m_trans1(trans1), 
		m_rot(rot),
		m_scale(scale),
		m_trans2(trans2),
		m_ambient(ambient),
		m_eye(eye),
		m_root(root)
{
}

RayTracer::~RayTracer()
{
}

void RayTracer::intersectsWithAny(Ray *ray, IntersectionData &idata, IntersectionData exclude)
{	
	m_root->intersectsWithAnyNode(ray, m_root, idata, exclude);
}

double RayTracer::getLightFactorKD(const Light *light, Ray *lightray, const IntersectionData idata)
{
	double r = glm::length(light->position - lightray->eye);
	double falloffSum = light->falloff[0] + light->falloff[1] * r + light->falloff[2] * r * r;
	double lightFactor = dot(normalize(light->position - lightray->eye), normalize(idata.prim->getNormal(lightray->eye)));

	lightFactor /= falloffSum;
	return lightFactor;
}

double RayTracer::getLightFactorKS(const Light *light, Ray *lightray, Ray *ray, const IntersectionData idata)
{
	vec3 normal = idata.prim->getNormal(lightray->eye);
	Ray v(lightray->eye, ray->eye-lightray->eye);
	
	double size = glm::length(light->position - lightray->eye);
	double falloffSum = light->falloff[0] + light->falloff[1] * size + light->falloff[2] * size * size;
	
	vec3 r = 2*dot(normalize(lightray->direction),normalize(normal))*normalize(normal) - normalize(lightray->direction);

	double lightFactor = pow(dot(normalize(r),normalize(v.direction)),idata.pmat->m_shininess);
	lightFactor /= falloffSum;
	return lightFactor;
}


bool RayTracer::lightObstructed(Ray *lightRay, IntersectionData idata)
{
	IntersectionData other_idata;
	intersectsWithAny(lightRay, other_idata, idata);
	
	if(other_idata.pmat) return true;
	else return false;
}

glm::vec4 RayTracer::calculateWorldCoord(glm::vec4 coord)
{
	return m_trans2 * m_rot * m_scale * m_trans1 * coord;
}

void RayTracer::shootRay(int x, int y, const std::list<Light *> & lights, Image & image)
{
	IntersectionData idata = IntersectionData();
	vec4 coord = glm::vec4(x,y,0,1);

	vec4 worldCoord = calculateWorldCoord(coord);

	Ray ray = Ray(m_eye, vec3(worldCoord)-m_eye);
	double overallShininess = 1;
	for(int depth = 0; depth < MAX_DEPTH; depth++)
	{
		vec3 colour(0,0,0);
		vec3 normal(0,0,0);
		float epsilon = 0.01f;
		idata = IntersectionData();
		intersectsWithAny(&ray, idata, IntersectionData());
		
		glm::vec3 intersectionPt = ray.eye + (idata.t * ray.direction);

		if(!idata.pmat && depth == 0)
		{
			float backgroundColy = 0.01 * y;
			float backgroundColx = 0.001 * x;
			image(x, y, 0) = 0.0f;
			image(x, y, 1) = backgroundColx;
			image(x, y, 2) = backgroundColy;
			break;
		}
		else if(idata.pmat)
		{
			colour = m_ambient*idata.pmat->m_kd;
			for(const Light * light : lights) {
				Ray lightRay(intersectionPt+epsilon, light->position-(intersectionPt+epsilon));
				if(!lightObstructed(&lightRay, idata))
				{
					double lightFactorKD = getLightFactorKD(light,&lightRay,idata);
					double lightFactorKS = getLightFactorKS(light,&lightRay,&ray,idata);
					if(lightFactorKD >= 0)
					{
						colour += light->colour*lightFactorKD*idata.pmat->m_kd;
					}
					if(lightFactorKS >= 0)
					{
						colour += light->colour*lightFactorKS*idata.pmat->m_ks;
					}
					normal = idata.prim->getNormal(intersectionPt);
					if(depth != 0)
					{
						colour *= overallShininess;
						double shininessPct = (double)idata.pmat->m_shininess/100;
						overallShininess *= shininessPct;
					}
				}
			}
		}
		if(colour == vec3(0,0,0)) break;
		image(x, y, 0) += colour.x;
		image(x, y, 1) += colour.y;
		image(x, y, 2) += colour.z;
		vec3 r = normalize(ray.direction) + 2*dot(normalize(-ray.direction),normalize(normal))*normalize(normal);
		ray = Ray(intersectionPt+epsilon*r, r);
	}
}

void outputPercentage(int percentageDone, int np)
{
	cout << "[" << ((np%2) ? "\\" : "/") << "]" << percentageDone << "%\r" << flush;
}

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
) {

	float d = 100.0f;

	size_t nx = image.height();
	size_t ny = image.width();
	
	float h = 2*d*tan(degreesToRadians(fovy)/2);

	mat4 trans1,scale,rot,trans2;
	rot = mat4(1.0f);
	glm::vec3 wvec = (view-eye)/length(view-eye);
	glm::vec3 uvec = cross(up,wvec)/length(cross(up,wvec));
	glm::vec3 vvec = cross(wvec,uvec);
	trans1 = glm::translate(trans1, vec3(-(float)nx/2,-(float)ny/2,d));
	scale = glm::scale(scale, vec3(-h/nx,-h/ny,1));
	rot = mat4(
		vec4(uvec,0),
		vec4(vvec,0),
		vec4(wvec,0),
		vec4(0,0,0,1)
	);
	trans2 = glm::translate(trans2, eye);

	std::cout << "Calling RayTrace(\n" <<
		  "\t" << *root <<
          "\t" << "Image(width:" << image.width() << ", height:" << image.height() << ")\n"
          "\t" << "eye:  " << glm::to_string(eye) << std::endl <<
		  "\t" << "view: " << glm::to_string(view) << std::endl <<
		  "\t" << "up:   " << glm::to_string(up) << std::endl <<
		  "\t" << "fovy: " << fovy << std::endl <<
          "\t" << "ambient: " << glm::to_string(ambient) << std::endl <<
		  "\t" << "lights{" << std::endl;

	for(const Light * light : lights) {
		std::cout << "\t\t" <<  *light << std::endl;
	}

	std::cout << "\t}" << std::endl;
	std:: cout <<")" << std::endl;

	RayTracer *myRayTracer = new RayTracer(trans1, rot, scale, trans2, ambient, eye, root);

	std::vector<std::thread> myThreads;

	int np = 0;
	for (uint y = 0; y < nx; ++y) {
		outputPercentage(100*y/nx, np++);
		for (uint x = 0; x < ny; ++x) {
			myRayTracer->shootRay(x,y,lights,image);
		}
	}
	outputPercentage(100, np++);
	
	for(std::thread &t : myThreads)
	{
		t.join();
	}

	cout << endl;

	delete myRayTracer;
}
