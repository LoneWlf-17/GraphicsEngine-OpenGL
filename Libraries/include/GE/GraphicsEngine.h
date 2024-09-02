#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "HelperClasses/Mesh.h"
#include "HelperClasses/Shader.h"

#include "Components/Component.h"
#include "Components/DirectionalLight.h"
#include "Components/Light.h"
#include "Components/Model.h"
#include "Components/PointLight.h"
#include "Components/Transform.h"

#include "Entity/Object.h"
#include "Entity/Camera.h"
#include "Entity/SceneObject.h"
#include "Entity/Scene.h"