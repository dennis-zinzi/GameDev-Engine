#include "RenderObject.h"

RenderObject::RenderObject(){
	mesh = NULL;
	shader = NULL;
	texture = NULL;
	parent = NULL;
}


RenderObject::RenderObject(Mesh *m, Shader *s, GLuint tex){
	mesh = m;
	shader = s;
	texture = tex;
	parent = NULL;
}


RenderObject::~RenderObject(){
}


void RenderObject::Update(float msec){
	if(parent){
		//worldTransform = parent->modelMatrix * modelMatrix;
		worldTransform = parent->worldTransform * modelMatrix;
	}
	else{
		worldTransform = modelMatrix;
	}

	for(auto child : children){
		child->Update(msec);
	}
}


void RenderObject::Draw() const{
	if(mesh){
		mesh->Draw();
	}
}