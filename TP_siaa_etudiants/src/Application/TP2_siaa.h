#ifndef _Application_TP2_siaa_H
#define _Application_TP2_siaa_H

#include <HelperGl/LightServer.h>
#include <HelperGl/Camera.h>
#include <HelperGl/Material.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Cylinder.h>
#include <Animation/KinematicChain.h>
#include <Animation/CyclicCoordinateDescent.h>
#include <Math/Interval.h>
#include <Animation/HermiteSpline.h>
#include <Animation/HermiteTarget.h>

#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <GL/compatibility.h>

namespace Application
{
	class TP2_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera ;
		
		SceneGraph::Group m_root ;
		SceneGraph::Sphere *m_sphereObjectif;
		SceneGraph::Translate *m_translateObjectif ;

		Animation::KinematicChain m_rootChain;
		std::vector<std::pair<SceneGraph::Rotate*, Animation::KinematicChain::Node*> > m_mapDOF;

		CyclicCoordinateDescent *m_ccd;
		HermiteTarget *m_target;

		virtual void handleKeys() 
		{
			// The camera translation speed
			float cameraSpeed = 5.0f ;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi/2.0) ;

			// quit
			if(m_keyboard.isPressed('q')) { quit() ; }
			// Go front
			if(m_keyboard.isPressed('+')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,-cameraSpeed*(float)getDt())) ; } 
			// Go back
			if(m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f,0.0f,(float)cameraSpeed*(float)getDt())) ; } 
			// Go left
			if(m_keyboard.isPressed('1')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed*(float)getDt(),0.0f,0.0f)) ; }
			// Go right
			if(m_keyboard.isPressed('3')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(),0.0f,0.0f)) ; }
			// Go down
			if(m_keyboard.isPressed('2')) { m_camera.translateLocal(Math::makeVector(0.0f,-cameraSpeed*(float)getDt(),0.0f)) ; }
			// Go up
			if (m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f, (float)cameraSpeed*(float)getDt(), 0.0f)); }
			
			// Random Goal
			if (m_keyboard.isPressed('n')) { 
				Math::Vector3f position = Math::makeVector((float)(std::rand() % 20 - 10), (float)(std::rand() % 20 - 10), (float)(std::rand() % 20 - 10));
				m_translateObjectif->setTranslation(position);
			}
		}


		Animation::KinematicChain::Node * polyArticulatedChain(SceneGraph::Group * rootGraph, Animation::KinematicChain::Node * rootChain, int segments)
		{
			// End condition for recursive function
			if (segments == 0)
				return rootChain;


			// Init materials
			HelperGl::Material matArticulation;
			matArticulation.setDiffuse(HelperGl::Color(0.0f, 0.8f, 0.0f));

			HelperGl::Material matBone;
			matBone.setDiffuse(HelperGl::Color(0.0f, 0.0f, 0.7f));


			// Init poly-articulated chain in scene graph
			SceneGraph::Sphere * articulation = new SceneGraph::Sphere(matArticulation,0.2);

			SceneGraph::Cylinder * bone = new SceneGraph::Cylinder(matBone, 0.1, 0.1, 0.5);

			SceneGraph::Rotate * articulationRotationX = new SceneGraph::Rotate(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f));
			SceneGraph::Rotate * articulationRotationZ = new SceneGraph::Rotate(0.0f, Math::makeVector(0.0f, 0.0f, 1.0f));

			SceneGraph::Translate * boneTranslation = new SceneGraph::Translate(Math::makeVector(0.20f,0.0f,0.0f));
			SceneGraph::Rotate * boneRotation = new SceneGraph::Rotate(Math::pi/2, Math::makeVector(0.0f, 1.0f, 0.0f));

			SceneGraph::Translate * rootTranslation = new SceneGraph::Translate(Math::makeVector(0.70f, 0.0f, 0.0f));


			// Init poly-articulated chain in kinematic chain
			Animation::KinematicChain *kineChain = new Animation::KinematicChain();
			Animation::KinematicChain::DynamicNode *nodeArticulationX = kineChain->addDynamicRotation(rootChain, Math::makeVector(1.0f, 0.0f, 0.0f), Math::makeInterval((float)-Math::piDiv2, (float)Math::piDiv2), 0.0f);
			Animation::KinematicChain::DynamicNode *nodeArticulationZ = kineChain->addDynamicRotation(nodeArticulationX, Math::makeVector(0.0f, 0.0f, 1.0f), Math::makeInterval((float)-Math::piDiv2, (float)Math::piDiv2), 0.0f);
			Animation::KinematicChain::StaticNode *nodeBone = kineChain->addStaticTranslation(nodeArticulationZ, Math::makeVector(0.90f, 0.0f, 0.0f));

			m_mapDOF.push_back(std::pair<SceneGraph::Rotate*, Animation::KinematicChain::Node*>(articulationRotationX, nodeArticulationX));
			m_mapDOF.push_back(std::pair<SceneGraph::Rotate*, Animation::KinematicChain::Node*>(articulationRotationZ, nodeArticulationZ));


			// Init Scene Graph
			rootGraph->addSon(articulationRotationX);
				articulationRotationX->addSon(articulationRotationZ);
				articulationRotationZ->addSon(articulation);
				articulationRotationZ->addSon(boneTranslation);
					boneTranslation->addSon(boneRotation);
						boneRotation->addSon(bone);
					boneTranslation->addSon(rootTranslation);
					
			return polyArticulatedChain(rootTranslation, nodeBone, segments - 1);
		}

	public:
		TP2_siaa()
		{}

		virtual void initializeRendering()
		{
			// Light
			HelperGl::Color lightColor(1.0,1.0,1.0);
			HelperGl::Color lightAmbiant(0.0,0.0,0.0,0.0);
			Math::Vector4f lightPosition = Math::makeVector(0.0f,0.0f,10000.0f,1.0f) ;
			HelperGl::LightServer::Light * light = HelperGl::LightServer::getSingleton()->createLight(lightPosition.popBack(), lightColor, lightColor, lightColor) ;
			light->enable();

			m_camera.translateLocal(Math::makeVector(0.0, 0.0, 20.0));

			HelperGl::Material matObjectif;
			matObjectif.setDiffuse(HelperGl::Color(1.0f, 0.0f, 0.0f));
			m_sphereObjectif = new SceneGraph::Sphere(matObjectif, 0.2f);
			
			m_translateObjectif = new SceneGraph::Translate(Math::makeVector(7.0f, 3.0f, 0.0f));

			m_root.addSon(m_translateObjectif);
			m_translateObjectif->addSon(m_sphereObjectif);

			Animation::KinematicChain::Node *extremity = polyArticulatedChain(&m_root, m_rootChain.getRoot(), 12);
			Math::Vector3f extremePosition = Math::makeVector(extremity->getGlobalTransformation()(0, 3), extremity->getGlobalTransformation()(1, 3), extremity->getGlobalTransformation()(2, 3));
			
			m_target = new HermiteTarget(HermiteSpline(extremePosition, Math::makeVector(0.0f, 1.0f, 0.0f), Math::makeVector(0.0f, 10.0f, -3.0f), Math::makeVector(1.0f, 0.0f, 0.0f)));
			m_target->addSpline(Math::makeVector(-10.0f, 0.0f, 0.0f), Math::makeVector(0.0f, 1.0f, 0.0f));
			m_target->addSpline(Math::makeVector(0.0f, -10.0f, 3.0f), Math::makeVector(-1.0f, 0.0f, 0.0f));
			m_target->addSpline(extremePosition, Math::makeVector(0.0f, -1.0f, 0.0f));
			
			m_ccd = new CyclicCoordinateDescent(&m_rootChain, extremity);
		}

		virtual void render(double dt)
		{
			handleKeys() ;
			GL::loadMatrix(m_camera.getInverseTransform()) ;
			
			m_root.draw() ;

			m_ccd->solve(m_target->getPosition(0.0015), 0.0005f);
			// m_ccd->convergeToward(m_translateObjectif->getTranslation(), 0.001f);

			for (int i = 0; i < m_mapDOF.size(); i++)
				m_mapDOF[i].first->setAngle(m_mapDOF[i].second->getDOF()[0]);
		}
	};
}

#endif