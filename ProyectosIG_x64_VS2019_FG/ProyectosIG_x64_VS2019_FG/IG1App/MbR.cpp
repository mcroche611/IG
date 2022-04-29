#include "MbR.h"

MbR::MbR(int m, int n, dvec3* perfil)
{
	this->m = m;
	this->n = n;
	this->perfil = perfil;
}

MbR* MbR::generaIndexMbR(int mm, int nn, glm::dvec3* perfil)
{
	MbR* mesh = new MbR(mm, nn, perfil);
	// Definir la primitiva como GL_TRIANGLES
	mesh->mPrimitive = GL_TRIANGLES;
	// Definir el n�mero de v�rtices como nn*mm
	mesh->mNumVertices = nn * mm;
	// Usar un vector auxiliar de v�rtices
	dvec3* vertices = new dvec3[mesh->mNumVertices];

	for (int i = 0; i < nn; i++)
	{
		// Generar la muestra i-�sima de v�rtices
		GLdouble theta = i * 360 / nn;
		GLdouble c = cos(radians(theta));
		GLdouble s = sin(radians(theta));
		// R_y(theta) es la matriz de rotaci�n alrededor del eje Y
		for (int j = 0; j < mm; j++) 
		{
			int indice = i * mm + j;
			GLdouble x = c * perfil[j].x + s * perfil[j].z;
			GLdouble z = -s * perfil[j].x + c * perfil[j].z;
			vertices[indice] = dvec3(x, perfil[j].y, z);
		}
	}

	for (int i = 0; i < mesh->mNumVertices; i++)
	{
		mesh->vVertices.push_back(vertices[i]);
	}

	int indiceMayor = 0;
	// El contador i recorre las muestras alrededor del eje Y
	for (int i = 0; i < nn; i++)
	{
		// El contador j recorre los v�rtices del perfil,
		// de abajo arriba. Las caras cuadrangulares resultan
		// al unir la muestra i-�sima con la (i+1)%nn-�sima
		for (int j = 0; j < mm - 1; j++)
		{
			// El contador indice sirve para llevar cuenta
			// de los �ndices generados hasta ahora. Se recorre
			// la cara desde la esquina inferior izquierda
			int indice = i * mm + j;

			// Los cuatro �ndices son entonces:
			//(indice, (indice + mm) % (nn * mm), (indice + mm + 1) % (nn * mm), indice + 1)
			mesh->vIndices[indiceMayor] = indice;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = (indice + mm + 1) % (nn * mm);
			indiceMayor++;

			mesh->vIndices[indiceMayor] = (indice + mm) % (nn * mm);
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice + 1;
			indiceMayor++;
			mesh->vIndices[indiceMayor] = indice;
		}
	}
		
	return mesh;
}


