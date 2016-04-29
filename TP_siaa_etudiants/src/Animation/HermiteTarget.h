#pragma once

#include <list>
#include <Animation\HermiteSpline.h>

class HermiteTarget
{
protected:
	std::list<HermiteSpline> *m_hermites;

	int m_nbSpline;
	double m_u;

public: 
	HermiteTarget(HermiteSpline spline);
	~HermiteTarget();

	void addSpline(Math::Vector3f position, Math::Vector3f tangent);
	void removeSpline();

	Math::Vector3f getPosition(double dt);

	Math::Vector3f getSpeed();
};

