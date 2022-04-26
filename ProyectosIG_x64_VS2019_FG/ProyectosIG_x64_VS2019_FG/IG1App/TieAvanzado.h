#pragma once
#include "CompoundEntity.h"
using namespace glm;

class TieAvanzado : public CompoundEntity
{
public:
	TieAvanzado();

protected:
	dvec4 miColor = { 0.0, 65.0, 106.0, 1.0 };
};

