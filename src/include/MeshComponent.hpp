#ifndef PUGGO_MESH_COMPONENT_HPP
#define PUGGO_MESH_COMPONENT_HPP

namespace puggo {
	struct MeshComponent {
		unsigned int VAO = 0;
		unsigned int VBO = 0;
		unsigned int numVertices = 0;
	};
}

#endif // !PUGGO_MESH_COMPONENT_HPP
