#include "Renderer.h"
#include "common.h"

Renderer::Renderer(Window &window) : OGLRenderer(window){
	time = 0.0f;
	root = new RenderObject(nullptr, new Shader(SHADER_PATH"BasicVert.glsl", SHADER_PATH"BasicFrag.glsl"));
	camera = new Camera;
	//camera->SetPosition(Vector3(0.0f, 30.0f, 175.0f));

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

	//delete root;

	//Delete all render objects
	//for(auto obj : objectsToRender){
	//	delete obj;
	//}
}


void Renderer::RenderRenderObj(const RenderObject &ro){
	modelMatrix = ro.getWorldTransform();

	if(ro.getShader() && ro.getMesh()){
		GLuint program = ro.getShader()->GetShaderProgram();

		glUseProgram(program);

		//Set up shader uniforms here
		glUniformMatrix4fv(glGetUniformLocation(program, "transforms[0]"), 1, false,
			(float*)&Matrix4::Rotation(10.0f, Vector3(0.0f, 1.0f, 0.0f)));
		glUniformMatrix4fv(glGetUniformLocation(program, "transforms[1]"), 1, false,
			(float*)&Matrix4::Rotation(20.0f, Vector3(0.0f, 1.0f, 0.0f)));
		glUniformMatrix4fv(glGetUniformLocation(program, "transforms[2]"), 1, false,
			(float*)&Matrix4::Rotation(50.0f, Vector3(0.0f, 1.0f, 0.0f)));
		glUniformMatrix4fv(glGetUniformLocation(program, "transforms[3]"), 1, false,
			(float*)&Matrix4::Rotation(90.0f, Vector3(0.0f, 1.0f, 0.0f)));
		glUniformMatrix4fv(glGetUniformLocation(program, "transforms[4]"), 1, false,
			(float*)&Matrix4::Rotation(130.0f, Vector3(0.0f, 1.0f, 0.0f)));

		//Set up time uniform
		glUniform1f(glGetUniformLocation(program, "time"), time);

		//End setting up shaders

		//Set up MVP matricies
		UpdateShaderMatrices(program);
		ro.Draw();
	}

	//Render any children
	for(auto child : ro.getChildren()){
		RenderRenderObj(*child);
	}
}


void Renderer::RenderScene(){
	//Activate/Bind textures here
	RenderRenderObj(*root);

	//for(auto ro : objectsToRender){
	//	RenderRenderObj(*ro);
	//}
}

void Renderer::UpdateScene(float msec){
	time += msec / 1000;

	//for(auto obj : objectsToRender){
	//	obj->Update(msec);
	//}
	camera->UpdateCamera(time*0.1f);
	viewMatrix = camera->BuildViewMatrix();
	root->Update(msec);
}

//(Might move to RenderObject class)
GLuint Renderer::LoadTexture(string filename){
	return SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
}

/**
 * Draws a sphere using OpenGL
 */
void Renderer::DrawSphere(btRigidBody *sphere){
	if(sphere->getCollisionShape()->getShapeType() != SPHERE_SHAPE_PROXYTYPE){
		//If not a sphere, nothing to render here
		return;
	}

	//Set sphere color
	glColor3f(0.5f, 0.5f, 0.5f);
	
	float radius = ((btSphereShape*)sphere->getCollisionShape())->getRadius();
	
	//Get translation/rotation
	btTransform t;
	sphere->getMotionState()->getWorldTransform(t);

	float mat[16];
	t.getOpenGLMatrix(mat);
	
	glPushMatrix();
	
	//Multiplies mvp by model matrix
	glMultMatrixf(mat);
	//GLUquadric *quad = gluNewQuadric();
	//gluSphere(quad, radius, 20.0f, 20.0f);
	
	glPopMatrix();
}


/**
* Draws a plane using OpenGL
*/
void Renderer::DrawPlane(btRigidBody *plane){
	if(plane->getCollisionShape()->getShapeType() != STATIC_PLANE_PROXYTYPE){
		//If not a plane, nothing to render here
		return;
	}

	////Set plane color
	//glColor3f(0.5f, 0.5f, 0.5f);
	//
	////Get translation/rotation
	//btTransform t;
	//plane->getMotionState()->getWorldTransform(t);

	//float mat[16];
	//t.getOpenGLMatrix(mat);

	//glPushMatrix();

	////Multiplies mvp by model matrix
	//glMultMatrixf(mat);
	//{
	//	glBegin(GL_QUADS);
	//	glVertex3f(-1000.0f, 0, 1000.0f);
	//	glVertex3f(-1000.0f, 0, -1000.0f);
	//	glVertex3f(1000.0f, 0, -1000.0f);
	//	glVertex3f(1000.0f, 0, 1000.0f);
	//	glEnd();
	//}
	////GLUquadric *quad = gluNewQuadric();
	////gluSphere(quad, radius, 20.0f, 20.0f);

	//glPopMatrix();

	Mesh *m = Mesh::LoadMeshFile(MESH_PATH"cube.asciimesh");
	Shader *s = new Shader(SHADER_PATH"BasicVert.glsl", SHADER_PATH"BasicFrag.glsl");
	
}