#version 330 core

in vec2 TexCoord;

out vec4 FragColor;

struct Material
{
    sampler2D diffuse0;
    sampler2D specular0;
};

uniform Material material;

void main()
{
    FragColor = texture(material.diffuse0, TexCoord);
}