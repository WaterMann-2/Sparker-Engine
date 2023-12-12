#ifndef MATERIALMANAGER_H

#define MATERIALMANAGER_H

#include <iostream>
#include <fstream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <stb/stb_image.h>
#include <string>


#include "Shader/Shader.h"

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

struct Material {
	unsigned int id;
	bool enabled = true;
	std::string name;
	vector<Texture> textureDiffuse;
	vector<Texture> textureSpecular;

	float diffuse = 1.0f;
	float specular = 0.2f;
	float shininess = 0.2f;
	
	Material() :
		id(0),
		enabled(true),
		name("New Material"),
		textureDiffuse(),
		textureSpecular(),
		diffuse(1.0f),
		specular(0.25f),
		shininess(0.15f) {}
};

class MaterialManager {

public:

	void addMaterial(const Material& material) {
		materials.push_back(material);
	}

	void static setDefault(Material& material) {

	}


	void static materialToFile(Material &material, const char* filePath) {
		const char* extension = ".mat";
		std::string materialFile = std::string(filePath) + material.name + extension;
		std::ofstream file(materialFile);

		if (!std::filesystem::exists(filePath)) {
			std::cout << "[INFO]: Creating directory: " << filePath << std::endl;
			std::filesystem::create_directory(filePath);
		}


		if (file.is_open()) {
			file << material.id << std::endl << material.name;
			
		}
		else {
			std::cerr << "[ERROR]: Opening material file for writing: " << material.name << std::endl;
			return;
		}


		file.close();
	}

	void materialFromFile() {

	}

private:
	unsigned int highestID;
	std::vector<Material> materials;


};


#endif // !MATERIALMANGER_H
