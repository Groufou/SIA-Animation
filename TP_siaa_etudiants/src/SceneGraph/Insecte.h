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

namespace SceneGraph
{
	class Insecte : public Group
	{
	private:
		Translate *m_rootTranslate;
		Rotate *m_rootRotate;

		Sphere *m_body;
		Scale *m_scaleBody;

		Sphere *m_wing;
		Scale *m_scaleWing;
		Translate *m_translateWingR;
		Translate *m_translateWingL;

		Sphere *m_eye;
		Scale *m_scaleEye;
		Translate *m_translateEyeR;
		Translate *m_translateEyeL;

		float m_speed;

	public:
		Insecte(float speed = 1.0f);
		~Insecte(void);

		void createSkeleton(void);

		void translateLocal(Math::Vector3f translation);

		void rotateLocal(float angle, Math::Vector3f axis);

		float getSpeed(void);
	};
}

#endif 