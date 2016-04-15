#pragma once

#include <Math\Matrix4x4.h>
#include <Math\Vector.h>
#include <Math\Vectorf.h>
#include <Math\Interpolation.h>

class HermiteSpline
{
protected:
	Math::Matrix4x4<float> hermite;
	Math::Vector<Math::Vector3f , 4> spline;
	Math::Vector3f position;
	Math::Interpolation interpolator;

public:
	HermiteSpline(Math::Vector3f P0, Math::Vector3f P1, Math::Vector3f D0, Math::Vector3f D1);
	~HermiteSpline();

	Math::Vector3f getPosition(double dt);

private:
	void completeHermite(void);
};

