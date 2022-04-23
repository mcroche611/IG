#include "QuadricEntity.h"

QuadricEntity::QuadricEntity() 
{
	q = gluNewQuadric();
}

void QuadricEntity::setColor(dvec4 color)
{
	this->color = color;
}

Sphere::Sphere(GLdouble rr) 
{ 
	r = rr; 
}

void QuadricEntity::renderColor() const
{
	// Aquí se puede fijar el color de la esfera así:
	glEnable(GL_COLOR_MATERIAL);
	//glColor3b((GLbyte)color.x, (GLbyte)color.y, (GLbyte)color.z);
	glColor3f(color.x, color.y, color.z);
	// Aquí se puede fijar el modo de dibujar la esfera:
	gluQuadricDrawStyle(q, GL_FILL);
}

void Sphere::render(glm::dmat4 const& modelViewMat) const
{
	dmat4 aMat = modelViewMat * mModelMat;
	upload(aMat);
	renderColor();
	gluSphere(q, r, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
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
	renderColor();
	//glutSolidCone(r, h, 100, 100); 
	gluCylinder(q, baseRadius, topRadius, h, 50, 50);
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
	renderColor();
	gluDisk(q, innerRadius, outerRadius, 50, 50);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
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
	renderColor();
	gluPartialDisk(q, innerRadius, outerRadius, 50, 50, startAngle, sweepAngle);
	// Aquí se debe recuperar el color:
	glColor3f(1.0, 1.0, 1.0);
}
