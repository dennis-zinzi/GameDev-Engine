#pragma once

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mesh.h"
#include <vector>

class SceneNode{
	public:
		SceneNode(Mesh *m = NULL, Vector4 colour = Vector4(1, 1, 1, 1));
		~SceneNode();

		void SetTransform(const Matrix4 &matrix){
			transform = matrix;
		}
		const Matrix4 GetTransform() const{
			return transform;
		}

		Matrix4 GetWorldTransform() const{
			return worldTransform;
		}

		void SetColour(Vector4 c){
			colour = c;
		}
		Vector4 GetColour() const{
			return colour;
		}

		void SetModelScale(Vector3 ms){
			modelScale = ms;
		}
		Vector3 GetModelScale() const{
			return modelScale;
		}

		void SetMesh(Mesh *m){
			mesh = m;
		}
		Mesh* GetMesh() const{
			return mesh;
		}

		void AddChild(SceneNode *s);

		virtual void Update(float msec);
		virtual void Draw(const OGLRenderer &r);

		/*std::*/vector<SceneNode*>::const_iterator GetChildIteratorStart(){
			return children.begin();
		}

		/*std::*/vector<SceneNode*>::const_iterator GetChildIteratorEnd(){
			return children.end();
		}


	protected:
		SceneNode *parent;
		Mesh *mesh;

		Matrix4 worldTransform,
			transform;

		Vector3 modelScale;
		Vector4 colour;

		std::vector<SceneNode *> children;

};