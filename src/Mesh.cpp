#include "GE/HelperClasses/Mesh.h"

GE::Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void GE::Mesh::Draw(Shader* shader)
{
	shader->Use();
	int diffuseNr = 0;
	int specularNr = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::string name;
		if (textures[i].type == "diffuse")
			name = textures[i].type + std::to_string(diffuseNr++);
		else if (textures[i].type == "specular")
			name = textures[i].type + std::to_string(specularNr++);
		//std::cout << "material." + name << std::endl;
		shader->SetInt("material." + name, i);
		glBindTexture(GL_TEXTURE_2D, textures[0].id);
	}
	glActiveTexture(GL_TEXTURE0);

	glBindVertexArray(VAO);
	shader->Use();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void GE::Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int Buffers[2];
	glGenBuffers(2, Buffers);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}
