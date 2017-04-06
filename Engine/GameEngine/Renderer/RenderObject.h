#pragma once

#include "common.h"
#include "../NCLGL/nclgl/Matrix4.h"
#include "Mesh.h"
#include "Shader.h"
#include "../NCLGL/nclgl/OGLRenderer.h"

#pragma comment(lib, "nclgl.lib")

class RenderObject{
	public:
		RenderObject();
		RenderObject(Mesh *m, Shader *s, GLuint tex = 0);
		~RenderObject();

		inline Mesh* getMesh() const{
			return mesh;
		}
		inline void setMesh(Mesh *m){
			mesh = m;
		}

		inline Shader* getShader() const{
			return shader;
		}
		inline void setShader(Shader *s){
			shader = s;
		}

		inline GLuint getTexture() const{
			return texture;
		}
		inline void setTexture(GLuint tex){
			texture = tex;
		}

		inline Matrix4 getWorldTransform() const{
			return worldTransform;
		}

		inline void setWorldTransform(Matrix4 mat){
			worldTransform = mat;
		}

		inline Matrix4 getModelMatrix() const{
			return modelMatrix;
		}
		inline void setModelMatrix(Matrix4 mat){
			modelMatrix = mat;
		}
		
		inline const vector<RenderObject*>& getChildren() const{
			return children;
		}


		virtual void Update(float msec);
		virtual void Draw() const;

		inline void AddChild(RenderObject &child){
			children.push_back(&child);
			child.parent = this;
		}

	private:
		Mesh *mesh;
		Shader *shader;
		GLuint texture;

		Matrix4 modelMatrix,
			worldTransform;

		RenderObject *parent;
		vector<RenderObject*> children;
};