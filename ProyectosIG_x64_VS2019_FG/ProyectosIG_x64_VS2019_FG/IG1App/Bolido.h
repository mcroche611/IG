#pragma once
#include "CompoundEntity.h"
#include "Light.h"
using namespace glm;

class Bolido : public CompoundEntity
{
public:
	Bolido();
	~Bolido() {
		delete spotLight;
		spotLight = nullptr;
	};
protected:
	//dvec4 miColor = { 0.0, 65.0, 106.0, 1.0 };
};

