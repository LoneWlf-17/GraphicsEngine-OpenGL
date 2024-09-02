#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GE/HelperClasses/Shader.h"

namespace GE
{
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texCoord;
	};

	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};

	class Mesh
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> Textures);

		void Draw(Shader* shader);
	private:
		unsigned int VAO;

		void setupMesh();
	};
}

