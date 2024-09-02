#pragma once

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GE/Components/Light.h"

namespace GE
{
    class DirectionalLight : public Light
    {
    public:
        glm::vec3 Direction;

        DirectionalLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

        float* getDirection();

        void update() override;
    };

}

