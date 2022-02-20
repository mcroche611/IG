//#pragma once
#ifndef _H_Scene2D_H_
#define _H_Scene2D_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene2D	
{ 
public:
	Scene2D() {};
	~Scene2D() { free(); resetGL(); };

	Scene2D(const Scene2D& s) = delete;  // no copy constructor
	Scene2D& operator=(const Scene2D& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;
	
protected:
	void free();
	void setGL();
	void resetGL();

	std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the Scene2D
};
//-------------------------------------------------------------------------

#endif //_H_Scene2D_H_

