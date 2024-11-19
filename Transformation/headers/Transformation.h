#pragma once
#include "Triangulation.h"
#include "Matrix4x4.h"
	using namespace Geometry;
namespace Transformation
{
	class Transformation
	{
	public:
		bool operator()(double a, double b) const;
		Triangulation scaling(Triangulation& triangulation, double scale_x = 2.0, double scale_y = 2.0, double scale_z = 1.0);
		Triangulation translation(Triangulation& triangulation, double translate_x = 10.0, double translate_y = 10.0, double translate_z = 1.0);
		Triangulation rotation_x(Triangulation& triangulation, double rotate_x = 0);
		Triangulation rotation_y(Triangulation& triangulation, double rotate_x = 0);
		Triangulation rotation_z(Triangulation& triangulation, double rotate_x = 0);
	};
}