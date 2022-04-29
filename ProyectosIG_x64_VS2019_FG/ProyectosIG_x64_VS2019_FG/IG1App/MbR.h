#pragma once
#include "IndexMesh.h"

class MbR : public IndexMesh
{
protected:
	int m; //number of points
	int n; //number of rotations
	dvec3* perfil; //perfil en XY

public:
	MbR(int m, int n, dvec3* perfil);

	static MbR* generaIndexMbR(int mm, int nn, glm::dvec3* perfil);
};

