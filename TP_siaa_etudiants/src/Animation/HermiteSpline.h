#pragma once

#include <Math\Matrix4x4.h>
#include <Math\Vector.h>
#include <Math\Vectorf.h>
#include <Math\Interpolation.h>

class HermiteSpline
{
protected:
	Math::Matrix4x4<float> m_hermite;
	Math::Vector<Math::Vector3f , 4> m_spline;
	Math::Interpolation m_interpolator;

	double m_u;

public:
	HermiteSpline(Math::Vector3f P0, Math::Vector3f P1, Math::Vector3f D0, Math::Vector3f D1);
	HermiteSpline();
	~HermiteSpline();

	Math::Vector3f getPosition(double dt);
	
	Math::Vector3f getSpeed();

	Math::Vector<Math::Vector3f, 4> getSpline();
	void setSpline(Math::Vector<Math::Vector3f, 4> spline);

private:
	void completeHermite(void);

	Math::Vector3f computePosition(double t);
};

