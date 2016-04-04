#include "..\Insecte.h"


SceneGraph::Insecte::Insecte(void)
{
	// TODO SCENEGRAPH : Tout mettre sous le translate du body

	// Insect Body
	HelperGl::Material sphereMatBody;
	HelperGl::Color sphereColorBody(0.0,0.6,0.4);
	sphereMatBody.setDiffuse(sphereColorBody);
	
	m_sphereBody = new SceneGraph::Sphere(sphereMatBody);
	
	m_scaleBody = new SceneGraph::Scale(Math::makeVector(1.0f, 0.3f, 0.3f));
	m_scaleBody->addSon(m_sphereBody);

	m_root.addSon(m_scaleBody);	

	// Insect Wings
	HelperGl::Material sphereMatWing;
	HelperGl::Color sphereColorDiffuseWing(0.4,0.2,0.4);
	HelperGl::Color sphereColorSpecularWing(1.0,1.0,1.0);
	sphereMatWing.setDiffuse(sphereColorDiffuseWing);
	sphereMatWing.setSpecular(sphereColorSpecularWing);
	
	m_sphereWingR = new SceneGraph::Sphere(sphereMatWing);
	m_sphereWingL = new SceneGraph::Sphere(sphereMatWing);
	
	m_scaleWingR = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));
	m_scaleWingL = new SceneGraph::Scale(Math::makeVector(0.3f, 0.3f, 0.05f));
	m_scaleWingR->addSon(m_sphereWingR);
	m_scaleWingL->addSon(m_sphereWingL);

	m_translateWingR = new SceneGraph::Translate(Math::makeVector(0.0f, 0.6f, 0.0f));
	m_translateWingL = new SceneGraph::Translate(Math::makeVector(0.0f, -0.6f, 0.0f));
	m_translateWingR->addSon(m_scaleWingR);
	m_translateWingL->addSon(m_scaleWingL);

	m_root.addSon(m_translateWingR);
	m_root.addSon(m_translateWingL);

	// Insect Eyes
	HelperGl::Material sphereMatEye;
	HelperGl::Color sphereColorDiffuseEye(0.4,0.4,0.2);
	HelperGl::Color sphereColorSpecularEye(1.0,1.0,1.0);
	sphereMatEye.setDiffuse(sphereColorDiffuseEye);
	sphereMatEye.setSpecular(sphereColorSpecularEye);
	
	m_sphereEyeR = new SceneGraph::Sphere(sphereMatEye);
	m_sphereEyeL = new SceneGraph::Sphere(sphereMatEye);
	
	m_scaleEyeR = new SceneGraph::Scale(Math::makeVector(0.05f, 0.05f, 0.05f));
	m_scaleEyeL = new SceneGraph::Scale(Math::makeVector(0.05f, 0.05f, 0.05f));
	m_scaleEyeR->addSon(m_sphereEyeR);
	m_scaleEyeL->addSon(m_sphereEyeL);

	m_translateEyeR = new SceneGraph::Translate(Math::makeVector(0.7f, 0.2f, 0.2f));
	m_translateEyeL = new SceneGraph::Translate(Math::makeVector(0.7f, -0.2f, 0.2f));
	m_translateEyeR->addSon(m_scaleEyeR);
	m_translateEyeL->addSon(m_scaleEyeL);
	
	m_root.addSon(m_translateEyeR);
	m_root.addSon(m_translateEyeL);
}


SceneGraph::Insecte::~Insecte(void)
{
	delete m_sphereBody;
	delete m_scaleBody;

	delete m_sphereWingR;
	delete m_sphereWingL;
	delete m_scaleWingR;
	delete m_scaleWingL;
	delete m_translateWingR;
	delete m_translateWingL;

	delete m_sphereEyeR;
	delete m_sphereEyeL;
	delete m_scaleEyeR;
	delete m_scaleEyeL;
	delete m_translateEyeR;
	delete m_translateEyeL;
}


SceneGraph::Group * SceneGraph::Insecte::getSceneGraph()
{
	return &m_root;
}


void SceneGraph::Insecte::draw()
{
	m_root.draw();
}