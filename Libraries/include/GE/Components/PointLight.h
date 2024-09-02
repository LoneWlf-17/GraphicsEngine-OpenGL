#pragma once

#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GE/Components/Light.h"
#include "GE/HelperClasses/Shader.h"

namespace GE
{
    class PointLight : public Light
    {
    private:
        float linear, quadratic;
    public:
        glm::vec3 Position;

        PointLight(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float linear, float quadratic);

        float* getPosition();
        float getLinear() const;
        float getQuadratic() const;

        void update() override;
    };
}


