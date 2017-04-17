#pragma once

#include "../NCLGL/nclgl/OGLRenderer.h"
#include "../NCLGL/nclgl/Camera.h"
#include "RenderObject.h"

#include "../bullet3-2.86.1/src/btBulletDynamicsCommon.h"

#pragma comment(lib, "nclgl.lib")
#pragma comment(lib, "PhysicsSystem.lib")

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

		void DrawSphere(btRigidBody *sphere);
		void DrawPlane(btRigidBody *plane);

		void RotateObject(char dir);
		void ScaleObject(char dir);
		void MoveObject(float units, char axis);

		inline RenderObject* getRenderRoot() const{
			return root;
		}

	protected:
		//Missing in PDF (Might move to RenderObject class)
		GLuint LoadTexture(string filename);

		float time;

		RenderObject *root;

		Camera *camera;

		vector<RenderObject*> objectsToRender;
};