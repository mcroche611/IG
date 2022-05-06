//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Texture.h"
#include "CheckML.h"
#include "Poligono.h"
#include "TrianguloRGB.h"
#include "RectanguloRGB.h"
#include "Cubo.h"
#include "CuboRGB.h"
#include "Suelo.h"
#include "ContornoCaja.h"
#include "Cristalera.h"
#include "Foto.h"
#include "Estrella3D.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "QuadricEntity.h"
#include "CompoundEntity.h"
#include "TieAvanzado.h"
#include "CuboIndexado.h"
#include <vector>
#include "Light.h"
//-------------------------------------------------------------------------

class Scene	: public CompoundEntity
{ 
public:
	Scene() { dirLight = nullptr; spotLight = nullptr; posLight = nullptr; };
	~Scene() { free(); resetGL(); };

	Scene(const Scene& s) = delete;  // no copy constructor
	Scene& operator=(const Scene& s) = delete;  // no copy assignment
		
	void init();

    void render(Camera const& cam) const;

	void setState(int id);

	int getState();

	void sceneDirLight(Camera const& cam) const;
	virtual void update();

	void orbit(); 
	void rotation();
	void setLights();
	void uploadLights(Camera const& cam) const;
	void enableDirLight() { dirLight->enable(); };
	void disableDirLight() { dirLight->disable(); };
protected:
	void free();
	void setGL();
	void resetGL();


	CompoundEntity* nodoFicticio;
	TrianguloRGB* tr;
	TieAvanzado* tie;
	
	int mId = 7;

	//std::vector<Abs_Entity*> gObjects;  // Entities (graphic objects) of the scene
	//std::vector<Abs_Entity*> tObjects;  // entidades traslucidas
	std::vector<Texture*> gTextures; //to manage objects texture
	SpotLight* spotLight;
	DirLight* dirLight;
	PosLight* posLight;

};
//-------------------------------------------------------------------------

#endif //_H_Scene_H_

