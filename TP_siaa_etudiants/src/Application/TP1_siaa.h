#ifndef _Application_TP1_siaa_H
#define _Application_TP1_siaa_H

#include <HelperGl/LightServer.h>
#include <HelperGl/Camera.h>
#include <HelperGl/Material.h>
#include <SceneGraph/Sphere.h>
#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <GL/compatibility.h>
#include <SceneGraph/Insecte.h>
#include <Animation/HermiteSpline.h>
#include <Animation/HermiteTarget.h>
#include <math.h>

namespace Application
{
	class TP1_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera ;

		SceneGraph::Insecte *m_musquito ;
		
		SceneGraph::Group m_root ;

		HermiteTarget *m_target ;

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

	public:
		TP1_siaa()
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
			m_musquito = new SceneGraph::Insecte(10.0f);

			m_root.addSon(m_musquito);

			m_target = new HermiteTarget(HermiteSpline(Math::makeVector(0.0, 0.0, 0.0), Math::makeVector(0.0, 0.0, 1.0), Math::makeVector(3.0, 3.0, 3.0), Math::makeVector(-1.0, 0.0, 0.0)), 3);
			m_target->addSpline(Math::makeVector(0.0, -2.0, -5.0), Math::makeVector(1.0, 0.0, 1.0));
			m_target->addSpline(Math::makeVector(0.0, 0.0, 0.0), Math::makeVector(0.0, 0.0, -1.0));
		}

		virtual void render(double dt)
		{
			handleKeys() ;
			GL::loadMatrix(m_camera.getInverseTransform()) ;

			m_musquito->animateLocal(dt);
			m_musquito->translateLocal(m_target->getPosition(dt));
			
			double angleY = acos((m_target->getSpeed()*Math::makeVector(0.0, 1.0, 0.0)) / m_target->getSpeed().norm());
			double angleZ = acos((m_target->getSpeed()*Math::makeVector(0.0, 0.0, 1.0)) / m_target->getSpeed().norm());

			m_musquito->rotateLocalY(-angleY);
			m_musquito->rotateLocalZ(angleZ);

			m_root.draw() ;
		}
	};
}

#endif