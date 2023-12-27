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
#include "ModelImporter.h"

ModelImporter::ModelImporter() {

}

vector<Mesh> ModelImporter::RetrieveMeshes() {

}

void ModelImporter::Cleanup() {
	meshes.clear();
	
}

void ModelImporter::ImportModel(const char* modelPath) {
	loadModel(modelPath);
}

void ModelImporter::loadModel(const char* Path) {
	string path = Path;
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_ALLOW_SHARED || !scene->mRootNode) {
		std::cout << "[ERROR]: Assimp importer failure. Assimp error: " << std::endl << importer.GetErrorString() << endl;
		return;
	}

	directory = path.substr(0, path.find_last_of('/'));

	std::cout << "[INFO]: Model Directory: " << directory << std::endl;

	processNode(scene->mRootNode, scene);
}

void ModelImporter::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
}

Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vector;
		Vertex vertex;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;

		vertex.Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;

		vertex.Normal = vector;

		if (mesh->mTextureCoords[0]) {
			vertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			vertex.TexCoords.x = 0.0f;
			vertex.TexCoords.y = 0.0f;
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		//aiFace face =
	}
}