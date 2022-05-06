#include "CuboIndexado.h"
#include "Mesh.h"
#include "IndexMesh.h"
#include <gtc/type_ptr.hpp>
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
        glEnable(GL_COLOR_MATERIAL);
        glColor3f(mColor.r, mColor.g, mColor.b);
        myMesh->render();
        glColor3f(1.0, 1.0, 1.0);
    }

}

void CuboIndexado::update()
{
}
