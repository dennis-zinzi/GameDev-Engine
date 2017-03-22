#include "../Renderer/Renderer.h"

#define SHADER_DIR "../Assets/Shaders/"
#define MESH_DIR "../Assets/Meshes/"

void RenderingCycle(Renderer &r, float msec){
	r.UpdateScene(msec);
	r.ClearBuffers();
	r.RenderScene();
	r.SwapBuffers();
}

int main(){
	//Initialize window
	Window w("GameDev Engine", 1200, 720);

	//Initialize renderer
	Renderer renderer(w);

	Mesh *m = Mesh::LoadMeshFile(MESH_DIR"cube.asciimesh");
	Shader *s = new Shader(SHADER_DIR"BasicVert.glsl", SHADER_DIR"BasicFrag.glsl");

	RenderObject ro(m, s);
	ro.setModelMatrix(Matrix4::Translation(Vector3(0, 0, 0)) * Matrix4::Scale(Vector3(1, 1, 1)));

	renderer.AddRenderObject(ro);

	renderer.setProjectionMatrix(Matrix4::Perspective(1, 100, 1.33f, 45.0f));
	renderer.setViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, -20), Vector3(0, 0, -10)));


	while(w.UpdateWindow()){
		float msec = w.GetTimer()->GetTimedMS();

		
		ro.setModelMatrix(ro.getModelMatrix() * Matrix4::Rotation(0.1f * msec, Vector3(0, 1, 1)));

		//Graphics update
		RenderingCycle(renderer, msec);
	}


	return 0;
}