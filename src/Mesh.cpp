#include <iostream>
#include <fstream>

#include <glm/ext.hpp>

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"

using namespace std;
using namespace glm;

#define BOUNDING_VOLUME_TOGGLED 0

Mesh::Mesh( const std::string& fname )
	: m_vertices()
	, m_faces()
{
	std::string code;
	double vx, vy, vz;
	size_t s1, s2, s3;

	std::ifstream ifs( fname.c_str() );
	while( ifs >> code ) {
		if( code == "v" ) {
			ifs >> vx >> vy >> vz;
			m_vertices.push_back( glm::vec3( vx, vy, vz ) );
		} else if( code == "f" ) {
			ifs >> s1 >> s2 >> s3;
			m_faces.push_back( Triangle( s1 - 1, s2 - 1, s3 - 1 ) );
		}
	}
	
	float minx = INT_MAX, miny = INT_MAX, minz = INT_MAX;
	float maxx = INT_MIN, maxy = INT_MIN, maxz = INT_MIN;
	
	for(int i = 0; i < m_vertices.size(); i++)
	{
		if(m_vertices[i].x < minx) minx = m_vertices[i].x;
		if(m_vertices[i].y < miny) miny = m_vertices[i].y;
		if(m_vertices[i].z < minz) minz = m_vertices[i].z;
		
		if(m_vertices[i].x > maxx) maxx = m_vertices[i].x;
		if(m_vertices[i].y > maxy) maxy = m_vertices[i].y;
		if(m_vertices[i].z > maxz) maxz = m_vertices[i].z;
	}
	
	boundingVolume = new NonhierSphere(0.5f*(vec3(minx,miny,minz)+vec3(maxx,maxy,maxz)),0.5f*max(maxx-minx,maxy-miny,maxz-minz));
}

Mesh::~Mesh()
{
	delete boundingVolume;
}

float Mesh::intersection(Ray *ray)
{
	float min = INT_MAX;
	float t, beta, gamma;
	float epsilon = 0.001f;
	
	t = boundingVolume->intersection(ray);
	
	if(t != INT_MAX && BOUNDING_VOLUME_TOGGLED)
	{
		vec3 intersectionPt = ray->eye + t*ray->direction;
		intersectionFaceNormal = intersectionPt-boundingVolume->m_pos;
		return t;
	}

	if(t == INT_MAX) return min;
	
	for(auto &triangle : m_faces)
	{
		vec3 p0 = m_vertices[triangle.v1];
		vec3 p1 = m_vertices[triangle.v2];
		vec3 p2 = m_vertices[triangle.v3];
		mat3 m(
			p1-p0,
			p2-p0,
			-ray->direction
		);
		
		mat3 inv_m = inverse(m);
		vec3 solution = inv_m * (ray->eye-p0);
		
		beta = solution[0];
		gamma = solution[1];
		t = solution[2];
		
		if(t < min && t > epsilon && (beta+gamma) <= 1+epsilon && beta >= epsilon && gamma >= epsilon)
		{
			min = t;
			intersectionFaceNormal = cross(p1-p0,p2-p0);
		}
	}
	
	return min;
}

glm::vec3 Mesh::getNormal(glm::vec3 pt)
{
	return intersectionFaceNormal;
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  out << "mesh {";
  /*
  
  for( size_t idx = 0; idx < mesh.m_verts.size(); ++idx ) {
  	const MeshVertex& v = mesh.m_verts[idx];
  	out << glm::to_string( v.m_position );
	if( mesh.m_have_norm ) {
  	  out << " / " << glm::to_string( v.m_normal );
	}
	if( mesh.m_have_uv ) {
  	  out << " / " << glm::to_string( v.m_uv );
	}
  }

*/
  out << "}";
  return out;
}
