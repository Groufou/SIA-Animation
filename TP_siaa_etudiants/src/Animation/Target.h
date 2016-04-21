#pragma once

#include <vector>
#include <Animation\HermiteSpline.h>

class Target
{
protected:
	std::vector<HermiteSpline> *m_hermites;

	int m_nbSpline;
	double m_u;

public: 
	Target(HermiteSpline spline, int nb_Spline);
	~Target();

	void addSpline(Math::Vector3f position, Math::Vector3f tangent);
	void removeSpline(int indice);

	Math::Vector3f getPosition(double dt);

	Math::Vector3f getSpeed();
};

