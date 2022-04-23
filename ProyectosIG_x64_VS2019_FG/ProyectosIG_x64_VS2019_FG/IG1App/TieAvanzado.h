#pragma once
#include "CompoundEntity.h"
using namespace glm;

class TieAvanzado : public CompoundEntity
{
public:
	TieAvanzado();

protected:
	dvec4 mColor = { 0.0 / 255.0, 65.0 / 255.0, 106.0 / 255.0, 1.0 };
};

