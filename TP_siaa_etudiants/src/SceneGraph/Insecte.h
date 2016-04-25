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
	protected:
		Translate m_rootTranslate;
		Rotate m_rootRotateY;
		Rotate m_rootRotateZ;

		Sphere *m_body;
		Scale m_scaleBody;

		Sphere *m_wing;
		Scale m_scaleWing;
		Translate m_translateAxeWingR;
		Translate m_translateAxeWingL;
		Rotate m_rotateWingR;
		Rotate m_rotateWingL;
		Translate m_translateWingR;
		Translate m_translateWingL;

		Sphere *m_eye;
		Scale m_scaleEye;
		Translate m_translateEyeR;
		Translate m_translateEyeL;

		double m_speed;

		bool m_upDownWing;
		double m_maxAngleWing;
		double m_minAngleWing;

	public:
		Insecte(double speed = 1.0f);
		~Insecte(void);

		void translateLocal(Math::Vector3f translation);

		void rotateLocalY(double angle);
		void rotateLocalZ(double angle);

		double getSpeed(void);
		void setSpeed(double speed);

		void animateLocal(double dt);

	protected:
		void animateWings(double dt);

		void createSkeleton(void);
	};
}

#endif 