#pragma once
#include "OGLRenderer.h"

using std::string;

enum MeshBuffer{
	VERTEX_BUFFER,
	COLOUR_BUFFER,
	TEXTURE_BUFFER,
	MAX_BUFFER
};

class Mesh{
	public:
		Mesh(void);
		~Mesh(void);

		virtual void Draw();
		static Mesh* GenerateTriangle();
		static Mesh* GenerateQuad();

		void SetTexture(GLuint tex) {
			texture = tex;
		}

		GLuint GetTexture() {
			return texture;
		}

		static Mesh* LoadMeshFile(const string &filename);

	protected:
		void BufferData();

		GLuint arrayObject,
			bufferObject[MAX_BUFFER],
			numVertices,
			type;

		Vector3 *vertices;
		Vector4 *colours;

		GLuint texture;
		Vector2 *textureCoords;

};