#include "IndexMesh.h"

void IndexMesh::buildNormalVectors()
{
	dvec3 normals[8] = { dvec3(0, 0, 0),  dvec3(0, 0, 0), dvec3(0, 0, 0), dvec3(0, 0, 0), dvec3(0, 0, 0), dvec3(0, 0, 0), dvec3(0, 0, 0), dvec3(0, 0, 0) };    //vector de normales

}

void IndexMesh::draw() const {
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}

static const GLdouble cube_strip[] = { -0.5, 0.5, 0.5,
									 -0.5, -0.5, 0.5,
									 0.5, 0.5, 0.5,
									  0.5, -0.5, 0.5,

									  0.5, 0.5, -0.5,
									  0.5, -0.5, -0.5,
									 -0.5, 0.5, -0.5,
									 -0.5, -0.5, -0.5,
};
static const GLdouble cube_strip2[] = { 0.5, 0.5, -0.5,
									    0.5, -0.5, -0.5,
									    0.5, 0.5, 0.5,
									    0.5, -0.5, 0.5,

									    -0.5, 0.5, 0.5,
									    -0.5, -0.5, 0.5,
									     -0.5, 0.5, -0.5,
									      -0.5, -0.5, -0.5,
};

unsigned int stripIndices[] =
{ 0, 1, 2, 3, 4, 5, 6, 7, 0, 1 };
IndexMesh* IndexMesh::generaCuboConTapasIndexado(GLdouble l)
{
	IndexMesh* indexMesh = new IndexMesh();
	indexMesh->mPrimitive = GL_TRIANGLES;

	indexMesh->mNumVertices = 8;
	indexMesh->nNumIndices = 36;
	indexMesh->vColors.reserve(indexMesh->mNumVertices);
	indexMesh->vVertices.reserve(indexMesh->mNumVertices);

	GLdouble v = l / 2;
	indexMesh->vVertices.emplace_back(-v, v, v);
	indexMesh->vVertices.emplace_back(-v, -v, v);
	indexMesh->vVertices.emplace_back(v, v, v);
	indexMesh->vVertices.emplace_back(v, -v, v);

	indexMesh->vVertices.emplace_back(v, v, -v);
	indexMesh->vVertices.emplace_back(v, -v, -v);
	indexMesh->vVertices.emplace_back(-v, v, -v);
	indexMesh->vVertices.emplace_back(-v, -v, -v);

	for (int i = 0; i < indexMesh->mNumVertices; i++) {
		indexMesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
	}

	indexMesh->vIndices = new GLuint[indexMesh->nNumIndices]  { 0,1,2, 2,1,3,
																2,3,4, 4,3,5,
																4,5,6, 6,5,7,
																6,7,0, 0,7,1,
																4,6,2, 2,6,0,
																1,7,3, 3,7,5};

	//falta indexmesh->buildnormalvectors

	return indexMesh;
}