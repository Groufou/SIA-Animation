#ifndef _Application_TP2_siaa_H
#define _Application_TP2_siaa_H

#include <HelperGl/LightServer.h>
#include <HelperGl/Camera.h>
#include <HelperGl/Material.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Cylinder.h>
#include <Animation/KinematicChain.h>

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
			if(m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f,(float)cameraSpeed*(float)getDt(),0.0f)) ; }
		}

		void polyArticulatedChain(SceneGraph::Group * root, int segments)
		{
			if (segments == 0)
				return;

			//Animation::KinematicChain::DegreeOfFreedom kine();
			
			HelperGl::Material matArticulation;
			matArticulation.setDiffuse(HelperGl::Color(0.8, 0.0, 0.0));

			HelperGl::Material matBone;
			matBone.setDiffuse(HelperGl::Color(0.0, 0.0, 0.7));

			SceneGraph::Sphere * articulation = new SceneGraph::Sphere(matArticulation,0.2);
			SceneGraph::Cylinder * bone = new SceneGraph::Cylinder(matBone, 0.1, 0.1, 0.5);

			SceneGraph::Rotate * articulationRotationX = new SceneGraph::Rotate(0.0f, Math::makeVector(1.0f, 0.0f, 0.0f));
			SceneGraph::Rotate * articulationRotationZ = new SceneGraph::Rotate(0.0f, Math::makeVector(0.0f, 0.0f, 1.0f));

			SceneGraph::Translate * boneTranslation = new SceneGraph::Translate(Math::makeVector(0.20f,0.0f,0.0f));
			SceneGraph::Rotate * boneRotation = new SceneGraph::Rotate(Math::pi/2, Math::makeVector(0.0f, 1.0f, 0.0f));

			//Translation du futur root
			SceneGraph::Translate * rootTranslation = new SceneGraph::Translate(Math::makeVector(0.70f, 0.0f, 0.0f));

			root->addSon(articulationRotationX);
				articulationRotationX->addSon(articulationRotationZ);
				articulationRotationZ->addSon(articulation);
				articulationRotationZ->addSon(boneTranslation);
					boneTranslation->addSon(boneRotation);
						boneRotation->addSon(bone);
					boneTranslation->addSon(rootTranslation);
					
			polyArticulatedChain(rootTranslation, segments - 1);
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

			m_camera.translateLocal(Math::makeVector(0.0, 0.0, 10.0));

			polyArticulatedChain(&m_root, 10);
		}

		virtual void render(double dt)
		{
			handleKeys() ;
			GL::loadMatrix(m_camera.getInverseTransform()) ;
			
			m_root.draw() ;
		}
	};
}

#endif