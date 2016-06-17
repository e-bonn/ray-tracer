#pragma once

#include <glm/glm.hpp>

struct Ray {
  Ray() {}
  Ray(glm::vec3 e, glm::vec3 d) : eye(e), direction(d) {}
  glm::vec3 eye;
  glm::vec3 direction;
};


class Primitive {
public:
  virtual ~Primitive();
  virtual float intersection(Ray *ray) = 0;
  virtual glm::vec3 getNormal(glm::vec3 pt) = 0;
  
  glm::vec3 intersectionFaceNormal;
};

class NonhierSphere : public Primitive {
public:
  NonhierSphere(const glm::vec3& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual float intersection(Ray *ray);
  virtual glm::vec3 getNormal(glm::vec3 pt);

  glm::vec3 m_pos;
  double m_radius;
};

class NonhierBox : public Primitive {
public:
  NonhierBox(const glm::vec3& pos, double size)
    : m_pos(pos), m_size(size)
  {
	bounds[0] = m_pos;
	bounds[1] = glm::vec3(m_pos.x, m_pos.y, m_pos.z + m_size);
	bounds[2] = glm::vec3(m_pos.x, m_pos.y + m_size, m_pos.z);
	bounds[3] = glm::vec3(m_pos.x + m_size, m_pos.y, m_pos.z);
	bounds[4] = glm::vec3(m_pos.x, m_pos.y + m_size, m_pos.z + m_size);
	bounds[5] = glm::vec3(m_pos.x + m_size, m_pos.y, m_pos.z + m_size);
	bounds[6] = glm::vec3(m_pos.x + m_size, m_pos.y + m_size, m_pos.z);
	bounds[7] = glm::vec3(m_pos.x + m_size, m_pos.y + m_size, m_pos.z + m_size);
  }
  
  virtual ~NonhierBox();
  virtual float intersection(Ray *ray);
  virtual glm::vec3 getNormal(glm::vec3 pt);

  glm::vec3 m_pos;
  double m_size;
  glm::vec3 bounds[8];
};

class Sphere : public Primitive {
public:
  Sphere()
  {
  	nonhier = new NonhierSphere(glm::vec3(0,0,0),1);
  }
  virtual ~Sphere();
  virtual float intersection(Ray *ray);
  virtual glm::vec3 getNormal(glm::vec3 pt);
  
  NonhierSphere *nonhier;
};

class Cube : public Primitive {
public:
  Cube()
  {
	nonhier = new NonhierBox(glm::vec3(0,0,0),1);
  }
  virtual ~Cube();
  virtual float intersection(Ray *ray);
  virtual glm::vec3 getNormal(glm::vec3 pt);
  
  NonhierBox *nonhier;
};
