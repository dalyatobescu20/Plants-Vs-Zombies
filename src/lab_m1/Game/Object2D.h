#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace Object2D
{

    // Create square with given bottom left corner, length and color
   
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float width, float lenght, glm::vec3 color, bool fill = false);
    Mesh* CreateDiamond(const std::string& name, glm::vec3 center, float side, float width, float lenght,  glm::vec3 color, bool fill = false);
    Mesh* CreateHexagon(const std::string &name, glm::vec3 leftBottomCorner,float width, float lenght, glm::vec3 color,glm::vec3 color2, bool fill = false);
    Mesh* CreateStar(const std::string &name, glm::vec3 leftBottomCorner, float width, float lenght, glm::vec3 color, bool fill = false);
    Mesh* CreateHeart(const std::string &name, glm::vec3 leftBottomCorner, float size,  glm::vec3 color, bool fill = false);

    
}
