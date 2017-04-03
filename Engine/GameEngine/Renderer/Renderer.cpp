#include "Renderer.h"

Renderer::Renderer(Window &window) : OGLRenderer(window){
	time = 0.0f;

	//Load textures here

	//Enable depth test
	glEnable(GL_DEPTH_TEST);

	//Enable Alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	init = true;
}

Renderer::~Renderer(){
	//Delete textures in here

	//Delete all render objects
	//for(auto obj : objectsToRender){
	//	delete obj;
	//}
}


void Renderer::RenderObj(const RenderObject &ro){
	modelMatrix = ro.getWorldTransform();

	if(ro.getShader() && ro.getMesh()){
		GLuint program = ro.getShader()->GetShaderProgram();

		glUseProgram(program);

		UpdateShaderMatrices(program);

		//Set up shader uniforms here

		//Set up time uniform
		glUniform1f(glGetUniformLocation(program, "time"), time);

		//End setting up shaders

		ro.Draw();
	}

	//Render any children
	for(auto child : ro.getChildren()){
		RenderObj(*child);
	}
}


void Renderer::RenderScene(){
	//Activate/Bind textures here

	for(auto ro : objectsToRender){
		RenderObj(*ro);
	}
}

void Renderer::UpdateScene(float msec){
	time += msec / 1000;

	for(auto obj : objectsToRender){
		obj->Update(msec);
	}
}

//(Might move to RenderObject class)
GLuint Renderer::LoadTexture(string filename){
	return SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}