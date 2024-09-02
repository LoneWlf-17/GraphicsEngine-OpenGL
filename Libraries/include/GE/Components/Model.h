#pragma once

#include <iostream>
#include <vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "stb_image/stb_image.h"

#include "GE/HelperClasses/Shader.h"
#include "GE/HelperClasses/Mesh.h"
#include "GE/Components/Component.h"

namespace GE
{

	class Model : public Component
	{
	public:

		Shader* shader;

		Model(std::string modelPath, int ShaderType);

		void Draw(Shader* shader);

		void update() override;
	private:
		std::vector<Mesh> meshes;
		std::string directory;
		std::vector<Texture> loadedTextures;

		//std::string unlitDir = "C:\\SampleProjects\\OpenGL\\OpenGLChapter3FinishingProject\\GraphicsEngine-OpenGL\\Res\\Shaders\\unlit";
		//std::string litDir = "C:\\SampleProjects\\OpenGL\\OpenGLChapter3FinishingProject\\GraphicsEngine-OpenGL\\Res\\Shaders\\lit";
		//std::string lightDir = "C:\\SampleProjects\\OpenGL\\OpenGLChapter3FinishingProject\\GraphicsEngine-OpenGL\\Res\\Shaders\\light";

		void loadModel(std::string modelPath);

		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<Texture> loadMaterialTexture(aiMaterial* material, aiTextureType texType, std::string typeName);
		unsigned int TextureFromFile(std::string path);
	};

}

