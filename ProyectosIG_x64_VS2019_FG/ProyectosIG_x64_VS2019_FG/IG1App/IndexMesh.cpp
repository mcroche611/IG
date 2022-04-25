#include "IndexMesh.h"


void IndexMesh::draw() const {
	
	glDrawElements(mPrimitive, nNumIndices,
		GL_UNSIGNED_INT, vIndices);
}
void IndexMesh::buildNormalVectors()
{
	
	vNormals.assign(mNumVertices, dvec3(0.0, 0.0, 0.0));

	for (int i = 0; i < nNumIndices; i += 3) {

		/*Extrae los vértices de índices i, i + 1, i + 2. Recuerda que el vértice
			correspondiente al índice k es vVertices.at(vIndices[k])*/

		dvec3 v0 = vVertices[vIndices[i]];
		dvec3 v1 = vVertices[vIndices[i + 1]];
		dvec3 v2 = vVertices[vIndices[i + 2]];

		dvec3 n = normalize(cross((v1 - v0), (v2 - v0)));

		vNormals[vIndices[i]] += n;
		vNormals[vIndices[i+1]] += n;
		vNormals[vIndices[i+2]] += n;

	}

	for (auto i : vNormals) {
		i = normalize(i);
	}
}


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
	indexMesh->buildNormalVectors();
	return indexMesh;
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