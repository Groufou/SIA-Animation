#include "..\CyclicCoordinateDescent.h"


CyclicCoordinateDescent::CyclicCoordinateDescent(Animation::KinematicChain * kinematicChain, Animation::KinematicChain::Node * extremNode) :
	m_kinematicChain(kinematicChain),
	m_extremNode(extremNode)
{}

CyclicCoordinateDescent::~CyclicCoordinateDescent()
{}

bool CyclicCoordinateDescent::solve(Math::Vector3f objectif, float maxAngle)
{
	Math::Vector3f extremPosition;
	Math::Vector3f constraint;
	Math::Vector3f lastPosition = Math::makeVector(0.0f, 0.0f, 0.0f);

	float delta = std::numeric_limits<float>::max();
	
	do {
		extremPosition[0] = m_extremNode->getGlobalTransformation()(0, 3);
		extremPosition[1] = m_extremNode->getGlobalTransformation()(1, 3);
		extremPosition[2] = m_extremNode->getGlobalTransformation()(2, 3); 
		
		if ((lastPosition - extremPosition).norm() < 0.001f)
			return false;

		lastPosition = extremPosition;

		constraint = objectif - extremPosition;
		
		ccd(constraint, maxAngle);

	} while (constraint.norm() > 0.1f);

	return true;
}

void CyclicCoordinateDescent::convergeToward(Math::Vector3f objectif, float maxAngle)
{
	Math::Vector3f extremPosition;
	extremPosition[0] = m_extremNode->getGlobalTransformation()(0, 3);
	extremPosition[1] = m_extremNode->getGlobalTransformation()(1, 3);
	extremPosition[2] = m_extremNode->getGlobalTransformation()(2, 3);

	Math::Vector3f constraint = objectif - extremPosition;
	
	ccd(constraint, maxAngle);
}

void CyclicCoordinateDescent::ccd(Math::Vector3f constraint, float maxAngle)
{
	std::vector<Animation::KinematicChain::DegreeOfFreedom> allDof;
	m_extremNode->collectDegreesOfFreedom(allDof);

	float epsilon = 0.0001;

	for (int i = 0; i < allDof.size(); i++)
	{
		Math::Vector3f jacobien = m_kinematicChain->derivate(m_extremNode, Math::makeVector(0.0f, 0.0f, 0.0f), allDof[i], epsilon);

		float angle = 0.0f;

		if (jacobien.norm2() != 0)
			angle = (jacobien.inv() * constraint) / jacobien.norm2();

		if (angle > maxAngle) angle = maxAngle;

		allDof[i] = allDof[i] + angle;
	}
}

