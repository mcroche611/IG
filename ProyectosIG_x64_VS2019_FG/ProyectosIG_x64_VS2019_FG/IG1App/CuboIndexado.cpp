#include "CuboIndexado.h"
#include "Mesh.h"
#include "IndexMesh.h"
CuboIndexado::CuboIndexado(GLdouble longitud)
{
    l_ = longitud;

    myMesh = new Mesh();
    myMesh = IndexMesh::generaCuboConTapasIndexado(l_);

}

void CuboIndexado::render(dmat4 const& modelViewMat)const
{

    if (myMesh != nullptr)
    {
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        myMesh->render();
    }

}

void CuboIndexado::update()
{
}
