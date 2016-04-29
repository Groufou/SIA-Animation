#include "..\HermiteTarget.h"

HermiteTarget::HermiteTarget(HermiteSpline spline) :
	m_nbSpline(1),
	m_u(0.0)
{
	m_hermites = new std::list<HermiteSpline>();
	m_hermites->push_back(spline);
}


HermiteTarget::~HermiteTarget()
{}


void HermiteTarget::addSpline(Math::Vector3f position, Math::Vector3f tangent)
{
	Math::Vector3f initialPosition = m_hermites->back().getSpline()[1];
	Math::Vector3f revertTangent = -m_hermites->back().getSpline()[3];

	m_hermites->push_back(HermiteSpline(initialPosition, revertTangent, position, tangent));
	m_nbSpline++;
}

void HermiteTarget::removeSpline()
{
	m_hermites->pop_front();
	m_nbSpline--;
}

Math::Vector3f HermiteTarget::getPosition(double dt)
{
	if (m_u > m_nbSpline) m_u = 0;

	if ((int)m_u != (int)(m_u + dt)) {
		m_hermites->push_back(m_hermites->front());
		m_hermites->pop_front();
	}
	
	Math::Vector3f position = m_hermites->front().getPosition(dt);
	
	m_u += dt;

	return position;
}

Math::Vector3f HermiteTarget::getSpeed()
{
	return m_hermites->front().getSpeed();
}