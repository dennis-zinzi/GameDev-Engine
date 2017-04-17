#include "GameObject.h"

GameObject::GameObject(Renderer &renderer, Physics &physics, Mesh *mesh, Shader *shader, GLuint texture,
	GameObject *parent, Vector3 translation, float rotation, Vector3 rotationAxis, Vector3 scale){

	renderObj = new RenderObject(mesh, shader, texture);
	renderObj->setModelMatrix(Matrix4::Translation(translation) * Matrix4::Rotation(rotation, rotationAxis) * Matrix4::Scale(scale));

	if(parent){
		parent->AddChild(*this);
	}
	else{
		renderer.AddRenderObject(*renderObj);
	}

	Vector3 roPos = renderObj->getWorldTransform().GetPositionVector();//head.getModelMatrix().GetPositionVector();
	Vector3 roDimensions = (roPos * renderObj->getModelMatrix().GetScalingVector()) - roPos;
	physics.addBox(roPos.x, roPos.y, roPos.z, roDimensions.x, roDimensions.y, roDimensions.z, 1.0f);
}