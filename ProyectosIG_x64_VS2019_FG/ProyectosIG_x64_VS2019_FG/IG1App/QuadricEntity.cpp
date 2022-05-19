#include "QuadricEntity.h"
#include <gtc/type_ptr.hpp>

QuadricEntity::QuadricEntity() 
{
	q = gluNewQuadric();
}
/*
void QuadricEntity::setColor(dvec4 color)
{
	this->color = color;
}
*/
Sphere::Sphere(GLdouble rr) 
{ 
	r = rr; 
}

void QuadricEntity::renderColor() const
{
	// Aquí se puede fijar el color de la esfera así:
	//glEnable(GL_COLOR_MATERIAL);
	////glColor3b((GLbyte)color.x, (GLbyte)color.y, (GLbyte)color.z);
	//glColor3f(color.x, color.y, color.z);
	//// Aquí se puede fijar el modo de dibujar la esfera:
	//gluQuadricDrawStyle(q, GL_FILL);
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (this->material != nullptr)
	{
		material->upload();
	}
	else
	{
		// Aquí se puede fijar el color de la esfera así:
		glEnable(GL_COLOR_MATERIAL);
		glColor3f(mColor.r, mColor.g, mColor.b);
	}

	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GLU_FILL);
	gluSphere(q, r, 300, 300);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);
}


Cylinder::Cylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble h) 
{ 
	this->baseRadius = baseRadius; 
	this->topRadius = topRadius;
	this->h = h;
}

void Cylinder::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);
	glutSolidCylinder(baseRadius, h, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}

Disk::Disk(GLdouble innerRadius, GLdouble outerRadius)
{
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
}


void Disk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (this->material != nullptr)
		this->material->upload();
	else
		glColor4dv(value_ptr(mColor));

	gluQuadricDrawStyle(q, GL_FILL);
	gluDisk(q, innerRadius, outerRadius, 50, 50);
	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

PartialDisk::PartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLdouble startAngle, GLdouble sweepAngle)
{
	this->innerRadius = innerRadius;
	this->outerRadius = outerRadius;
	this->startAngle = startAngle;
	this->sweepAngle = sweepAngle;
}

void PartialDisk::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);

	if (this->material != nullptr)
		this->material->upload();
	else
		glColor4dv(value_ptr(mColor));
	gluQuadricDrawStyle(q, GL_FILL);
	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);
	// Aquí se debe recuperar el color:
	glColor4d(1.0, 1.0, 1.0, 1.0);
}

RevCone::RevCone(GLdouble baseRadius, GLdouble h)
{
	this->baseRadius = baseRadius;
	this->h = h;
}

void RevCone::render(glm::dmat4 const& modelViewMat) const
{
	//dmat4 aMat = modelViewMat * mModelMat;
	//upload(aMat);

	//if (this->material != nullptr)
	//	this->material->upload();
	//else
	//	glColor4dv(value_ptr(mColor));
	//gluQuadricDrawStyle(q, GL_FILL);
	//glutSolidCone(baseRadius, h, 50, 50);
	//// Aquí se debe recuperar el color:
	//glColor4d(1.0, 1.0, 1.0, 1.0);

}

MyCone::MyCone(GLdouble baseRadius, GLdouble h)
{
	this->baseRadius = baseRadius;
	this->h = h;
}

void MyCone::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	glEnable(GL_COLOR_MATERIAL);

	glColor3f(mColor.r, mColor.g, mColor.b);
	gluQuadricDrawStyle(q, GLU_FILL);
	glutSolidCone(baseRadius, h, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}
