#include "..\Insecte.h"


SceneGraph::Insecte::Insecte(float speed) :
	m_speed(speed),
	m_maxAngleWing(1.0f),
	m_minAngleWing(-1.0f),
	m_upDownWing(true)
{
	// Insecte Root
	m_rootTranslate = new Translate(Math::makeVector(0.0f, 0.0f, -3.0f));
	m_rootRotate = new Rotate(0.0f, Math::makeVector(0.0f, 0.0f, 0.0f));


	// Insect Body

	HelperGl::Material matBody;
	matBody.setDiffuse(HelperGl::Color(0.0, 0.6, 0.4));

	m_body = new Sphere(matBody);

	//m_body3ds = new HelperGl::Loader3ds("../../../INSECTE/Insecte.3DS", "../../../INSECTE/textures");
	//m_body3ds = new HelperGl::Loader3ds("~/Users/vincent/Documents/ESIR/SIA-Animation/SIA-Animation/INSECTE/Insecte.3DS",
	//	"~/Users/vincent/Documents/ESIR/SIA-Animation/SIA-Animation/INSECTE/textures/");
	//m_bodyMesh = new MeshVBO_v2(m_body3ds->getMeshes()[0]);

	m_scaleBody = new Scale(Math::makeVector(1.0f, 0.3f, 0.3f));


	// Insect Wings
	HelperGl::Material matWing;
	matWing.setDiffuse(HelperGl::Color(0.4, 0.2, 0.4));
	matWing.setSpecular(HelperGl::Color(1.0, 1.0, 1.0));
	
	m_wing = new SceneGraph::Sphere(matWing);
	
	m_scaleWing = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));

	m_translateAxeWingR = new SceneGraph::Translate(Math::makeVector(0.0f, 0.3f, 0.0f));
	m_translateAxeWingL = new SceneGraph::Translate(Math::makeVector(0.0f, -0.3f, 0.0f));
	
	m_rotateWingR = new Rotate(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f));
	m_rotateWingL = new Rotate(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f));
	
	m_translateWingR = new SceneGraph::Translate(Math::makeVector(0.0f, 0.3f, 0.0f));
	m_translateWingL = new SceneGraph::Translate(Math::makeVector(0.0f, -0.3f, 0.0f));


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
	delete m_body3ds;
	delete m_bodyMesh;
	delete m_scaleBody;

	delete m_wing;
	delete m_scaleWing;
	delete m_translateAxeWingR;
	delete m_translateAxeWingL;
	delete m_rotateWingR;
	delete m_rotateWingL;
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
	//m_scaleBody->addSon(m_bodyMesh);

	m_rootRotate->addSon(m_scaleBody);

	// Insect Wings
	m_scaleWing->addSon(m_wing);
	m_translateWingR->addSon(m_scaleWing);
	m_translateWingL->addSon(m_scaleWing);
	m_rotateWingR->addSon(m_translateWingR);
	m_rotateWingL->addSon(m_translateWingL);
	m_translateAxeWingR->addSon(m_rotateWingR);
	m_translateAxeWingL->addSon(m_rotateWingL);
	m_rootRotate->addSon(m_translateAxeWingR);
	m_rootRotate->addSon(m_translateAxeWingL);

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

void SceneGraph::Insecte::setSpeed(float speed)
{
	m_speed = speed;
}

void SceneGraph::Insecte::animateLocal(float dt)
{
	this->animateWings(dt);
}

void SceneGraph::Insecte::animateWings(float dt)
{
	// Decide if wings go up or down
	if (m_rotateWingL->getAngle() > m_maxAngleWing)
		m_upDownWing = false;

	if (m_rotateWingL->getAngle() < m_minAngleWing)
		m_upDownWing = true;

	// Generate smooth rotation angle
	double angle = 0;
	if (m_rotateWingL->getAngle() > 0)
		angle = m_speed*dt*(m_maxAngleWing + 0.3 - m_rotateWingL->getAngle());
	else
		angle = m_speed*dt*(m_rotateWingL->getAngle() + 0.3 - m_minAngleWing);

	// Set wings rotation
	if (m_upDownWing)
	{
		m_rotateWingL->setAngle(m_rotateWingL->getAngle() + angle);
		m_rotateWingR->setAngle(m_rotateWingR->getAngle() - angle);
	}
	else
	{
		m_rotateWingL->setAngle(m_rotateWingL->getAngle() - angle);
		m_rotateWingR->setAngle(m_rotateWingR->getAngle() + angle);
	}
}