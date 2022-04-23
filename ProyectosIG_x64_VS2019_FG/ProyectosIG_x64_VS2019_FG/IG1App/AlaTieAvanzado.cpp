#include "AlaTieAvanzado.h"

AlaTieAvanzado::AlaTieAvanzado(GLdouble w, GLdouble h)
{
	alas = new Mesh();
	alas = Mesh::generaAla(w, h);
}

AlaTieAvanzado::~AlaTieAvanzado()
{
	delete alas;
}

void AlaTieAvanzado::render(glm::dmat4 const& modelViewMat) const
{
	//dmat4 aMat = modelViewMat * mModelMat;
	//upload(aMat);
	//alas->render();

    glColor3d(mColor.r, mColor.g, mColor.b);

    if (alas != nullptr)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        mTexture->setWrap(GL_REPEAT);
        mTexture->bind(GL_MODULATE);

        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        //culling a las traseras
        alas->render();

        //se renderiza lo de fuera


        glLineWidth(1);
        glDisable(GL_CULL_FACE);
        glPolygonMode(GL_FRONT, GL_FILL);
        glPolygonMode(GL_BACK, GL_FILL);
    }

    glColor3d(255, 255, 255);
}
