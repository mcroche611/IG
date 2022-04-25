#pragma once
#include "Mesh.h"

using namespace std;
using namespace glm;

class IndexMesh : public Mesh
{
	void buildNormalVectors();
protected:
	GLuint* vIndices = nullptr; // tabla de índices
	GLuint nNumIndices = 0;
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { delete[] vIndices; }
	virtual void draw() const;

	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);

};

