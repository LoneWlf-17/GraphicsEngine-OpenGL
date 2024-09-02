#include "GE/Components/Model.h"


GE::Model::Model(std::string modelPath, int ShaderType)
{
	loadModel(modelPath);
	/*
	if (ShaderType == UNLIT_SHADER)
		shader = new Shader(unlitDir + "\\unlit.vs", unlitDir + "\\unlit.fs");
	else if (ShaderType == LIT_SHADER)
		shader = new Shader(litDir + "\\lit.vs", litDir + "\\lit.fs");
	else if (ShaderType == LIGHT_SHADER)
		shader = new Shader(lightDir + "\\light.vs", lightDir + "\\light.fs");*/
	shader = new Shader(ShaderType);

}

void GE::Model::Draw(Shader* shader)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw(shader);
	}
}

void GE::Model::update()
{
	Draw(shader);
}

void GE::Model::loadModel(std::string modelPath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelPath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::MODEL::FAILED_TO_OPEN_MODEL" << std::endl;
	}

	directory = modelPath.substr(0, modelPath.find_last_of("\\"));

	std::cout << directory << std::endl;

	processNode(scene->mRootNode, scene);

	std::cout << "LOG::MODEL::Model has successfuly loaded." << std::endl;
}

void GE::Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

GE::Mesh GE::Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		vertex.position.x = mesh->mVertices[i].x;
		vertex.position.y = mesh->mVertices[i].y;
		vertex.position.z = mesh->mVertices[i].z;
		vertex.normal.x = mesh->mNormals[i].x;
		vertex.normal.y = mesh->mNormals[i].y;
		vertex.normal.z = mesh->mNormals[i].z;
		if (mesh->mTextureCoords[0])
		{
			vertex.texCoord.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoord.y = mesh->mTextureCoords[0][i].y;
		}
		else
			vertex.texCoord = glm::vec2(0.0f);
		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
		{
			indices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}

	if (mesh->mMaterialIndex >= 0)
	{
		std::vector<Texture> diffuseMaps = loadMaterialTexture(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_DIFFUSE, "diffuse");
		std::vector<Texture> specularMaps = loadMaterialTexture(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_SPECULAR, "specular");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<GE::Texture> GE::Model::loadMaterialTexture(aiMaterial* material, aiTextureType texType, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < material->GetTextureCount(texType); i++)
	{
		aiString texStr;
		material->GetTexture(texType, i, &texStr);
		bool skip = false;

		for (int j = 0; j < loadedTextures.size(); j++)
		{
			if (strcmp(loadedTextures[j].path.data(), texStr.C_Str()) == 0)
			{
				textures.push_back(loadedTextures[i]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			Texture texture;
			texture.type = typeName;
			texture.id = TextureFromFile(texStr.C_Str());
			texture.path = texStr.C_Str();
			textures.push_back(texture);
			loadedTextures.push_back(texture);
		}
	}

	return textures;
}

unsigned int GE::Model::TextureFromFile(std::string path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrChannels;
	GLenum format = GL_RGB;
	unsigned char* textureSource = stbi_load((directory + "\\" + path).c_str(), &width, &height, &nrChannels, 0);
	if (textureSource)
	{
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, textureSource);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(textureSource);
	}
	else
	{
		std::cout << "ERROR::TEXTURE::FAILED_TO_LOAD_TEXTURE " << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}

