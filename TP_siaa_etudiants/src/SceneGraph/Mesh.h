#ifndef _SceneGraph_Mesh_H
#define _SceneGraph_Mesh_H

#include <HelperGl/Mesh.h>
#include <HelperGl/Draw.h>
#include <SceneGraph/NodeInterface.h>

namespace SceneGraph
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \class	Mesh
	///
	/// \brief	A Mesh drawer node with no optimization.
	///
	/// \author	F. Lamarche, Université de Rennes 1
	/// \date	01/12/2015
	////////////////////////////////////////////////////////////////////////////////////////////////////
	class Mesh : public virtual NodeInterface
	{
	private:
		/// \brief	The associated mesh.
		HelperGl::Mesh * m_mesh ;

	public:
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	Mesh::Mesh(HelperGl::Mesh * mesh)
		///
		/// \brief	Constructor.
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	01/12/2015
		///
		/// \param [in,out]	mesh	If non-null, the mesh.
		////////////////////////////////////////////////////////////////////////////////////////////////////
		Mesh(HelperGl::Mesh * mesh)
			: m_mesh(mesh)
		{}

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// \fn	virtual void Mesh::draw()
		///
		/// \brief	Draws this node (and the mesh ;) ).
		///
		/// \author	F. Lamarche, Université de Rennes 1
		/// \date	01/12/2015
		////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void draw()
		{
			HelperGl::Draw::draw(*m_mesh) ;
		}
	};
}

#endif