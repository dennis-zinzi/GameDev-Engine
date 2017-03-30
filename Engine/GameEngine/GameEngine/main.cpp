#include "../Renderer/Renderer.h"

#pragma comment(lib, "nclgl.lib")
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

	//Set window to render stuff in
	w.SetRenderer(&renderer);

	//Create world objects here
	//TODO - Load from text files in Game dir to dynamically create them
	Mesh *m = Mesh::LoadMeshFile(MESH_DIR"cube.asciimesh");
	Shader *s = new Shader(SHADER_DIR"BasicVert.glsl", SHADER_DIR"BasicFrag.glsl");

	RenderObject ro(m, s);
	ro.setModelMatrix(Matrix4::Translation(Vector3(0, 0, 0)) * Matrix4::Scale(Vector3(1, 1, 1)));

	renderer.AddRenderObject(ro);

	renderer.setProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.setViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, -20), Vector3(0, 0, -10)));


	while(w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		float msec = w.GetTimer()->GetTimedMS();

		
		ro.setModelMatrix(ro.getModelMatrix() * Matrix4::Rotation(1.0f * msec, Vector3(0, 1, 1)));

		//Graphics update
		renderer.UpdateScene(msec);
		renderer.ClearBuffers();
		renderer.RenderScene();
		renderer.SwapBuffers();
	}

	//TODO - delete all pointers to avoid memory leaks
	delete &renderer;
	

	return 0;
}