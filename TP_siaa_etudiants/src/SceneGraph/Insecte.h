#ifndef _SceneGraph_Insecte_H
#define _SceneGraph_Insecte_H

#include <GL/glew.h>
#include <SceneGraph/NodeInterface.h>
#include <SceneGraph/Sphere.h>
#include <SceneGraph/Group.h>
#include <SceneGraph/Scale.h>
#include <SceneGraph/Translate.h>
#include <Math/Vectorf.h>

namespace SceneGraph
{
	class Insecte : public NodeInterface
	{
	private:
		Group m_root ;
		
		Sphere *m_sphereBody;
		Scale *m_scaleBody;

		Sphere *m_sphereWingR;
		Sphere *m_sphereWingL;
		Scale *m_scaleWingR;
		Scale *m_scaleWingL;
		Translate *m_translateWingR;
		Translate *m_translateWingL;

		Sphere *m_sphereEyeR;
		Sphere *m_sphereEyeL;
		Scale *m_scaleEyeR;
		Scale *m_scaleEyeL;
		Translate *m_translateEyeR;
		Translate *m_translateEyeL;

	public:
		Insecte(void);
		~Insecte(void);

		SceneGraph::Group * getSceneGraph();

		virtual void draw();
	};
}

#endif 