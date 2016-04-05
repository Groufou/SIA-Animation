#include "..\Insecte.h"


SceneGraph::Insecte::Insecte(float speed) :
	m_speed(speed)
{
	// Insecte Root
	m_rootTranslate = new Translate();
	m_rootRotate = new Rotate(1.5f, Math::makeVector(0.0f, 0.0f, 1.0f));


	// Insect Body
	HelperGl::Material matBody;
	matBody.setDiffuse(HelperGl::Color(0.0, 0.6, 0.4));
	
	m_body = new Sphere(matBody);
	m_scaleBody = new Scale(Math::makeVector(1.0f, 0.3f, 0.3f));


	// Insect Wings
	HelperGl::Material matWing;
	matWing.setDiffuse(HelperGl::Color(0.4, 0.2, 0.4));
	matWing.setSpecular(HelperGl::Color(1.0, 1.0, 1.0));
	
	m_wing = new SceneGraph::Sphere(matWing);
	
	m_scaleWing = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));

	m_translateWingR = new SceneGraph::Translate(Math::makeVector(0.0f, 0.6f, 0.0f));
	m_translateWingL = new SceneGraph::Translate(Math::makeVector(0.0f, -0.6f, 0.0f));
	

	// Insect Eyes
	HelperGl::Material matEye;
	matEye.setDiffuse(HelperGl::Color(0.4, 0.4, 0.2));
	matEye.setSpecular(HelperGl::Color(1.0, 1.0, 1.0));
	
	m_eye = new SceneGraph::Sphere(matEye);
	
	m_scaleEye = new SceneGraph::Scale(Math::makeVector(0.05f, 0.05f, 0.05f));

	m_translateEyeR = new SceneGraph::Translate(Math::makeVector(0.7f, 0.2f, 0.2f));
	m_translateEyeL = new SceneGraph::Translate(Math::makeVector(0.7f, -0.2f, 0.2f));
	

	// Generate Insecte's scene graph
	this->createSkeleton();
}


SceneGraph::Insecte::~Insecte(void)
{
	delete m_body;
	delete m_scaleBody;

	delete m_wing;
	delete m_scaleWing;
	delete m_translateWingR;
	delete m_translateWingL;

	delete m_eye;
	delete m_scaleEye;
	delete m_translateEyeR;
	delete m_translateEyeL;
}

void SceneGraph::Insecte::createSkeleton(void)
{
	// Insect Root
	this->addSon(m_rootTranslate);
	m_rootTranslate->addSon(m_rootRotate);

	// Insect Body
	m_scaleBody->addSon(m_body);
	m_rootRotate->addSon(m_scaleBody);

	// Insect Wings
	m_scaleWing->addSon(m_wing);
	m_translateWingR->addSon(m_scaleWing);
	m_translateWingL->addSon(m_scaleWing);
	m_rootRotate->addSon(m_translateWingR);
	m_rootRotate->addSon(m_translateWingL);

	// Insect Eyes
	m_scaleEye->addSon(m_eye);
	m_translateEyeR->addSon(m_scaleEye);
	m_translateEyeL->addSon(m_scaleEye);
	m_rootRotate->addSon(m_translateEyeR);
	m_rootRotate->addSon(m_translateEyeL);
}

void SceneGraph::Insecte::translateLocal(Math::Vector3f translation)
{
	m_rootTranslate->setTranslation(m_rootTranslate->getTranslation() + translation);
}

void SceneGraph::Insecte::rotateLocal(float angle, Math::Vector3f axis)
{
	m_rootRotate->setAxis(axis);
	m_rootRotate->setAngle(m_rootRotate->getAngle() + angle);
}

float SceneGraph::Insecte::getSpeed(void)
{
	return m_speed;
}