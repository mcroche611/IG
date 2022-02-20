#define _USE_MATH_DEFINES

#include "Mesh.h"
#include "CheckML.h"
#include <fstream>
#include <cmath>
using namespace std;
using namespace glm;



//-------------------------------------------------------------------------

void Mesh::draw() const 
{
  glDrawArrays(mPrimitive, 0, size());   // primitive graphic, first index and number of elements to be rendered
}
//-------------------------------------------------------------------------

void Mesh::render() const 
{
  if (vVertices.size() > 0) {  // transfer data
    // transfer the coordinates of the vertices
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vVertices.data());  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (vColors.size() > 0) { // transfer colors
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, vColors.data());  // components number (rgba=4), type of each component, stride, pointer  
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* mesh = new Mesh();

  mesh->mPrimitive = GL_LINES;

  mesh->mNumVertices = 6;
  mesh->vVertices.reserve(mesh->mNumVertices);

  // X axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(l, 0.0, 0.0);
  // Y axis vertices
  mesh->vVertices.emplace_back(0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, l, 0.0);
  // Z axis vertices
  mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
  mesh->vVertices.emplace_back(0.0, 0.0, l);

  mesh->vColors.reserve(mesh->mNumVertices);
  // X axis color: red  (Alpha = 1 : fully opaque)
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
  mesh->vColors.emplace_back(0.0, 0.0, 1.0, 1.0);
 
  return mesh;
}
//-------------------------------------------------------------------------

static Mesh* generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    // X axis vertice
    mesh->vVertices.emplace_back(w, 0.0, 0.0);
    // Y axis vertice
    mesh->vVertices.emplace_back(0.0, w, 0.0);
    // Z axis vertice
    mesh->vVertices.emplace_back(0.0, 0.0, h);
}

Mesh* Mesh::generaPoligonoRegular(GLuint num, GLdouble r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINE_LOOP;

    mesh->mNumVertices = num;
    mesh->vVertices.reserve(mesh->mNumVertices);

    float aumento = 0.0;
    for (int i = 0; i < num; i++) {
        mesh->vVertices.emplace_back(r * cos(radians(90.0 + aumento)), r * sin(radians(90.0 + aumento)), 0.0);
        aumento += (360.0 / num);
    }

    //mesh->vColors.reserve(mesh->mNumVertices);
    //for (int j = 0; j < num; j++) 
    //{
    //    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    //}

    return mesh;
}

//Mesh* Mesh::createTriangle(float r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_TRIANGLES;
//
//    mesh->mNumVertices = 3;
//    mesh->vVertices.reserve(3);
//
//    // X axis vertice
//    mesh->vVertices.emplace_back(r, 0.0, 0.0);
//    // Y axis vertice
//    mesh->vVertices.emplace_back(0.0, r, 0.0);
//    // Z axis vertice
//    mesh->vVertices.emplace_back(0.0, 0.0, r);
//
//    mesh->vColors.reserve(3);
//    // X axis color: cyan  (Alpha = 1 : fully opaque)
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//    // Y axis color: cyan
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//    // Z axis color: cyan
//    mesh->vColors.emplace_back(0, 255, 255, 1.0);
//
//    return mesh;
//}
//
//Mesh* Mesh::createCircle(float r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_LINE_LOOP;
//
//    mesh->vVertices.reserve(360);
//
//    for (float i = 0.0; i < 360.0; i++) 
//    {
//        mesh->vVertices.emplace_back(r * cos(radians(i)), r * sin(radians(i)), 0.0);
//    }
//
//    mesh->vColors.reserve(360);
//    for (int i = 0; i < 360; i++)
//    {
//        mesh->vColors.emplace_back(255, 0, 255, 1.0); //magenta
//    }
//
//    return mesh;
//}

Mesh* Mesh::createTriangleRGB(float r)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLES;

    mesh->mNumVertices = 3;
    mesh->vVertices.reserve(mesh->mNumVertices);

    float aumento = 0.0;
    for (int i = 0; i < 3; i++) {
        mesh->vVertices.emplace_back(r * cos(radians(90.0 + aumento)), r * sin(radians(90.0 + aumento)), 0.0);
        aumento += (360.0 / 3);
    }

    //// X axis vertice
    //mesh->vVertices.emplace_back(r/2, -r/2, 0);
    //// Y axis vertice
    //mesh->vVertices.emplace_back(-r/2, -r/2, 0.0);
    //// Z axis vertice
    //mesh->vVertices.emplace_back(0, r/2, 0);

    mesh->vColors.reserve(mesh->mNumVertices);
    // X axis color: cyan  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(255, 0, 0, 1.0);
    // Y axis color: cyan
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Z axis color: cyan
    mesh->vColors.emplace_back(0, 0, 255, 1.0);

    return mesh;
}

//
//Mesh* Mesh::generaTriangleRegular(GLuint num, GLdouble r)
//{
//    Mesh* mesh = new Mesh();
//
//    mesh->mPrimitive = GL_LINE_LOOP;
//
//    mesh->mNumVertices = num;
//    mesh->vVertices.reserve(mesh->mNumVertices);
//
//    for (float i = 0; i < 360; i += 360 / num)
//    {
//        //mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
//        //glVertex2f(r * cos(radians(i)), r * sin(radians(i)));
//
//        mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
//        mesh->vVertices.emplace_back(r * cos(radians(i)), r * sin(radians(i)), 0.0);
//    }
//
//    return mesh;
//
//    //glBegin(GL_LINE_LOOP);
//    //for (float i = 0; i < 360; i += 360/num)
//    //{
//    //    glVertex2f(r * cos(radians(i)), r * sin(radians(i)));
//    //}
//    //glVertex2f(r, 0);
//    //glEnd();
//}