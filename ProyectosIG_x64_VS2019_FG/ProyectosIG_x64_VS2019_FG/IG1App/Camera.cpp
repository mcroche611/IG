#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>

using namespace glm;

//-------------------------------------------------------------------------

Camera::Camera(Viewport* vp): mViewPort(vp), mViewMat(1.0), mProjMat(1.0),  
							  xRight(vp->width() / 2.0), xLeft(-xRight),
							  yTop(vp->height() / 2.0), yBot(-yTop)
{
    setPM();
}
//-------------------------------------------------------------------------

void Camera::setAxes()
{
	mRight = row(mViewMat, 0);
	mUpward = row(mViewMat, 1);
	mFront = -row(mViewMat, 2);
}

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(mViewMat)); // transfers view matrix to the GPU 
}
//-------------------------------------------------------------------------

void Camera::setVM() 
{
	mViewMat = lookAt(mEye, mLook, mUp);  // glm::lookAt defines the view matrix 
	setAxes();

}
//-------------------------------------------------------------------------

void Camera::set2D() 
{
	int z = 500;
	mEye = dvec3(0, 0, z);
	mLook = dvec3(0, 0, 0);
	mUp = dvec3(0, 1, 0);

	mAng = -90;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	int x = 500;
	mEye = dvec3(x, x, x);  
	mLook = dvec3(0, 10, 0);   
	mUp = dvec3(0, 1, 0);

	mRadio = 1000;

	if (mEye.x >= 0)
	{
		mAng = 0;
	}
	else
	{
		mAng = 180;
	}

	mAng = -45;

	setVM();
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(1.0, 0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::yaw(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 1.0, 0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::roll(GLdouble a) 
{
	mViewMat = rotate(mViewMat, glm::radians(a), glm::dvec3(0, 0, 1.0));
	// glm::rotate returns mViewMat * rotationMatrix
}
//-------------------------------------------------------------------------

void Camera::setSize(GLdouble xw, GLdouble yh) 
{
	xRight = xw / 2.0;
	xLeft = -xRight;
	yTop = yh / 2.0;
	yBot = -yTop;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setScale(GLdouble s) 
{
	mScaleFact -= s;
	if (mScaleFact < 0) mScaleFact = 0.01;
	setPM();
}

void Camera::changePrj()
{
	bOrto = !bOrto;
	setPM();
}
//-------------------------------------------------------------------------

void Camera::setPM() 
{
	if (bOrto) 
	{ //  if orthogonal projection
		mNearVal = 1;
		mProjMat = ortho(xLeft*mScaleFact, xRight*mScaleFact, yBot*mScaleFact, yTop*mScaleFact, mNearVal, mFarVal);
		// glm::ortho defines the orthogonal projection matrix

	}
	else 
	{
		mNearVal = yTop;
		mProjMat = frustum(xLeft * mScaleFact, xRight * mScaleFact, yBot * mScaleFact, yTop * mScaleFact, mNearVal, mFarVal);
	}
}

void Camera::setCenital()
{
	mEye = dvec3(0, mRadio, 0);
	mAng = -90;
	mUp = dvec3(0, 0, -1);
	setVM();
}

void Camera::orbit(double incAng, double incY)
{
	mAng += glm::degrees(incAng);
	mEye.x = mLook.x + cos(radians(mAng)) * mRadio;
	mEye.z = mLook.z - sin(radians(mAng)) * mRadio;
	mEye.y = mLook.y + incY;
	setVM();
}

void Camera::moveLR(GLdouble cs)
{
	mEye += mRight * cs; /*sin(radians(cs));*/
	mLook += mRight * cs;
	setVM();
}

void Camera::moveFB(GLdouble cs)
{
	mEye += mFront * cs;
	mLook += mFront * cs;
	setVM();
}

void Camera::moveUD(GLdouble cs)
{
	mEye += mUpward * cs; /*sin(radians(cs));*/
	mLook += mUpward * cs;
	setVM();
}

void Camera::pitchReal(GLdouble cs)
{
	mViewMat = rotate(dmat4(1.0), glm::radians(cs), glm::dvec3(1.0, 0, 0)) * mViewMat;
}

void Camera::yawReal(GLdouble cs)
{
	mViewMat = rotate(dmat4(1.0), glm::radians(cs), glm::dvec3(0, 1.0, 0)) * mViewMat;
}

void Camera::rollReal(GLdouble cs)
{
	mViewMat = rotate(dmat4(1.0), glm::radians(cs), glm::dvec3(0, 0, 1.0)) * mViewMat;
}

//-------------------------------------------------------------------------

void Camera::uploadPM() const 
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(mProjMat)); // transfers projection matrix to the GPU
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


