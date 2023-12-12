#ifndef MESHRENDERER_H

#define MESHRENDERER_H

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "GameObject/Component.h"
#include "Utility/MaterialManager.h"
#include "GameObject/Mesh.h"

class MeshRenderer : public Component {
public:

	vector<Material*> Materials;
	Mesh* mesh;

	MeshRenderer();

	void EarlyFrame() override;


private:


};

#endif // !MESHRENDERER_H
