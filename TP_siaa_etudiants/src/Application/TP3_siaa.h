#ifndef _Application_TP3_siaa_H
#define _Application_TP3_siaa_H

#include <HelperGl/LightServer.h>
#include <HelperGl/Camera.h>
#include <HelperGl/Material.h>
#include <HelperGl/Buffer.h>
#include <SceneGraph/Sphere.h>
#include <Application/BaseWithKeyboard.h>
#include <Application/KeyboardStatus.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/MeshVBO_v2.h>
#include <SceneGraph/Translate.h>
#include <GL/compatibility.h>
#include <math.h>

#include <Animation/SpringMassSystem.h>
#include <SceneGraph/Patch.h>

namespace Application
{
	class TP3_siaa : public BaseWithKeyboard
	{
	protected:
		HelperGl::Camera m_camera;
		SceneGraph::Group m_root;

		Animation::SpringMassSystem m_springMassSystem;
		SceneGraph::Patch *m_patch;

		SceneGraph::Translate *Application::TP3_siaa::m_sphereTranslation;


		virtual void handleKeys()
		{
			// The camera translation speed
			float cameraSpeed = 5.0f;
			// The camera rotation speed (currently not used)
			float rotationSpeed = float(Math::pi / 2.0);

			// Quit
			if (m_keyboard.isPressed('q')) { quit(); }
			
			// Go front
			if (m_keyboard.isPressed('+')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, -cameraSpeed*(float)getDt())); }
			// Go back
			if (m_keyboard.isPressed('-')) { m_camera.translateLocal(Math::makeVector(0.0f, 0.0f, (float)cameraSpeed*(float)getDt())); }
			// Go left
			if (m_keyboard.isPressed('1')) { m_camera.translateLocal(Math::makeVector(-cameraSpeed*(float)getDt(), 0.0f, 0.0f)); }
			// Go right
			if (m_keyboard.isPressed('3')) { m_camera.translateLocal(Math::makeVector((float)cameraSpeed*(float)getDt(), 0.0f, 0.0f)); }
			// Go down
			if (m_keyboard.isPressed('2')) { m_camera.translateLocal(Math::makeVector(0.0f, -cameraSpeed*(float)getDt(), 0.0f)); }
			// Go up
			if (m_keyboard.isPressed('5')) { m_camera.translateLocal(Math::makeVector(0.0f, (float)cameraSpeed*(float)getDt(), 0.0f)); }
			
			// Move Sphere Up
			if (m_keyboard.isPressed('o')) { m_sphereTranslation->setTranslation(Math::makeVector(m_sphereTranslation->getTranslation()[0], m_sphereTranslation->getTranslation()[1]+0.01f, m_sphereTranslation->getTranslation()[2])); }
			// Move Sphere Down
			if (m_keyboard.isPressed('l')) { m_sphereTranslation->setTranslation(Math::makeVector(m_sphereTranslation->getTranslation()[0], m_sphereTranslation->getTranslation()[1]-0.01f, m_sphereTranslation->getTranslation()[2])); }
			// Move Sphere Left
			if (m_keyboard.isPressed('k')) { m_sphereTranslation->setTranslation(Math::makeVector(m_sphereTranslation->getTranslation()[0]-0.01f, m_sphereTranslation->getTranslation()[1], m_sphereTranslation->getTranslation()[2])); }
			// Move Sphere Right
			if (m_keyboard.isPressed('m')) { m_sphereTranslation->setTranslation(Math::makeVector(m_sphereTranslation->getTranslation()[0]+0.01f, m_sphereTranslation->getTranslation()[1], m_sphereTranslation->getTranslation()[2])); }

			// Free constraints
			if (m_keyboard.isPressed('f')) { 
				if (m_keyboard.isPressed('0'))
					m_springMassSystem.unconstrainPosition(0); 
				if (m_keyboard.isPressed('1'))
					m_springMassSystem.unconstrainPosition(49);
				if (m_keyboard.isPressed('2'))
					m_springMassSystem.unconstrainPosition(2400);
				if (m_keyboard.isPressed('3'))
					m_springMassSystem.unconstrainPosition(2449);
			}
		}


		static std::pair<Math::Vector3f, Math::Vector3f> updateMassPosition(const Animation::SpringMassSystem::Mass & previous, const Animation::SpringMassSystem::Mass & current, float dt)
		{
			Math::Vector3f speed;
			speed = previous.m_forces*(dt/ previous.m_mass) + previous.m_speed;

			Math::Vector3f position;
			position = previous.m_position + ((previous.m_speed + speed)/2)*dt;

			return std::pair<Math::Vector3f, Math::Vector3f>(position, speed);
		}

		static Math::Vector3f updateMassForce(const Animation::SpringMassSystem::Mass & mass)
		{
			return Math::makeVector(0.0f, 0.0f, -0.981f) * mass.m_mass;
		}

		static Math::Vector3f updateLinkForce(const Animation::SpringMassSystem::Mass & mass1, const Animation::SpringMassSystem::Mass & mass2, const Animation::SpringMassSystem::Link & link)
		{
			float k = 1.0f;
			float mu = 0.05f;

			return ((mass2.m_position - mass1.m_position) * k * (1.0f - (link.m_initialLength / (mass2.m_position - mass1.m_position).norm()))) - mass1.m_speed*mu;
		}

		static std::pair<Math::Vector3f, Math::Vector3f> floorConstraint(const Animation::SpringMassSystem::Mass & previous, const Animation::SpringMassSystem::Mass & current)
		{
			// Si la masse atteind la table
			if (current.m_position[2] < -1.5f)
			{
				Math::Vector3f position = Math::makeVector(current.m_position[0], current.m_position[1], -1.5f);
				Math::Vector3f speed = Math::makeVector(0.0f, 0.0f, 0.0f);
				return std::pair<Math::Vector3f, Math::Vector3f>(position, speed);
			}
			else
				return std::pair<Math::Vector3f, Math::Vector3f>(current.m_position, current.m_speed);
		}

		static std::pair<Math::Vector3f, Math::Vector3f> sphereConstraint(const Animation::SpringMassSystem::Mass & previous, const Animation::SpringMassSystem::Mass & current)
		{
			// Vecteur distance entre la masse et la centre de la sphère
			Math::Vector3f distance = (current.m_position + Math::makeVector(-1.5f, -1.5f, 0.0f)) - Math::makeVector(0.0f, -0.3f, -1.0f); // m_sphereTranslation->getTranslation();
			
			// Si la masse atteind le bord de la sphère
			if (distance.norm() <= 1.0f)
			{
				Math::Vector3f position = current.m_position;
				Math::Vector3f speed = current.m_speed;

				if(current.m_speed*distance < Math::piDiv2)
					speed = -current.m_speed;

				return std::pair<Math::Vector3f, Math::Vector3f>(position, speed);
			}
			else
				return std::pair<Math::Vector3f, Math::Vector3f>(current.m_position, current.m_speed);
		}


	public:
		TP3_siaa()
		{}

		virtual void initializeRendering()
		{
			// Light
			HelperGl::Color lightColor(1.0, 1.0, 1.0);
			HelperGl::Color lightAmbiant(0.0, 0.0, 0.0, 0.0);
			Math::Vector3f lightPosition = Math::makeVector(0.0f, 0.0f, 10000.0f);
			HelperGl::LightServer::Light * light = HelperGl::LightServer::getSingleton()->createLight(lightPosition, lightColor, lightColor, lightColor);
			light->enable();


			// Camera
			m_camera.translateLocal(Math::makeVector(0.0, -5.0, 5.0));
			m_camera.rotateLocal(Math::makeVector(1.0f, 0.0f, 0.0f), Math::piDiv4);


			// Spring Mass System
			m_springMassSystem.createPatch(3.0f, 49, 3.0f, 49, 1, 10.0f);
			m_springMassSystem.setIntegrator(&TP3_siaa::updateMassPosition);
			m_springMassSystem.addForceFunction(&TP3_siaa::updateMassForce);
			m_springMassSystem.addLinkForceFunction(&TP3_siaa::updateLinkForce);
			m_springMassSystem.addPositionConstraint(&TP3_siaa::floorConstraint);
			m_springMassSystem.addPositionConstraint(&TP3_siaa::sphereConstraint);

			m_springMassSystem.constrainPosition(2449);
			m_springMassSystem.constrainPosition(2400);
			m_springMassSystem.constrainPosition(49);
			m_springMassSystem.constrainPosition(0);


			// Tissu
			HelperGl::Material matPatch;
			matPatch.setDiffuse(HelperGl::Color(1.0f, 0.0f, 0.0f));
			matPatch.setSpecular(HelperGl::Color(0.4f, 0.3f, 0.3f));
			m_patch = new SceneGraph::Patch(50, 50, matPatch);
			
			SceneGraph::Translate *patchTranslation = new SceneGraph::Translate(Math::makeVector(-1.5f, -1.5f, 0.0f));
			
			patchTranslation->addSon(m_patch);
			m_root.addSon(patchTranslation);


			// Table
			HelperGl::Material matTable;
			matTable.setDiffuse(HelperGl::Color(0.8f, 0.8f, 0.8f));
			SceneGraph::Sphere *table = new SceneGraph::Sphere(matTable, 5.0f);
			
			SceneGraph::Scale *tableScale = new SceneGraph::Scale(Math::makeVector(1.0f, 1.0f, 0.01f));
			SceneGraph::Translate *tableTranslation = new SceneGraph::Translate(Math::makeVector(0.0f, 0.0f, -1.6f));

			tableScale->addSon(table);
			tableTranslation->addSon(tableScale);
			m_root.addSon(tableTranslation);


			// Sphere
			HelperGl::Material matSphere;
			matSphere.setDiffuse(HelperGl::Color(0.0f, 0.2f, 0.8f));
			SceneGraph::Sphere *sphere = new SceneGraph::Sphere(matSphere, 1.0f);

			m_sphereTranslation = new SceneGraph::Translate(Math::makeVector(0.0f, -0.3f, -1.0f));

			m_sphereTranslation->addSon(sphere);
			m_root.addSon(m_sphereTranslation);
		}

		virtual void render(double dt)
		{
			handleKeys();
			GL::loadMatrix(m_camera.getInverseTransform());
			
			m_springMassSystem.update(dt);

			for (int i = 0; i < m_patch->getVertices().size(); i++)
				m_patch->getVertices()[i] = m_springMassSystem.getMasses()[i].m_position;

			m_root.draw();
		}
	};
}

#endif
