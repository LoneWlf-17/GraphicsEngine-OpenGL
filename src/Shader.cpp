#include "GE/HelperClasses/Shader.h"

GE::Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	std::ifstream vertexFile;
	std::ifstream fragmentFile;
	std::string vertexString;
	std::string fragmentString;

	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);
		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexString = vertexStream.str();
		fragmentString = fragmentStream.str();

		vertexFile.close();
		fragmentFile.close();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER::FAILED_TO_OPEN_SHADER_FILES::" << e.what();
	}

	int success;
	char infolog[512];
	const char* vertexSource = vertexString.c_str();
	const char* fragmentSource = fragmentString.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_VERTEX_SHADER::" << infolog;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_FRAGMENT_SHADER::" << infolog;
	}

	id = glCreateProgram();
	glAttachShader(id, vertexShader);
	glAttachShader(id, fragmentShader);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, 512, NULL, infolog);
		std::cout << "ERROR::SHADER::FAILED_TO_LINK_PROGRAM::" << infolog;
	}

	std::cout << "LOG::SHADER::Shader has successfuly linked." << std::endl;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GE::Shader::Shader(int ShaderType)
{
    ShaderStrings shaderStr = InitializeShader(ShaderType);
    int success;
    char infolog[512];
    const char* vertexSource = shaderStr.VertexShader;
    const char* fragmentSource = shaderStr.FragmentShader;

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_VERTEX_SHADER::" << infolog;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FAILED_TO_COMPILE_FRAGMENT_SHADER::" << infolog;
    }

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(id, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FAILED_TO_LINK_PROGRAM::" << infolog;
    }

    std::cout << "LOG::SHADER::Shader has successfuly linked." << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GE::Shader::~Shader()
{
	glDeleteProgram(id);
}

void GE::Shader::Use()
{
	glUseProgram(id);
}

void GE::Shader::SetInt(std::string name, int value)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location != -1)
		glUniform1i(location, value);
}

void GE::Shader::SetFloat(std::string name, float value)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location != -1)
		glUniform1f(location, value);
}

void GE::Shader::SetVec3(std::string name, float* value)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location != -1)
		glUniform3fv(location, 1, value);
}

void GE::Shader::SetMat4(std::string name, float* value)
{
	int location = glGetUniformLocation(id, name.c_str());
	if (location != -1)
		glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

GE::ShaderStrings GE::Shader::InitializeShader(int ShaderType)
{
    ShaderStrings shaderstr;
    if (ShaderType == LIT_SHADER)
    {
        shaderstr.VertexShader = "#version 330 core\n"

            "layout(location = 0) in vec3 aPos;"
            "layout(location = 1) in vec3 aNormal;"
            "layout(location = 2) in vec2 aTexCoord;"

            "out vec2 TexCoord;"
            "out vec3 Normal;"
            "out vec3 FragPos;"

            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"

            "void main()"
            "{"
            "gl_Position = projection * view * model * vec4(aPos, 1.0f);"

            "TexCoord = aTexCoord;"
            "Normal = mat3(transpose(inverse(view * model))) * aNormal;"
            "FragPos = vec3(view * model * vec4(aPos, 1.0f));"
            "}";

        shaderstr.FragmentShader = "#version 330 core\n"
            "in vec2 TexCoord;"
            "in vec3 Normal;"
            "in vec3 FragPos;"

            "out vec4 FragColor;"

            "struct Material"
            "{"
            "sampler2D diffuse0;"
            "sampler2D specular0;"
            "};"

            "struct PointLight"
            "{"
            "vec3 position;"

            "vec3 ambient;"
            "vec3 diffuse;"
            "vec3 specular;"

            "float quadratic;"
            "float linear;"
            "};"

            "struct DirectionalLight"
            "{"
            "vec3 direction;"

            "vec3 ambient;"
            "vec3 diffuse;"
            "vec3 specular;"
            "};"

            "vec3 computePointLight(vec3 normalizedNorm, PointLight light, vec3 FragPos);"
            "vec3 computeDirectionalLight(vec3 normalizedNorm, DirectionalLight light, vec3 FragPos);"

            "uniform int PointLightNo;"
            "uniform int DirectionalLightNo;"
            "uniform Material material;"
            "uniform PointLight pointLights[50];"
            "uniform DirectionalLight directionalLights[5];"
            "uniform mat4 view;"

            "void main()"
            "{"
            "vec3 result = vec3(0.0f, 0.0f, 0.0f);"
            "for (int i = 0; i < PointLightNo; i++)"
            "{"
            "result += computePointLight(normalize(Normal), pointLights[i], FragPos);"
            "}"
            "for (int i = 0; i < DirectionalLightNo; i++)"
            "{"
            "result += computeDirectionalLight(normalize(Normal), directionalLights[i], FragPos);"
            "}"
            "FragColor = vec4(result, 1.0f);"
            "}"

            "vec3 computePointLight(vec3 normalizedNorm, PointLight light, vec3 FragPos)"
            "{"
            "vec3 lightPos = vec3(view * vec4(light.position, 1.0f));"
            "float distance = length(lightPos - FragPos);"
            "float attenuation = 1.0f / (1.0f + (light.linear * distance) + (light.quadratic * distance * distance));"

            "vec3 ambient = vec3(texture(material.diffuse0, TexCoord)) * light.ambient;"

            "vec3 lightDir = normalize(lightPos - FragPos);"
            "float diffuseStrength = max(dot(lightDir, normalizedNorm), 0.0f);"
            "vec3 diffuse = vec3(texture(material.diffuse0, TexCoord)) * light.diffuse * diffuseStrength;"

            "vec3 viewDir = normalize(-FragPos);"
            "vec3 reflectDir = reflect(-lightDir, normalizedNorm);"
            "float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);"
            "vec3 specular = vec3(texture(material.specular0, TexCoord)) * light.specular * specularStrength;"

            "vec3 result = (ambient + diffuse + specular) * attenuation;"
            "return result;"
            "}"

            "vec3 computeDirectionalLight(vec3 normalizedNorm, DirectionalLight light, vec3 FragPos)"
            "{"
            "vec3 ambient = vec3(texture(material.diffuse0, TexCoord)) * light.ambient;"

            "vec3 lightDir = normalize(-light.direction);"
            "float diffuseStrength = max(dot(lightDir, normalizedNorm), 0.0f);"
            "vec3 diffuse = vec3(texture(material.diffuse0, TexCoord)) * light.diffuse * diffuseStrength;"

            "vec3 viewDir = normalize(-FragPos);"
            "vec3 reflectDir = reflect(-lightDir, normalizedNorm);"
            "float specularStrength = pow(max(dot(viewDir, reflectDir), 0.0f), 32.0f);"
            "vec3 specular = vec3(texture(material.specular0, TexCoord)) * light.specular * specularStrength;"

            "vec3 result = (ambient + diffuse + specular);"
            "return result;"
            "}";
    }
    else if (ShaderType == UNLIT_SHADER)
    {
        shaderstr.VertexShader = "#version 330 core\n"

            "layout(location = 0) in vec3 aPos;"
            "layout(location = 1) in vec3 aNormal;"
            "layout(location = 2) in vec2 aTexCoord;"

            "out vec2 TexCoord;"

            "uniform mat4 model;"
            "uniform mat4 view;"
            "uniform mat4 projection;"

            "void main()"
            "{"
            "gl_Position = projection * view * model * vec4(aPos, 1.0f);"

            "TexCoord = aTexCoord;"
            "}";
        shaderstr.FragmentShader = "#version 330 core\n"

            "in vec2 TexCoord;"

            "out vec4 FragColor;"

            "struct Material"
            "{"
            "sampler2D diffuse0;"
            "sampler2D specular0;"
            "};"

            "uniform Material material;"

            "void main()"
            "{"
            "FragColor = texture(material.diffuse0, TexCoord);"
            "}";
    }

    return shaderstr;
}
