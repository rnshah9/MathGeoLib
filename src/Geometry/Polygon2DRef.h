#pragma once

#include <sstream>
#include "../Math/float2.h"
#include "../Math/MathConstants.h"
#include "../Math/myassert.h"

/// Polygon2DRef represents a Polygon2D, but by referencing an existing set of points, rather than allocating/owning its own set of points.
struct Polygon2DRef
{
public:
	const float2 *points;
	int numPoints;

	FORCE_INLINE vec2d AnyPointFast() const
	{
		assert(points);
		assert(numPoints > 0);
		return points[0];
	}

	vec2d ExtremePoint(const vec2d &direction, float &projectionDistance) const
	{
		vec2d mostExtreme = vec2d::nan;
		projectionDistance = -FLOAT_INF;
		for(int i = 0; i < numPoints; ++i)
		{
			float d = Dot(direction, points[i]);
			if (d > projectionDistance)
			{
				projectionDistance = d;
				mostExtreme = points[i];
			}
		}
		return mostExtreme;
	}

	std::string SerializeToString() const
	{
		std::stringstream ss;
		ss << "(";
		for(int i = 0; i < numPoints; ++i)
			ss << "(" << points[i].SerializeToString() + (i+1 != numPoints ? ")," : ")");
		ss << ")";
		return ss.str();
	}
};

