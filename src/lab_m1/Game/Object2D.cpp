#include "Object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"



Mesh* Object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float width,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(width, 0, 0), color),
        VertexFormat(corner + glm::vec3(width, height, 0), color),
        VertexFormat(corner + glm::vec3(0, height, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);


    return square;
}

// Create a diamond shape
Mesh* Object2D::CreateDiamond(
   const std::string &name,
    glm::vec3 center,
    float sideLength,
    float rectangleWidth,
    float rectangleHeight,
    glm::vec3 color,
    bool fill)
{
    // Define the dimensions of the rhombus and rectangle
    glm::vec3 rhombusHalfDimensions(sideLength / 2.0f, sideLength / 2.0f, 0.0f);
    glm::vec3 rectangleHalfDimensions(rectangleWidth / 2.0f, rectangleHeight / 2.0f, 0.0f);

    // Define the vertices for the rhombus
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, -sideLength, 0), color),  // Bottom vertex
        VertexFormat(center + glm::vec3(-rhombusHalfDimensions.x, 0, 0), color),  // Left vertex
        VertexFormat(center + glm::vec3(0, sideLength, 0), color),  // Top vertex
        VertexFormat(center + glm::vec3(rhombusHalfDimensions.x, 0, 0), color)   // Right vertex
    };

    // Adjust the center position for the rectangle
    glm::vec3 rectangleCenter = center + glm::vec3(rectangleHeight, 0, 0);

    // Define the vertices for the rectangle
    std::vector<VertexFormat> rectangleVertices =
    {
        VertexFormat(rectangleCenter - rectangleHalfDimensions, color),  // Bottom-left vertex
        VertexFormat(rectangleCenter + glm::vec3(rectangleHalfDimensions.x, -rectangleHalfDimensions.y, 0), color),  // Bottom-right vertex
        VertexFormat(rectangleCenter + rectangleHalfDimensions, color),  // Top-right vertex
        VertexFormat(rectangleCenter + glm::vec3(-rectangleHalfDimensions.x, rectangleHalfDimensions.y, 0), color)  // Top-left vertex
    };

    Mesh* rhombusWithRectangle = new Mesh(name);

    // Define the indices for drawing the rhombus and rectangle
    std::vector<unsigned int> indices;

    if (fill) {
        // Draw the rhombus as two triangles
        indices = { 0, 1, 2,
                     0, 2, 3 };

        // Add indices for the rectangle (two triangles)
        indices.insert(indices.end(), { 4, 5, 6, 4, 6, 7 });
    }

    // Combine the vertices and indices for the rhombus and rectangle
    vertices.insert(vertices.end(), rectangleVertices.begin(), rectangleVertices.end());

    rhombusWithRectangle->InitFromData(vertices, indices);

    return rhombusWithRectangle;
}

Mesh* Object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float width,
    float lenght,
    glm::vec3 color,
    glm::vec3 color2,
    bool fill)
{   

    //hexagon mare
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(glm::vec3(0, 0, 1), color),
        VertexFormat(glm::vec3(width, lenght, 1), color),
        VertexFormat(glm::vec3(-width, lenght, 1), color),
        VertexFormat(glm::vec3(-lenght, 0, 1), color),
        VertexFormat(glm::vec3(-width, -lenght, 1), color),
        VertexFormat(glm::vec3(width, -lenght, 1), color),
        VertexFormat(glm::vec3(lenght, 0, 1), color),
    };
    Mesh* hexagon = new Mesh(name);
    std::vector<unsigned int> indices = { 
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,1
    };


    //hexagon mic

    std::vector<VertexFormat> vertices1 =
    {   
        VertexFormat(glm::vec3(0, 0, 2), color2),
        VertexFormat(glm::vec3(width/1.5, lenght/1.5, 2), color2),
        VertexFormat(glm::vec3(-width/1.5, lenght/1.5, 2), color2),
        VertexFormat(glm::vec3(-lenght/1.5, 0, 2), color2),
        VertexFormat(glm::vec3(-width/1.5, -lenght/1.5, 2), color2),
        VertexFormat(glm::vec3(width/1.5, -lenght/1.5, 2), color2),
        VertexFormat(glm::vec3(lenght/1.5, 0, 2), color2),
    };


    std::vector<unsigned int> indices1 = {
        7, 8, 9,
        7, 9, 10,
        7, 10, 11,
        7, 11, 12,
        7, 12, 13,
        7, 13, 8
    };
    
        // Append the vertices and indices for the small hexagon
    vertices.insert(vertices.end(), vertices1.begin(), vertices1.end());
    indices.insert(indices.end(), indices1.begin(), indices1.end());

    hexagon->InitFromData(vertices, indices);
    
    //small hexagon inside

    return hexagon;

}


Mesh* Object2D::CreateStar(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float width,
    float lenght,
    glm::vec3 color,
    bool fill)
{
        std::vector<VertexFormat> vertices =
        {
            VertexFormat(glm::vec3(0, 0, 1), color),
            VertexFormat(glm::vec3(0, lenght/1.5, 1), color),
            VertexFormat(glm::vec3(-lenght, 0, 1), color),
            VertexFormat(glm::vec3(-width, -lenght, 1), color),
            VertexFormat(glm::vec3(width, -lenght, 1), color),
            VertexFormat(glm::vec3(lenght, 0, 1), color),
        
        };
        Mesh* hexagon = new Mesh(name);
        std::vector<unsigned int> indices = { 
            0,1,3,
            0,3,5,
            0,5,2,
            0,2,4,
            0,4,1

        };

        hexagon->InitFromData(vertices, indices);
    

        //small hexagon insie
    
        return hexagon;
}

Mesh* Object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length / 2, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, length / 2, 0), color),
        VertexFormat(corner + glm::vec3(0, length * 3 / 4, 0), color),
        VertexFormat(corner + glm::vec3(length / 4, length, 0), color),
        VertexFormat(corner + glm::vec3(length / 2, length * 3 / 4, 0), color),
        VertexFormat(corner + glm::vec3(length * 3 / 4, length, 0), color),
        VertexFormat(corner + glm::vec3(length, length * 3 / 4, 0), color),
        VertexFormat(corner + glm::vec3(length, length / 2, 0), color)
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        indices = { 0, 1, 2, 3, 4, 5, 6, 7 };
        heart->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices = { 0, 1, 7,
                    1, 4, 7,
                    1, 2, 4,
                    2, 3, 4,
                    4, 5, 6,
                    4, 6, 7 };
    }

    heart->InitFromData(vertices, indices);
    return heart;
}
