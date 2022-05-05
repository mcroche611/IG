#pragma once
#include "Mesh.h"

using namespace std;
using namespace glm;

class IndexMesh : public Mesh
{

protected:
	vector<GLuint> vIndices; // tabla de índices
	GLuint nNumIndices = 15000;
public:
	IndexMesh() { mPrimitive = GL_TRIANGLES; }
	~IndexMesh() { /*delete[] vIndices;*/ }
	virtual void draw() const;
	void buildNormalVectors();

	static IndexMesh* generaCuboConTapasIndexado(GLdouble l);

};

