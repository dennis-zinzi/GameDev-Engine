#pragma once

#include "../NCLGL/nclgl/OGLRenderer.h"
#include "../NCLGL/nclgl/Camera.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")

class Renderer : public OGLRenderer{
	public:
		Renderer(Window &parent);
		~Renderer();

		virtual void RenderRenderObj(const RenderObject &ro);
		virtual void RenderScene() override;
		virtual void UpdateScene(float msec) override;

		inline void AddRenderObject(RenderObject &ro){
			//objectsToRender.push_back(&ro);
			root->AddChild(ro);
		}

		void RotateObject(char dir);
		void ScaleObject(char dir);
		void MoveObject(float units, char axis);

	protected:
		//Missing in PDF (Might move to RenderObject class)
		GLuint LoadTexture(string filename);

		float time;

		RenderObject *root;

		Camera *camera;

		vector<RenderObject*> objectsToRender;
};