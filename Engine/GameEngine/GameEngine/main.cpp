#include "../Renderer/Renderer.h"
#include "../Renderer/OBJMesh.h"

#pragma comment(lib, "Renderer.lib")

#define SHADER_DIR "../Assets/Shaders/"
#define MESH_DIR "../Assets/Meshes/"


int main(){
	//Initialize window
	Window w("GameDev Engine", 1200, 720);
	if(!w.HasInitialised()) {
		return -1;
	}

	//Initialize renderer
	Renderer renderer(w);
	if(!renderer.HasInitialised()) {
		return -1;
	}

	//Create world objects here
	//TODO - Load from text files in Game dir to dynamically create them
	Mesh *m = Mesh::LoadMeshFile(MESH_DIR"cube.asciimesh");

	Shader *s = new Shader(SHADER_DIR"BasicVert.glsl", SHADER_DIR"BasicFrag.glsl");

	RenderObject ro(m, s);
	ro.setModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));
	RenderObject ro1(m, s);
	ro1.setModelMatrix(Matrix4::Translation(Vector3(-1, 0, -5)) * Matrix4::Scale(Vector3(1, 1, 1)));

	Mesh *segMesh = Mesh::GenerateSegmentedQuads(5);
	Shader *segShade = new Shader(SHADER_DIR"segmentVert.glsl", SHADER_DIR"BasicFrag.glsl");

	RenderObject segObj(segMesh, segShade);
	segObj.setModelMatrix(Matrix4::Translation(Vector3(0, -3, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));


	RenderObject body(m, s);
	body.setModelMatrix(Matrix4::Translation(Vector3(0, -3.0f, -30.0f)) * Matrix4::Scale(Vector3(1.0f, 2.0f, 1)));
	renderer.AddRenderObject(body);

	RenderObject head(m, s);
	head.setModelMatrix(Matrix4::Translation(Vector3(0, 2.0f, 0.0f)) * Matrix4::Scale(Vector3(0.5f, 0.5f, 1)));
	body.AddChild(head);

	RenderObject lArm(m, s);
	lArm.setModelMatrix(Matrix4::Translation(Vector3(-2.5f, -0.7f, -0.0f)) * Matrix4::Scale(Vector3(0.6f, 1.7f, 0.4f)));
	body.AddChild(lArm);

	RenderObject rArm(m, s);
	rArm.setModelMatrix(Matrix4::Translation(Vector3(2.5f, -0.7f, -0.0f)) * Matrix4::Scale(Vector3(0.6f, 1.7f, 0.4f)));
	body.AddChild(rArm);

	RenderObject lLeg(m, s);
	lLeg.setModelMatrix(Matrix4::Translation(Vector3(-0.8f, -2.5f, -0.0f)) * Matrix4::Scale(Vector3(0.6f, 1.2f, 0.5f)));
	body.AddChild(lLeg);

	RenderObject rLeg(m, s);
	rLeg.setModelMatrix(Matrix4::Translation(Vector3(0.8f, -2.5f, -0.0f)) * Matrix4::Scale(Vector3(0.6f, 1.2f, 0.5f)));
	body.AddChild(rLeg);




	//renderer.AddRenderObject(ro);
	//renderer.AddRenderObject(ro1);
	//renderer.AddRenderObject(segObj);

	renderer.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	//renderer.setViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, -20), Vector3(0, 0, -10)));
	renderer.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	//Physics physics;
	//renderer.DrawPlane(physics.getRigidBodies()[0]);
	//btRigidBody* sphere = physics.addSphere(10.0f, 0.0f, 0.0f, -10.0f, 1.0f);
	//renderer.DrawSphere(sphere);

	while(w.UpdateWindow() && !Keyboard::KeyDown(KEY_ESCAPE)){
		float msec = w.GetTimer()->GetTimedMS();

		Matrix4 rot = Matrix4::Rotation(0.5f * msec, Vector3(0, 1, 0));
		Matrix4 negRot = Matrix4::Rotation(0.1f * -msec, Vector3(0, 1, 0));
		
		//body.setModelMatrix(body.getModelMatrix() * Matrix4::Rotation(0.01f * msec, Vector3(0, 1, 0)));
		//body.setWorldTransform(body.getWorldTransform() * Matrix4::Rotation(0.01f * msec, Vector3(0, 1, 0)));
		//rLeg.setModelMatrix(rLeg.getModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(1, 0, 0)));

		if(Keyboard::KeyDown(KEY_D)){
			body.setModelMatrix(body.getModelMatrix() * Matrix4::Translation(Vector3(0.01f, 0, 0)));
			renderer.SetViewMatrix(/*renderer.GetViewMatrix() * */Matrix4::Translation(Vector3(1, 0, 0)));
		}
		if(Keyboard::KeyDown(KEY_A)){
			body.setModelMatrix(body.getModelMatrix() * Matrix4::Translation(Vector3(-0.01f, 0, 0)));
			renderer.SetViewMatrix(body.getModelMatrix());///*renderer.GetViewMatrix() * */Matrix4::Translation(Vector3(-1, 0, 0)));
		}
		if(Keyboard::KeyDown(KEY_W)){
			lLeg.setModelMatrix(lLeg.getModelMatrix() * Matrix4::Rotation(0.1f * -msec, Vector3(1, 0, 0)));
			renderer.SetViewMatrix(body.getModelMatrix());///*renderer.GetViewMatrix() * */Matrix4::Translation(Vector3(-1, 0, 0)));
		}

		//rLeg.setModelMatrix(rLeg.getWorldTransform() * Matrix4::Rotation(0.1f * -msec, Vector3(0, 1, 0)));
		//lLeg.setModelMatrix(lLeg.getModelMatrix() * Matrix4::Rotation(0.1f * -msec, Vector3(1, 0, 0)));
		//body.getChildren()[0]->setWorldTransform(body.getChildren()[0]->getWorldTransform() * Matrix4::Rotation(0.1f * -msec, Vector3(0, 1, 0)));
		//body.getChildren()[1]->setWorldTransform(body.getChildren()[1]->getWorldTransform() * Matrix4::Rotation(0.1f * -msec, Vector3(1, 0, 0)));
		//body.getChildren()[2]->setWorldTransform(body.getChildren()[2]->getWorldTransform() * Matrix4::Rotation(0.1f * msec, Vector3(1, 0, 0)));

		//Graphics update
		
		renderer.UpdateScene(msec);
		renderer.ClearBuffers();
		renderer.RenderScene();
		renderer.SwapBuffers();
	}

	//TODO - delete all pointers to avoid memory leaks
	delete m;
	delete s;

	return 0;
}