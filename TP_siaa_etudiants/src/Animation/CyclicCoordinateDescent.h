#pragma once

#include <Animation\KinematicChain.h>

class CyclicCoordinateDescent
{
protected:
	Animation::KinematicChain * m_kinematicChain;
	Animation::KinematicChain::Node * m_extremNode;

public:
	CyclicCoordinateDescent(Animation::KinematicChain *kinematicChain, Animation::KinematicChain::Node *extremNode);
	~CyclicCoordinateDescent();

	void convergeToward(Math::Vector3f objectif, float maxAngle);
	bool solve(Math::Vector3f objectif, float maxAngl);

protected:
	void ccd(Math::Vector3f constraint, float maxAngle);
};

