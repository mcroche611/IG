#include "Poligono.h"
#include "Mesh.h"

Poligono::Poligono(float num, float r)
{
    num_ = num;
    r_ = r;
    myMesh = new Mesh();
    myMesh = Mesh::generaPoligonoRegular(num, r);

    glm::dvec4 color = { 255, 255, 0, 1.0 };
    setColor(color);
}

void Poligono::render(dmat4 const& modelViewMat)const
{
	glColor3d(mColor.r, mColor.g, mColor.b);

    /*myMesh->render();*/

    if (myMesh != nullptr)
    {
        dmat4 aMat = modelViewMat * mModelMat;
        upload(aMat);
        glLineWidth(2);
        myMesh->render();
        glLineWidth(1);
    }

    glColor3d(255, 255, 255);

    //if (myMesh->vVertices.size() > 0) {  // transfer data
    //// transfer the coordinates of the vertices
    //    glEnableClientState(GL_VERTEX_ARRAY);
    //    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    //    if (vColors.size() > 0) { // transfer colors
    //        glEnableClientState(GL_COLOR_ARRAY);
    //        glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    //    }

    //    draw();

    //    glDisableClientState(GL_COLOR_ARRAY);
    //    glDisableClientState(GL_VERTEX_ARRAY);
    //}
}

void Poligono::update()
{
}
