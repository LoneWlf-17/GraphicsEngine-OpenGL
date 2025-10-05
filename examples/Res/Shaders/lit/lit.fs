#version 330 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

struct Material
{
    sampler2D diffuse0;
    sampler2D specular0;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float quadratic;
    float linear;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

vec3 computePointLight(vec3 normalizedNorm, PointLight light, vec3 FragPos);
vec3 computeDirectionalLight(vec3 normalizedNorm, DirectionalLight light, vec3 FragPos);

uniform int PointLightNo;
uniform int DirectionalLightNo;
uniform Material material;
uniform PointLight pointLights[50];
uniform DirectionalLight directionalLights[5];
uniform mat4 view;

void main()
{
    vec3 result = vec3(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < PointLightNo; i++)
    {
        result += computePointLight(normalize(Normal), pointLights[i], FragPos);
    }
    for (int i = 0; i < DirectionalLightNo; i++)
    {
        result += computeDirectionalLight(normalize(Normal), directionalLights[i], FragPos);
    }
    FragColor = vec4(result, 1.0f);
}

vec3 computePointLight(vec3 normalizedNorm, PointLight light, vec3 FragPos)
{
    vec3 lightPos = vec3(view * vec4(light.position, 1.0f));
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0f / (1.0f + (light.linear * distance) + (light.quadratic * distance * distance));

    vec3 ambient = vec3(texture(material.diffuse0, TexCoord)) * light.ambient;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseStrength = max(dot(lightDir, normalizedNorm), 0.0f);
    vec3 diffuse = vec3(texture(material.diffuse0, TexCoord)) * light.diffuse * diffuseStrength;

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normalizedNorm);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = vec3(texture(material.specular0, TexCoord)) * light.specular * specularStrength;

    vec3 result = (ambient + diffuse + specular) * attenuation;
    return result;
}

vec3 computeDirectionalLight(vec3 normalizedNorm, DirectionalLight light, vec3 FragPos)
{
    vec3 ambient = vec3(texture(material.diffuse0, TexCoord)) * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diffuseStrength = max(dot(lightDir, normalizedNorm), 0.0f);
    vec3 diffuse = vec3(texture(material.diffuse0, TexCoord)) * light.diffuse * diffuseStrength;

    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normalizedNorm);
    float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);
    vec3 specular = vec3(texture(material.specular0, TexCoord)) * light.specular * specularStrength;

    vec3 result = (ambient + diffuse + specular);
    return result;
}