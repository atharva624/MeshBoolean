#pragma once
#include "Triangulation.h"
#include "Transformation.h"
#include "RealPoint.h"
#include "MeshUtility.h"
#include "Matrix4x4.h"
using namespace Geometry;


	class TransformationManager
	{
	public:
		TransformationManager();
		~TransformationManager();
		MeshUtility mesh;
		Transformation::Transformation t;
		std::vector<Triangulation> transformObject(std::vector<Triangulation>& triangulation);

	};
