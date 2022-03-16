//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include <vector>

//-------------------------------------------------------------------------

class Mesh 
{
public:

	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D-RGB axes mesh

	static Mesh* create2DAxes(GLdouble l);

	static Mesh* generaPoligonoRegular(GLuint num, GLdouble r);

	static Mesh* createTriangleRGB(float r);

	static Mesh* generaRectangulo(GLdouble w, GLdouble h);

	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh);

	static Mesh* generaRectanguloRGB(GLdouble w, GLdouble h);

	static Mesh* generaCubo(GLdouble l);

	static Mesh* generaCuboRGB(GLdouble l);
	
	static Mesh* generaContCaja(GLdouble l);

	static Mesh* generaContCajaTexCor(GLdouble l);

	static Mesh* generaEstrella3D(GLdouble re, GLuint np,
		GLdouble h);


	Mesh() {};
	virtual ~Mesh() {};

	Mesh(const Mesh & m) = delete;  // no copy constructor
	Mesh & operator=(const Mesh & m) = delete;  // no copy assignment
			
	virtual void render() const;
	
	GLuint size() const { return mNumVertices; };   // number of elements
	std::vector<glm::dvec3> const& vertices() const { return vVertices; };
	std::vector<glm::dvec4> const& colors() const { return vColors; };
		
protected:
	
	GLuint mPrimitive = GL_TRIANGLES;   // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...
	GLuint mNumVertices = 0;  // number of elements ( = vVertices.size())
	std::vector<glm::dvec3> vVertices;  // vertex array
	std::vector<glm::dvec4> vColors;    // color array
	std::vector<glm::dvec2> vTexCoords; // texture array

	virtual void draw() const;
};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_