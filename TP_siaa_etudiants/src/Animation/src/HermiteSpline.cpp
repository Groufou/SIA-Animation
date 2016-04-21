#include "..\HermiteSpline.h"

HermiteSpline::HermiteSpline(Math::Vector3f P0, Math::Vector3f D0, Math::Vector3f P1, Math::Vector3f D1) :
	m_u(0.0)
{
	m_spline[0] = P0;
	m_spline[1] = P1;
	m_spline[2] = D0;
	m_spline[3] = D1;
	
	completeHermite();
}

HermiteSpline::HermiteSpline() :
	m_u(0.0),
	m_spline(0.0)
{
	completeHermite();
}

HermiteSpline::~HermiteSpline()
{
}

Math::Vector3f HermiteSpline::getPosition(double dt)
{
	if (m_u > 1.0) m_u = 0.0;
	
	Math::Vector3f position = computePosition(m_u);

	m_u += dt;

	return position;
}

Math::Vector3f HermiteSpline::getSpeed()
{
	float h = 0.0001;
	
	return (computePosition(m_u + h) - computePosition(m_u)) / h;
}

Math::Vector<Math::Vector3f, 4> HermiteSpline::getSpline()
{
	return m_spline;
}

Math::Vector3f HermiteSpline::computePosition(double t)
{
	Math::Vector4f b;
	
	b[0] = m_hermite(0, 0)*pow(t, 3) + m_hermite(1, 0)*pow(t, 2) + m_hermite(2, 0)*t + m_hermite(3, 0);
	b[1] = m_hermite(0, 1)*pow(t, 3) + m_hermite(1, 1)*pow(t, 2) + m_hermite(2, 1)*t + m_hermite(3, 1);
	b[2] = m_hermite(0, 2)*pow(t, 3) + m_hermite(1, 2)*pow(t, 2) + m_hermite(2, 2)*t + m_hermite(3, 2);
	b[3] = m_hermite(0, 3)*pow(t, 3) + m_hermite(1, 3)*pow(t, 2) + m_hermite(2, 3)*t + m_hermite(3, 3);

	return m_spline[0] * b[0] + m_spline[1] * b[1] + m_spline[2] * b[2] + m_spline[3] * b[3];
}

void HermiteSpline::completeHermite(void)
{
	Math::Vector4f vector0 = Math::makeVector(2, -2, 1, 1);
	Math::Vector4f vector1 = Math::makeVector(-3, 3, -2, -1);
	Math::Vector4f vector2 = Math::makeVector(0, 0, 1, 0);
	Math::Vector4f vector3 = Math::makeVector(1, 0, 0, 0);

	m_hermite = Math::Matrix4x4<float>(vector0, vector1, vector2, vector3);
}