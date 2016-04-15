#include "..\HermiteSpline.h"



HermiteSpline::HermiteSpline(Math::Vector3f P0, Math::Vector3f P1, Math::Vector3f D0, Math::Vector3f D1)
{
	spline[0] = P0;
	spline[1] = P1;
	spline[2] = D0;
	spline[3] = D1;

	position = P0;

	completeHermite();
}


HermiteSpline::~HermiteSpline()
{
}

Math::Vector3f HermiteSpline::getPosition(double dt)
{
	Math::Vector3f u = dt;

	Math::Vector4f b;
	b[0] = hermite(0, 0)*pow(u[0],3) + hermite(0, 1)*pow(u[1],2) + hermite(0, 2)*u[2] + hermite(0, 3);
	b[1] = hermite(1, 0)*pow(u[0],3) + hermite(1, 1)*pow(u[1],2) + hermite(1, 2)*u[2] + hermite(1, 3);
	b[2] = hermite(2, 0)*pow(u[0],3) + hermite(2, 1)*pow(u[1],2) + hermite(2, 2)*u[2] + hermite(2, 3);
	b[3] = hermite(3, 0)*pow(u[0],3) + hermite(3, 1)*pow(u[1],2) + hermite(3, 2)*u[2] + hermite(3, 3);

	position = spline[0]*b[0] + spline[1]*b[1] + spline[2]*b[2] + spline[3]*b[3];
	
	return position;
}

void HermiteSpline::completeHermite(void)
{
	Math::Vector4f vector0 = Math::makeVector(2, -2, 1, 1);
	Math::Vector4f vector1 = Math::makeVector(-3, 3, -2, -1);
	Math::Vector4f vector2 = Math::makeVector(0, 0, 1, 0);
	Math::Vector4f vector3 = Math::makeVector(1, 0, 0, 0);

	hermite = Math::Matrix4x4<float>(vector0, vector1, vector2, vector3);
}
