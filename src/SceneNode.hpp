#pragma once

#include "Material.hpp"
#include "PhongMaterial.hpp"
#include "Primitive.hpp"

#include <glm/glm.hpp>

#include <list>
#include <string>
#include <iostream>

enum class NodeType {
	SceneNode,
	GeometryNode,
	JointNode
};

struct IntersectionData {
	IntersectionData() {
		pmat = nullptr;
		t = INT_MAX;
		prim = nullptr;
		nodeId = -1;
	}
	IntersectionData(PhongMaterial *p, float o_t, Primitive *pr, unsigned int id) 
		: pmat(p), t(o_t), prim(pr), nodeId(id) {}
	PhongMaterial *pmat;
	Primitive *prim;
	float t;
	unsigned int nodeId;
    glm::vec3 pt;
};

class SceneNode {
public:
    SceneNode(const std::string & name);

	SceneNode(const SceneNode & other);

    virtual ~SceneNode();
    
	int totalSceneNodes() const;
    
    const glm::mat4& get_transform() const;
    const glm::mat4& get_inverse() const;
    
    void set_transform(const glm::mat4& m);
    
    void add_child(SceneNode* child);
    
    void remove_child(SceneNode* child);

	//-- Transformations:
    void rotate(char axis, float angle);
    void scale(const glm::vec3& amount);
    void translate(const glm::vec3& amount);
    
    void intersectsWithAnyNode(Ray *ray, SceneNode *node, IntersectionData &idata, IntersectionData exclude, glm::mat4 transSoFar, glm::mat4 rottransSoFar);

	friend std::ostream & operator << (std::ostream & os, const SceneNode & node);

    // Transformations
    glm::mat4 trans;
    glm::mat4 invtrans;
    glm::mat4 rottrans;
    
    std::list<SceneNode*> children;

	NodeType m_nodeType;
	std::string m_name;
	unsigned int m_nodeId;

private:
	// The number of SceneNode instances.
	static unsigned int nodeInstanceCount;
};
