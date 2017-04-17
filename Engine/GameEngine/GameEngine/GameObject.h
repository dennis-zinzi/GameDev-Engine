#include "common.h"

#pragma comment(lib, "PhysicsSystem.lib")
#pragma comment(lib, "Renderer.lib")

//Renderer includes
#include "../Renderer/Renderer.h"

//Physics include
#include "../PhysicsSystem/Physics.h"


class GameObject{
	public:
		GameObject(Renderer &renderer, Physics &physics, Mesh *mesh, Shader *shader,
			GLuint texture = 0, GameObject *parent = nullptr,
			Vector3 translation = Vector3(0.0f, 0.0f, 0.0f),
			float rotation = 0.0f, Vector3 rotationAxis = Vector3(0.0f, 0.0f, 0.0f),
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f));

		inline void AddChild(GameObject &child){
			children.push_back(&child);
			child.parent = this;

			renderObj->AddChild(*child.renderObj);
		}

		inline void UpdateModelMatrix(Matrix4 matrix){
			renderObj->setModelMatrix(renderObj->getModelMatrix() * matrix);
		}

		inline void SetModelMatrix(Matrix4 matrix){
			renderObj->setModelMatrix(matrix);
		}

	protected:
		GameObject *parent;
		vector<GameObject*> children;

		RenderObject *renderObj;
};