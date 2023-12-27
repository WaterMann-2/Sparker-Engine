#ifndef MODELIMPORTER_H

#define MODEL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Shader/Shader.h"
#include "GameObject/Mesh.h"
#include "Utility/MaterialManager.h"
#include "Mesh.h"

class ModelImporter {


public:

	ModelImporter();

	vector<Mesh> RetrieveMeshes();

	void Cleanup();

	void ImportModel(const char* modelPath);

private:
	vector<Mesh> meshes;
	vector<Material> textures_loaded;
	string directory;

	void loadModel(const char* path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);

};

#endif // !MODELIMPORTER_H
