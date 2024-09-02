#pragma once

#include <iostream>
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GE/Components/Component.h"

namespace GE
{
    class Light : public Component
    {
    public:
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;

        Light();
        Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

        float* getAmbient();
        float* getDiffuse();
        float* getSpecular();

        void update() override;
    };
}

