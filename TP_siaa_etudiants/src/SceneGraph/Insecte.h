#ifndef _SceneGraph_Insecte_H
#define _SceneGraph_Insecte_H

#include <GL/glew.h>
#include <SceneGraph/NodeInterface.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/Scale.h>
#include <SceneGraph/Translate.h>
#include <SceneGraph/Rotate.h>
#include <Math/Vectorf.h>
#include <HelperGl/Loader3ds.h>
#include <SceneGraph/Mesh.h>
#include <SceneGraph/MeshVBO_v2.h>

namespace SceneGraph
{
	class Insecte : public Group
	{
	private:
		Translate *m_rootTranslate;
		Rotate *m_rootRotate;

		Sphere *m_body;
		HelperGl::Loader3ds *m_body3ds;
		MeshVBO_v2 *m_bodyMesh;
		Scale *m_scaleBody;

		Sphere *m_wing;
		Scale *m_scaleWing;
		Translate *m_translateAxeWingR;
		Translate *m_translateAxeWingL;
		Rotate *m_rotateWingR;
		Rotate *m_rotateWingL;
		Translate *m_translateWingR;
		Translate *m_translateWingL;

		Sphere *m_eye;
		Scale *m_scaleEye;
		Translate *m_translateEyeR;
		Translate *m_translateEyeL;

		float m_speed;

		bool m_upDownWing;
		float m_maxAngleWing;
		float m_minAngleWing;

	public:
		Insecte(float speed = 1.0f);
		~Insecte(void);

		void createSkeleton(void);

		void translateLocal(Math::Vector3f translation);

		void rotateLocal(float angle, Math::Vector3f axis);

		float getSpeed(void);
		void setSpeed(float speed);

		void animateLocal(float dt);

	protected:
		void animateWings(float dt);
	};
}

#endif 