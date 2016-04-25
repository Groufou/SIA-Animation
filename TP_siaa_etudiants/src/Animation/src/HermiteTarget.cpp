#include "..\HermiteTarget.h"

HermiteTarget::HermiteTarget(HermiteSpline spline, int nb_Spline)
{
	m_hermites = new std::vector<HermiteSpline>(nb_Spline);
	(*m_hermites)[0] = spline;
	m_nbSpline = 1;
	m_u = 0.0;
}


HermiteTarget::~HermiteTarget()
{}


void HermiteTarget::addSpline(Math::Vector3f position, Math::Vector3f tangent)
{
	if (m_nbSpline < m_hermites->size())
	{
		Math::Vector3f initialPosition = (*m_hermites)[m_nbSpline - 1].getSpline()[1];
		Math::Vector3f revertTangent = -(*m_hermites)[m_nbSpline - 1].getSpline()[3];

		(*m_hermites)[m_nbSpline] = HermiteSpline(initialPosition, revertTangent, position, tangent);
		m_nbSpline++;
	}
}

void HermiteTarget::removeSpline(int indice)
{
	m_hermites->pop_back();
	m_nbSpline--;
}

Math::Vector3f HermiteTarget::getPosition(double dt)
{
	if (m_u > m_nbSpline) m_u = 0;

	Math::Vector3f position = (*m_hermites)[(int)m_u].getPosition(dt);
	
	m_u += dt;

	return position;
}

Math::Vector3f HermiteTarget::getSpeed()
{
	return (*m_hermites)[(int)m_u].getSpeed();
}