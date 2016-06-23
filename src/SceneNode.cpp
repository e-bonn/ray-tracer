#include "SceneNode.hpp"

#include "cs488-framework/MathUtils.hpp"

#include <iostream>
#include <sstream>
using namespace std;

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/transform.hpp>
#include "GeometryNode.hpp"

using namespace glm;


// Static class variable
unsigned int SceneNode::nodeInstanceCount = 0;


//---------------------------------------------------------------------------------------
SceneNode::SceneNode(const std::string& name)
  : m_name(name),
	m_nodeType(NodeType::SceneNode),
	trans(mat4()),
	invtrans(mat4()),
	m_nodeId(nodeInstanceCount++)
{

}

//---------------------------------------------------------------------------------------
// Deep copy
SceneNode::SceneNode(const SceneNode & other)
	: m_nodeType(other.m_nodeType),
	  m_name(other.m_name),
	  trans(other.trans),
	  invtrans(other.invtrans)
{
	for(SceneNode * child : other.children) {
		this->children.push_front(new SceneNode(*child));
	}
}

//---------------------------------------------------------------------------------------
SceneNode::~SceneNode() {
	for(SceneNode * child : children) {
		delete child;
	}
}

void SceneNode::intersectsWithAnyNode(Ray *ray, SceneNode *node, IntersectionData &idata, IntersectionData exclude/*, glm::mat4 transSoFar, glm::mat4 rottransSoFar*/) {

	// TODO e-bonn -> hierarchy intersection needs to be fixed, doesn't work properly at the moment

/*	float t = INT_MAX;
	
	// transform the eye and direction and then create a new eye .. to be propagated through the children
	vec3 newEye = vec3(invtrans * vec4(ray->eye,1.0f));
	vec3 newDir = vec3(invtrans * vec4(ray->direction,0.0f));
	Ray r(newEye,newDir);
	
	// transSoFar = transSoFar * trans;
	// rottransSoFar = rottransSoFar * rottrans;

	GeometryNode *gnode;
	if(node->m_nodeType == NodeType::GeometryNode)
	{
		gnode = static_cast<GeometryNode*>(node);
		t = gnode->m_primitive->intersection(&r);
		if(t != INT_MAX && node->m_nodeId != exclude.nodeId && t < exclude.t && t < idata.t)
		{
			idata.pt = r.eye + (idata.t * r.direction);
			idata.pt = vec3(trans * vec4(idata.pt,1.0f));
			gnode->m_primitive->intersectionFaceNormal = vec3(transpose(inverse(rottrans)) * vec4(gnode->m_primitive->intersectionFaceNormal,0.0f));
			idata.pmat = static_cast<PhongMaterial*>(gnode->m_material);
			idata.t = t;
			idata.prim = gnode->m_primitive;
			idata.nodeId = node->m_nodeId;
		}
	}
	//cout << "node_id: " << node->m_nodeId << ", idata.pmat: " << idata.pmat << ", t: " << idata.t << endl;
	for(SceneNode *child : node->children)
	{
		child->intersectsWithAnyNode(&r, child, idata, exclude, transSoFar, rottransSoFar);
	}
	node->intersectsWithAnyNode(ray, node, idata, exclude);*/

	float t = INT_MAX;
	
	// transform the eye and direction and then create a new eye .. to be propagated through the children
	vec3 newEye = vec3(invtrans * vec4(ray->eye,1.0f));
	vec3 newDir = vec3(invtrans * vec4(ray->direction,1.0f));
	Ray r(newEye,newDir);
	
	GeometryNode *gnode;
	if(node->m_nodeType == NodeType::GeometryNode)
	{
		gnode = static_cast<GeometryNode*>(node);
		t = gnode->m_primitive->intersection(&r);
		if(t != INT_MAX && node->m_nodeId != exclude.nodeId && t < exclude.t && t < idata.t)
		{
			gnode->m_primitive->intersectionFaceNormal = vec3(invtrans * vec4(gnode->m_primitive->intersectionFaceNormal,1.0f));
			idata.pmat = static_cast<PhongMaterial*>(gnode->m_material);
			idata.t = t;
			idata.prim = gnode->m_primitive;
			idata.nodeId = node->m_nodeId;
		}
	}
	//cout << "node_id: " << node->m_nodeId << ", idata.pmat: " << idata.pmat << ", t: " << idata.t << endl;
	for(SceneNode *child : node->children)
	{
		child->intersectsWithAnyNode(&r, child, idata, exclude);
	}
}

//---------------------------------------------------------------------------------------
void SceneNode::set_transform(const glm::mat4& m) {
	trans = m;
	invtrans = glm::inverse(m);
}

//---------------------------------------------------------------------------------------
const glm::mat4& SceneNode::get_transform() const {
	return trans;
}

//---------------------------------------------------------------------------------------
const glm::mat4& SceneNode::get_inverse() const {
	return invtrans;
}

//---------------------------------------------------------------------------------------
void SceneNode::add_child(SceneNode* child) {
	children.push_back(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::remove_child(SceneNode* child) {
	children.remove(child);
}

//---------------------------------------------------------------------------------------
void SceneNode::rotate(char axis, float angle) {
	vec3 rot_axis;

	switch (axis) {
		case 'x':
			rot_axis = vec3(1,0,0);
			break;
		case 'y':
			rot_axis = vec3(0,1,0);
	        break;
		case 'z':
			rot_axis = vec3(0,0,1);
	        break;
		default:
			break;
	}
	mat4 rot_matrix = glm::rotate(degreesToRadians(angle), rot_axis);
	set_transform( rot_matrix * trans );
	rottrans = rot_matrix * rottrans;
}

//---------------------------------------------------------------------------------------
void SceneNode::scale(const glm::vec3 & amount) {
	set_transform( glm::scale(amount) * trans );
}

//---------------------------------------------------------------------------------------
void SceneNode::translate(const glm::vec3& amount) {
	set_transform( glm::translate(amount) * trans );
	rottrans = glm::translate(amount) * rottrans;
}


//---------------------------------------------------------------------------------------
int SceneNode::totalSceneNodes() const {
	return nodeInstanceCount;
}

//---------------------------------------------------------------------------------------
std::ostream & operator << (std::ostream & os, const SceneNode & node) {

	//os << "SceneNode:[NodeType: ___, name: ____, id: ____, isSelected: ____, transform: ____"
	switch (node.m_nodeType) {
		case NodeType::SceneNode:
			os << "SceneNode";
			break;
		case NodeType::GeometryNode:
			os << "GeometryNode";
			break;
		case NodeType::JointNode:
			os << "JointNode";
			break;
	}
	os << ":[";

	os << "name:" << node.m_name << ", ";
	os << "id:" << node.m_nodeId;

	os << "]\n";
	return os;
}
