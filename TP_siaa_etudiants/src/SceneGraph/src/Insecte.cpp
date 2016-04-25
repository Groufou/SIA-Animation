#include "..\Insecte.h"


SceneGraph::Insecte::Insecte(double speed) :
	m_speed(speed),
	m_maxAngleWing(1.0f),
	m_minAngleWing(-1.0f),
	m_upDownWing(true),
	m_rootRotateY(0.0f, Math::makeVector(0.0f, 1.0f, 0.0f)),
	m_rootRotateZ(0.0f, Math::makeVector(0.0f, 0.0f, 1.0f)),
	m_scaleBody(Math::makeVector(1.0f, 0.3f, 0.3f)),
	m_scaleWing(Math::makeVector(0.3f, 0.3f, 0.05f)),
	m_translateAxeWingR(Math::makeVector(0.0f, 0.3f, 0.0f)),
	m_translateAxeWingL(Math::makeVector(0.0f, -0.3f, 0.0f)),
	m_rotateWingR(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f)),
	m_rotateWingL(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f)),
	m_translateWingR(Math::makeVector(0.0f, 0.3f, 0.0f)),
	m_translateWingL(Math::makeVector(0.0f, -0.3f, 0.0f)),
	m_scaleEye(Math::makeVector(0.05f, 0.05f, 0.05f)),
	m_translateEyeR(Math::makeVector(0.7f, 0.2f, 0.2f)),
	m_translateEyeL(Math::makeVector(0.7f, -0.2f, 0.2f))
{
	// Insect Body
	HelperGl::Material matBody;
	matBody.setDiffuse(HelperGl::Color(0.0f, 0.6f, 0.4f));
	m_body = new Sphere(matBody);
	
	// Insect Wings
	HelperGl::Material matWing;
	matWing.setDiffuse(HelperGl::Color(0.4f, 0.2f, 0.4f));
	matWing.setSpecular(HelperGl::Color(1.0f, 1.0f, 1.0f));
	m_wing = new SceneGraph::Sphere(matWing);

	// Insect Eyes
	HelperGl::Material matEye;
	matEye.setDiffuse(HelperGl::Color(0.4f, 0.4f, 0.2f));
	matEye.setSpecular(HelperGl::Color(1.0f, 1.0f, 1.0f));
	m_eye = new SceneGraph::Sphere(matEye);

	// Generate Insecte's scene graph
	this->createSkeleton();
}


SceneGraph::Insecte::~Insecte(void)
{
	delete m_body;
	delete m_wing;
	delete m_eye;
}

void SceneGraph::Insecte::createSkeleton(void)
{
	// Insect Root
	this->addSon(&m_rootTranslate);
		m_rootTranslate.addSon(&m_rootRotateZ);
			m_rootRotateZ.addSon(&m_rootRotateY);
				m_rootRotateY.addSon(&m_scaleBody);
				m_rootRotateY.addSon(&m_translateAxeWingR);
				m_rootRotateY.addSon(&m_translateAxeWingL);
				m_rootRotateY.addSon(&m_translateEyeR);
				m_rootRotateY.addSon(&m_translateEyeL);

	// Insect Body
	m_scaleBody.addSon(m_body);

	// Insect Wings
	m_translateAxeWingR.addSon(&m_rotateWingR);
	m_translateAxeWingL.addSon(&m_rotateWingL);
		m_rotateWingR.addSon(&m_translateWingR);
		m_rotateWingL.addSon(&m_translateWingL);
			m_translateWingR.addSon(&m_scaleWing);
			m_translateWingL.addSon(&m_scaleWing);
				m_scaleWing.addSon(m_wing);

	// Insect Eyes
	m_translateEyeR.addSon(&m_scaleEye);
	m_translateEyeL.addSon(&m_scaleEye);
		m_scaleEye.addSon(m_eye);
}

void SceneGraph::Insecte::translateLocal(Math::Vector3f translation)
{
	m_rootTranslate.setTranslation(translation);
}

void SceneGraph::Insecte::rotateLocalY(double angle)
{
	m_rootRotateY.setAngle(angle);
}

void SceneGraph::Insecte::rotateLocalZ(double angle)
{
	m_rootRotateZ.setAngle(angle);
}

double SceneGraph::Insecte::getSpeed(void)
{
	return m_speed;
}

void SceneGraph::Insecte::setSpeed(double speed)
{
	m_speed = speed;
}

void SceneGraph::Insecte::animateLocal(double dt)
{
	this->animateWings(dt);
}

void SceneGraph::Insecte::animateWings(double dt)
{
	// Decide if wings go up or down
	if (m_rotateWingL.getAngle() > m_maxAngleWing)
		m_upDownWing = false;

	if (m_rotateWingL.getAngle() < m_minAngleWing)
		m_upDownWing = true;

	// Generate smooth rotation angle
	float angle = 0;
	if (m_rotateWingL.getAngle() > 0)
		angle = m_speed*dt*(m_maxAngleWing + 0.3 - m_rotateWingL.getAngle());
	else
		angle = m_speed*dt*(m_rotateWingL.getAngle() + 0.3 - m_minAngleWing);

	// Set wings rotation
	if (m_upDownWing)
	{
		m_rotateWingL.setAngle(m_rotateWingL.getAngle() + angle);
		m_rotateWingR.setAngle(m_rotateWingR.getAngle() - angle);
	}
	else
	{
		m_rotateWingL.setAngle(m_rotateWingL.getAngle() - angle);
		m_rotateWingR.setAngle(m_rotateWingR.getAngle() + angle);
	}
}