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
    if (vTexCoords.size() > 0)
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_DOUBLE, 0, vTexCoords.data());
    }

	draw();

    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
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

Mesh* Mesh::create2DAxes(GLdouble l)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_LINES;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    // X axis vertices
    mesh->vVertices.emplace_back(0.0, 0.0, 0.0);
    mesh->vVertices.emplace_back(l, 0.0, 0.0);
    // Y axis vertices
    mesh->vVertices.emplace_back(0, 0.0, 0.0);
    mesh->vVertices.emplace_back(0.0, l, 0.0);

    mesh->vColors.reserve(mesh->mNumVertices);
    // X axis color: red  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    mesh->vColors.emplace_back(1.0, 0.0, 0.0, 1.0);
    // Y axis color: green
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);
    mesh->vColors.emplace_back(0.0, 1.0, 0.0, 1.0);

    return mesh;
}

//-------------------------------------------------------------------------

Mesh* Mesh::generaRectangulo(GLdouble w, GLdouble h)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = 4;
    mesh->vVertices.reserve(mesh->mNumVertices);

    GLdouble w2 = w / 2, h2 = h / 2;

    mesh->vVertices.emplace_back(w2, h2, 0.0);
    mesh->vVertices.emplace_back(-w2, h2, 0.0);
    mesh->vVertices.emplace_back(w2, -h2, 0.0);
    mesh->vVertices.emplace_back(-w2, -h2, 0.0);


	return mesh;
}

Mesh* Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh* mesh = generaRectangulo(w, h);

    GLuint numBaldosas = w / rw;

    mesh->vTexCoords.reserve(mesh->mNumVertices * numBaldosas);

    //Vertices de cada baldosa
    for (int i = 0; i < numBaldosas; i++)
    {
		mesh->vTexCoords.emplace_back(i * rw + rw, i * rh);
		mesh->vTexCoords.emplace_back(i * rw, i * rh);
		mesh->vTexCoords.emplace_back(i * rw + rw, i * rh + rh);
		mesh->vTexCoords.emplace_back(i * rw, i * rh + rh);
    }

    // Old method of matching vertices
    //mesh->vTexCoords.emplace_back(1, 0);
    //mesh->vTexCoords.emplace_back(0, 0);
    //mesh->vTexCoords.emplace_back(1, 1);
    //mesh->vTexCoords.emplace_back(0, 1);


    return mesh;
}

Mesh* Mesh::generaRectanguloRGB(GLdouble w, GLdouble h)
{
    Mesh* mesh = generaRectangulo(w, h);

    mesh->vColors.reserve(mesh->mNumVertices);
    // Red
    mesh->vColors.emplace_back(255, 0, 0, 1.0);
    // Green  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Green
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Blue
    mesh->vColors.emplace_back(0, 0, 255, 1.0);

    return mesh;
}

static const GLfloat cube_strip[] = { +0.5, +0.5, -0.5, // Back-top-right Red
                                    -0.5, +0.5, -0.5, // Back-top-left Red
                                    +0.5, -0.5, -0.5, // Back-bottom-right Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Green*
                                    -0.5, -0.5, +0.5, // Front-bottom-left Green
                                    -0.5, +0.5, -0.5, // Back-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Blue*
                                    +0.5, +0.5, +0.5, // Front-top-right Blue2
                                    -0.5, +0.5, -0.5, // Back-top-left Blue2
                                    +0.5, +0.5, -0.5, // Back-top-right Blue
                                    +0.5, +0.5, -0.5, // Back-top-right Green2
                                    +0.5, +0.5, +0.5, // Front-top-right Green*
                                    +0.5, -0.5, -0.5, // Back-bottom-right Green
                                    +0.5, -0.5, +0.5, // Front-bottom-right Green
                                    +0.5, -0.5, +0.5, // Front-bottom-right Red*
                                    +0.5, +0.5, +0.5, // Front-top-right Red2
                                    -0.5, -0.5, +0.5, // Front-bottom-left Red
                                    -0.5, +0.5, +0.5, // Front-top-left Red
                                    +0.5, -0.5, +0.5, // Front-bottom-right Red2
                                    +0.5, -0.5, +0.5, // Front-bottom-right Blue2
                                    -0.5, -0.5, +0.5, // Front-bottom-left Blue2
                                    +0.5, -0.5, -0.5, // Back-bottom-right Blue2
                                    -0.5, -0.5, -0.5 // Back-bottom-left Blue2  
};

static const GLfloat cube_colors[] = { 255, 0, 0, // Back-top-right Red
                                       255, 0, 0, // Back-top-left Red
                                    255, 0, 0, // // Back-bottom-right Red
                                    255, 0, 0, // // Back-bottom-left Red
                                    0, 255, 0, // // Back-bottom-left Green
                                    0, 255, 0, // // Front-bottom-left Green
                                    0, 255, 0, // // Back-top-left Green
                                    0, 255, 0, // // Front-top-left Green
                                    0, 0, 255, // // Front-top-left Blue*
                                    0, 0, 255, // // Front-top-right Blue2
                                    0, 0, 255, // // Back-top-left Blue2
                                    0, 0, 255, // // Back-top-right Blue
                                    0, 255, 0, // // Back-top-right Green2
                                    0, 255, 0, // // Front-top-right Green*
                                    0, 255, 0, // // Back-bottom-right Green
                                    0, 255, 0, // // Front-bottom-right Green
                                    255, 0, 0, // // Front-bottom-right Red*
                                    255, 0, 0, // // Front-top-right Red2
                                    255, 0, 0, // // Front-bottom-left Red
                                    255, 0, 0, // // Front-top-left Red
                                    255, 0, 0, // // Front-bottom-right Red2
                                    0, 0, 255, // // Front-bottom-right Blue2
                                    0, 0, 255, // // Front-bottom-left Blue2
                                    0, 0, 255, // // Back-bottom-right Blue2
                                    0, 0, 255 // // Back-bottom-left Blue2  
};

Mesh* Mesh::generaCubo(GLdouble l)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;

    mesh->mNumVertices = sizeof(cube_strip) / sizeof(GLfloat);
    mesh->vVertices.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i += 3)
    {
        mesh->vVertices.emplace_back(l* cube_strip[i], l * cube_strip[i + 1], l * cube_strip[i + 2]);
    }

    return mesh;
}

Mesh* Mesh::generaCuboRGB(GLdouble l)
{
    Mesh* mesh = generaCubo(l);

    mesh->vColors.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i += 3)
    {
        mesh->vColors.emplace_back(cube_colors[i], cube_colors[i + 1], cube_colors[i + 2], 1.0);
    }

    return mesh;
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

    return mesh;
}

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

    mesh->vColors.reserve(mesh->mNumVertices);
    // X axis color: red  (Alpha = 1 : fully opaque)
    mesh->vColors.emplace_back(255, 0, 0, 1.0);
    // Y axis color: green
    mesh->vColors.emplace_back(0, 255, 0, 1.0);
    // Z axis color: blue
    mesh->vColors.emplace_back(0, 0, 255, 1.0);

    return mesh;
}



static const GLfloat box_strip[] = { +0.5, +0.5, -0.5, // Back-top-right Red
                                    -0.5, +0.5, -0.5, // Back-top-left Red
                                    +0.5, -0.5, -0.5, // Back-bottom-right Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Red
                                    -0.5, -0.5, -0.5, // Back-bottom-left Green*
                                    -0.5, -0.5, +0.5, // Front-bottom-left Green
                                    -0.5, +0.5, -0.5, // Back-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Green
                                    -0.5, +0.5, +0.5, // Front-top-left Blue*
                                    +0.5, +0.5, +0.5, // Front-top-right Blue*
                                    -0.5, -0.5, +0.5, // Front-bottom-left Blue
                                    +0.5, -0.5, +0.5, // Front-bottom-right Blue
                                    +0.5, -0.5, +0.5, // Front-bottom-right Green
                                    +0.5, -0.5, -0.5, // Back-bottom-right Green
                                    +0.5, +0.5, +0.5, // Front-top-right Green*
                                    +0.5, +0.5, -0.5, // Back-top-right Green*


};

Mesh* Mesh::generaContCaja (GLdouble l)
{
    Mesh* mesh = new Mesh();

    mesh->mPrimitive = GL_TRIANGLE_STRIP;
    
    mesh->mNumVertices = sizeof(box_strip) / sizeof(GLfloat);
    mesh->vVertices.reserve(mesh->mNumVertices);

    for (int i = 0; i < mesh->mNumVertices; i += 3)
    {
        mesh->vVertices.emplace_back(l * box_strip[i], l * box_strip[i + 1], l * box_strip[i + 2]);
    }

    return mesh;
}

Mesh* Mesh::generaContCajaTexCor(GLdouble l)
{
    Mesh* mesh = generaContCaja(l);


    mesh->vTexCoords.reserve(mesh->mNumVertices);

    //Vertices de cada baldosa
    /*for (int i = 0; i < 5; i++)
    {
        mesh->vTexCoords.emplace_back((1+i)/4 , 1/3);
        mesh->vTexCoords.emplace_back((0+i)/4, 1 / 3);
        mesh->vTexCoords.emplace_back((0+i)/4, 2 / 3);
        mesh->vTexCoords.emplace_back((1+i)/4, 2 / 3);
    }*/

    // Old method of matching vertices
    
    for (int i = 0; i < 5; i++)
   {
        mesh->vTexCoords.emplace_back(1+i, 0);
        mesh->vTexCoords.emplace_back(0+i, 0);
        mesh->vTexCoords.emplace_back(1+i, 1);
        mesh->vTexCoords.emplace_back(0+i, 1);
   }

    return mesh;
}
