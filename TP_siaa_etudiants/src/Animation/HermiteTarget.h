#pragma once

#include <vector>
#include <Animation\HermiteSpline.h>

class HermiteTarget
{
protected:
	std::vector<HermiteSpline> *m_hermites;

	int m_nbSpline;
	double m_u;

public: 
	HermiteTarget(HermiteSpline spline, int nb_Spline);
	~HermiteTarget();

	void addSpline(Math::Vector3f position, Math::Vector3f tangent);
	void removeSpline(int indice);

	Math::Vector3f getPosition(double dt);

	Math::Vector3f getSpeed();
};

