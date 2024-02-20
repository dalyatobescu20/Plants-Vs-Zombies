#include "lab_m1/Game/Game.h"
#include <vector>
#include <iostream>
#include <cmath>
#include <random>

#include "lab_m1/Game/Transform2D.h"
#include "lab_m1/Game/Object2D.h"
#include "Game.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Game::Game()
{
}


Game::~Game()
{
}

float CalculateHexagonRadius(float sideLength, float hexagonHeight) {
    // Assuming the hexagon is regular
    float radius = (sideLength / 2.0f) * (1.0f / std::cos(M_PI / 6.0f)) + hexagonHeight;
    return radius;
}
float CalculateStarRadius(float starWidth, float starHeight) {
    // Assuming the star is composed of a regular hexagon and a regular pentagon
    float radius = (starHeight / 2.0f) + (starWidth / 2.0f) * (1.0f / std::tan(M_PI / 10.0f));
    return radius;
}

float CalculateRhombusRadius(Mesh* mesh, const glm::vec3& center, int rhombusVertexCount) {
    float maxDistanceSquared = 0.0f;

    // Iterate through the vertices of the rhombus
    for (int i = 0; i < rhombusVertexCount; ++i) {
        // Assuming vertices are stored consecutively in the mesh
        const auto& vertex = mesh->vertices[i];
        
        // Calculate the squared distance from the center
        float distanceSquared = glm::length2(vertex.position - center);

        // Update the maximum squared distance
        maxDistanceSquared = std::max(maxDistanceSquared, distanceSquared);
    }

    // Return the square root of the maximum squared distance as the radius
    return std::sqrt(maxDistanceSquared);
}

void Game::CreateGreenSquares() {
      //make the squares
    float squareSide = 200;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    Mesh* greenSquare =  Object2D::CreateSquare("greenSquare", corner, squareSide, squareSide, glm::vec3(0.5, 1, 0.4), true);
    AddMeshToList(greenSquare);

    for(int i = 0; i < 9; i++) {
        squareList.push_back(Square(squareSide, squareSide, 0, 0, false, greenSquare));
    }

    //primul rand de patrate
    squareList[0].x = 200;
    squareList[0].y = 50;

    squareList[1].x = 200;
    squareList[1].y = 350;

    squareList[2].x = 200;
    squareList[2].y = 650;

    //al doilea rand de patrate
    squareList[3].x = 500;
    squareList[3].y = 50;
 
    squareList[4].x = 500;
    squareList[4].y = 350;

    squareList[5].x = 500;
    squareList[5].y = 650;

    //al treilea rand de patrate
    squareList[6].x = 800;
    squareList[6].y = 50;
  
    squareList[7].x = 800;
    squareList[7].y = 350;
   
    squareList[8].x = 800;
    squareList[8].y = 650;
   
}

void Game::CreateEmptySquare() {
    float squareSide = 200;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    Mesh* emptySquare =  Object2D::CreateSquare("emptySquare", corner, squareSide, squareSide, glm::vec3(0, 0, 0), false);
    AddMeshToList(emptySquare);

    for(int i = 0; i < 4; i++) {
        emptySquareList.push_back(Square(squareSide, squareSide, 0, 0, false, emptySquare));
    }

    //primul patrat
    emptySquareList[0].x = 130;
    emptySquareList[0].y = 1190;
 

    //al doilea patrat
    emptySquareList[1].x = 530;
    emptySquareList[1].y = 1190;
 

    //al treilea patrat
    emptySquareList[2].x = 930;
    emptySquareList[2].y = 1190;
 

    //al patrulea patrat
    emptySquareList[3].x = 1330;
    emptySquareList[3].y = 1190;

}

int getRandomLine() {
    // Use a random number generator from the <random> header
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 2);  // Range for your specific lines

    // Lines you want to choose from
    std::vector<int> lines = {150, 450, 750};

    // Choose a random line from the vector
    int randomLineIndex = distribution(gen);
    return lines[randomLineIndex];
}

std::string getRandomColors() {
    // Use a random number generator from the <random> header
    std::vector<std::string> hexagonMeshNames = {"hexagonBlue", "hexagonYellow", "hexagonPurple", "hexagonOrange"};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, hexagonMeshNames.size() - 1);
    
    int randomColorIndex = dis(gen);

    return hexagonMeshNames[randomColorIndex];
}


float getRandomInterval(float min, float max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max); // Adjust the range as needed

    return dis(gen);
}

glm::vec3 getRandomColorStar() {
     std::vector<glm::vec3> colors = {
        glm::vec3(0.102f, 0.737f, 0.612f), //turquoise
        glm::vec3(1, 0.5, 0), // Orange
        glm::vec3(0, 0.5, 1), // Light Blue
        glm::vec3(0, 0, 1),   // Blue
        glm::vec3(0.5, 0, 1), // Purple
        glm::vec3(1, 0, 1)    // Magenta
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, colors.size() - 1);

    int randomColorIndex = dis(gen);

    return colors[randomColorIndex];
}

float getRandomPositionStar() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2880);


    return dis(gen);
}


void Game::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float width = 100;
    float height = 800;

    // Initialize tx and ty (the translation steps)
    sign = 1;
    interval = 0;
    rezolutie = glm::vec2(resolution.x, resolution.y);
   

    // Initialize angularStep
    angularStep = 0;
    squareList = std::vector<Square>();
    emptySquareList = std::vector<Square>();
    hexagonsList = std::vector<Hexagon>();
    starsList = std::vector<Star>();
    starsPointsList = std::vector<Star>();
    proiectilList = std::vector<Proiectil>();
    pistols = std::vector<Pistol>();

    Mesh* rectangle =  Object2D::CreateSquare("rectangle", corner, width, height, glm::vec3(1, 0, 0.3), true);
    AddMeshToList(rectangle);
    
    //make the green squares
    float squareSide = 200;
    CreateGreenSquares();


    float sideLength = 80;
    float width1 = 60;
    float height1 = 100;
    glm::vec3 corner_d = glm::vec3(0, 0, 0.75);
    cx=corner_d.x;
    cy=corner_d.y;
    translateX = corner.x + width1 / 2;
    translateY = corner.y;
    Mesh* orange_diamond =  Object2D::CreateDiamond("orange_diamond", corner_d, sideLength, height1, width1 , glm::vec3 (1.0f, 0.5f, 0.0f), true);
    AddMeshToList(orange_diamond);

    Mesh* blue_diamond =  Object2D::CreateDiamond("blue_diamond", corner_d, sideLength, height1, width1 , glm::vec3 (0.2f, 0.0f, 1.0f), true);
    AddMeshToList(blue_diamond);

    Mesh* yellow_diamond =  Object2D::CreateDiamond("yellow_diamond", corner_d, sideLength, height1, width1 , glm::vec3 (1.0f, 1.0f, 0.1f), true);
    AddMeshToList(yellow_diamond);

    Mesh* purple_diamond =  Object2D::CreateDiamond("purple_diamond", corner_d, sideLength, height1, width1 , glm::vec3 (0.5f, 0.0f, 0.5f), true);
    AddMeshToList(purple_diamond);

    Mesh* emptySquare =  Object2D::CreateSquare("emptySquare", corner, squareSide, squareSide, glm::vec3(0, 0, 0), false);
    AddMeshToList(emptySquare);
    CreateEmptySquare();

    //hexagon blue
    Mesh* hexagon =  Object2D::CreateHexagon("hexagonBlue", corner_d, 40, 80, glm::vec3(0.2f, 0.0f, 1.0f), glm::vec3(0.5f, 0.5f, 1.0f), true);
    AddMeshToList(hexagon);

    //hexagon yellow
    Mesh* hexagonYellow =  Object2D::CreateHexagon("hexagonYellow", corner, 40, 80, glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), true);
    AddMeshToList(hexagonYellow);

    //hexagon purple
    Mesh* hexagonPurple =  Object2D::CreateHexagon("hexagonPurple", corner, 40, 80, glm::vec3(0.5f, 0.0f, 0.5f), glm::vec3(0.75f, 0.0f, 0.75f), true);
    AddMeshToList(hexagonPurple);

    //hexagon orange
    Mesh* hexagonOrange =  Object2D::CreateHexagon("hexagonOrange", corner, 40, 80, glm::vec3(1.0f, 0.5f, 0.0f), glm::vec3(1.0f, 0.75f, 0.5f), true);
    AddMeshToList(hexagonOrange);

    //star
    Mesh* star =  Object2D::CreateStar("star", corner, 20, 30, glm::vec3(1, 1, 1), true);
    AddMeshToList(star);
    
    //blue bullet
    Mesh* blueBullet =  Object2D::CreateStar("blueBullet", corner, 30, 50, glm::vec3(0, 0, 1), true);
    AddMeshToList(blueBullet);
    //yellow bullet
    Mesh* yellowBullet =  Object2D::CreateStar("yellowBullet", corner, 30, 50, glm::vec3(1, 1, 0), true);
    AddMeshToList(yellowBullet);
    //purple bullet
    Mesh* purpleBullet =  Object2D::CreateStar("purpleBullet", corner, 30, 50, glm::vec3(0.5f, 0.0f, 0.5f), true);
    AddMeshToList(purpleBullet);
    //orange bullet
    Mesh* orangeBullet =  Object2D::CreateStar("orangeBullet", corner, 30, 50, glm::vec3(1.0f, 0.5f, 0.0f), true);
    AddMeshToList(orangeBullet);


    Mesh* heart =  Object2D::CreateHeart("heart", corner, 150, glm::vec3(1, 0.4, 0.5), true);
    AddMeshToList(heart);

}


void Game::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    modelMatrix = glm::mat3(1);
    modelMatrix *= Transform2D::Translate(50, 50);
    RenderMesh2D(meshes["rectangle"], shaders["VertexColor"], modelMatrix);
    RenderGreenSquares();
}

void Game::RenderGreenSquares() {
    // Define variables for the initial positions
    float initialX = 200.0f;
    float initialY[] = {50.0f, 350.0f, 650.0f};

    //green squares
    // Loop through the rows and columns
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= Transform2D::Translate(initialX + col * 300.0f, initialY[row]);
            RenderMesh2D(squareList[row * 3 + col].square, shaders["VertexColor"], modelMatrix);
        }
    }
}

void Game::RenderDiamonds() {
    std::vector<glm::vec2> positions = {
        {200, 1300}, {600, 1300}, {1000, 1300}, {1400, 1300}
    };

    std::vector<std::string> meshNames = {
        "orange_diamond", "blue_diamond", "yellow_diamond", "purple_diamond"
    };

    // Loop through positions and mesh names
    for (int i = 0; i < positions.size(); ++i) {
        // Render the diamond
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(positions[i].x, positions[i].y);
        RenderMesh2D(meshes[meshNames[i]], shaders["VertexColor"], modelMatrix);

        // Render the empty square
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(positions[i].x - 70, positions[i].y - 110);
        RenderMesh2D(meshes["emptySquare"], shaders["VertexColor"], modelMatrix);
    }
}

void Game::RenderStars() {
    std::vector<int> starCosts = {1, 2, 2, 3, 3, 4, 4, 4};
    std::vector<float> starPositions = {145, 545, 615, 945, 1015, 1345, 1415, 1485};

    // Loop through star costs and positions
    for (int i = 0; i < starCosts.size(); ++i) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(starPositions[i], 1150);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }
}

void Game::RenderPistols(float deltaTimeSeconds) {
      // Render the diamond at click
    modelMatrix = glm::mat3(1);
    float mx = window->GetCursorPosition().x;
    float my = window->GetCursorPosition().y;
    mx = ((mx * 5120) / 1280) / 2;
    my = (my * 2880) / 720;
    my = (2880 - my) / 2;

    modelMatrix *= Transform2D::Translate(mx, my);
    RenderMesh2D(meshes[diamondType], shaders["VertexColor"], modelMatrix);


    //render at release pistols
    for(int i = 0 ; i < 9; i ++) {
        modelMatrix = glm::mat3(1);
        float x_Diamond = squareList[i].x + 50;
        float y_Diamond = squareList[i].y + 100;
        modelMatrix *= Transform2D::Translate(x_Diamond, y_Diamond);
    
        for(int j = 0; j < pistols.size(); j++) {
            if((pistols[j].x + 50 == x_Diamond && pistols[j].y + 100 == y_Diamond && pistols[j].destroy == true)
                || (pistols[j].x + 50 == x_Diamond && pistols[j].y + 100 == y_Diamond && pistols[j].pressed == true)) {
                modelMatrix *= Transform2D::Translate(translateX , translateY);
                modelMatrix *= Transform2D::Scale(pistols[j].scaleX, pistols[j].scaleY);
                modelMatrix *= Transform2D::Translate(-translateX, -translateY);
                pistols[j].scaleX -= deltaTimeSeconds;
                pistols[j].scaleY -= deltaTimeSeconds;
               
                if(pistols[j].scaleX <= 0.0f && pistols[j].scaleY <= 0.0f) {
                    diamondRelease[pistols[j].squareNumber] = "";
                    squareList[pistols[j].squareNumber].selected = false;
                    pistols.erase(pistols.begin() + j);
                }
            }
            
        }
         RenderMesh2D(meshes[diamondRelease[i]], shaders["VertexColor"], modelMatrix);

    }
}

void Game::RenderEnemy(float deltaTimeSeconds) {
    float colorChangeInterval = getRandomInterval(8.0f, 15.0f);
    elapsedTime += deltaTimeSeconds;
    if(elapsedTime >= colorChangeInterval) {
        elapsedTime = 0.0f;
        hexagonsList.push_back(Hexagon(hexagonHeight, hexagonWidth, 2880, 0, 0, 1, 1, -1, 0, -1, getRandomColors(), getRandomLine()));
    }

    for(int i = 0; i < hexagonsList.size(); i++) {
        if(hexagonsList[i].x <= 2880 && hexagonsList[i].x >= 0) {
            modelMatrix = glm::mat3(1);
            hexagonsList[i].x -= 2 * deltaTimeSeconds * 50;
            if(hexagonsList[i].x <= 0) {
                numberOfLifes--;
            }
            modelMatrix *= Transform2D::Translate(hexagonsList[i].x, hexagonsList[i].line);
            if(hexagonsList[i].destroy == false) {
                RenderMesh2D(meshes[hexagonsList[i].type], shaders["VertexColor"], modelMatrix);
            }else {
                modelMatrix *= Transform2D::Translate(cx , cy);
                modelMatrix *= Transform2D::Scale(hexagonsList[i].scaleX, hexagonsList[i].scaleY);
                modelMatrix *= Transform2D::Translate(-cx, -cy);
                hexagonsList[i].scaleX -= deltaTimeSeconds;
                hexagonsList[i].scaleY -= deltaTimeSeconds;
            
                if(hexagonsList[i].scaleX <= 0.0f && hexagonsList[i].scaleY <= 0.0f) {
                    for(int k = 0; k < proiectilList.size(); k ++) {
                        if(k == hexagonsList[i].proiectilNr) {
                            proiectilList.erase(proiectilList.begin() + k);
                        }
                    }
                    hexagonsList.erase(hexagonsList.begin() + i);
                }
                RenderMesh2D(meshes[hexagonsList[i].type], shaders["VertexColor"], modelMatrix);
            }
        }
            
    
    }   
}

void Game::SpawnStars(float deltaTimeSeconds) {
    float starSpawnInterval = getRandomInterval(4.0f, 10.0f);
    elapsedTimeStars += deltaTimeSeconds;
    if(elapsedTimeStars >= starSpawnInterval) {
        elapsedTimeStars = 0.0f;
        for(int i = 0; i < 3; i++) {
            Mesh* star = Object2D ::CreateStar("starBig", glm::vec3(0, 0, 0), 60, 80, glm::vec3(0.102f, 0.737f, 0.612f), true);
            starsList.push_back(Star(60, 80, getRandomPositionStar(),getRandomPositionStar(), glm::vec3(0.102f, 0.737f, 0.612f), star));
        }
    }
    for(int i = 0; i < starsList.size(); i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= Transform2D::Translate(starsList[i].x, starsList[i].y);
            RenderMesh2D(starsList[i].star, shaders["VertexColor"], modelMatrix);
    
    }
}

void Game::CollectStars(float deltaTimeSeconds) {
     for(int i = 0; i < starPoints; i++) {
        if(i > 7) {
            starPoints = 8;
            break;
        }
        starsPointsList.push_back(Star(40, 60, 170 + i * 70, 1150, glm::vec3(1, 1, 1), meshes["star"]));
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(1650 + i * 100, 1150);
        RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
    }

    
}

void Game::AddProiectils(float deltaTimeSeconds) {
      for(int i = 0 ; i < pistols.size(); i++) {
                for(int j = 0 ; j < hexagonsList.size(); j++) {
                    if(pistols[i].y  == hexagonsList[j].line - 100 && pistols[i].diamondType == hexagonsList[j].type
                         &&pistols[i].x < hexagonsList[j].x) {
                            pistols[i].time -= deltaTimeSeconds;
                            if(pistols[i].time <= 0) {
                                proiectilList.push_back(Proiectil(proiectilHeight, proiectilWidth, pistols[i].x + 50, pistols[i].y + 100, 0, 0, pistols[i].type, hexagonsList[j].type, meshes[pistols[i].type]));
                                pistols[i].time = 2.0f;
                            }
                    }
                
            }
    }
}

void Game::RenderProiectils(float deltaTimeSeconds) {
      for(int k = 0; k < proiectilList.size(); k ++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(proiectilList[k].x, proiectilList[k].y);
        proiectilList[k].z += 10 * deltaTimeSeconds * 100;
        proiectilList[k].angularStep -= 5 * deltaTimeSeconds; // Adjust the rotation speed as needed
        modelMatrix *= Transform2D::Translate(proiectilList[k].z, 0);
        modelMatrix *= Transform2D::Rotate(proiectilList[k].angularStep);
        RenderMesh2D(meshes[proiectilList[k].type], shaders["VertexColor"], modelMatrix);
    } 
    
}

void Game::Update(float deltaTimeSeconds)
{   

   // RenderGreenSquares();
    RenderDiamonds();
    RenderStars();

    //life bar
    for (int i = 0; i < numberOfLifes; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Transform2D::Translate(1650 + i * 250, 1250);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }

    // Render the diamond at click
    modelMatrix = glm::mat3(1);
    float mx = window->GetCursorPosition().x;
    float my = window->GetCursorPosition().y;
    mx = ((mx * 5120) / 1280) / 2;
    my = (my * 2880) / 720;
    my = (2880 - my) / 2;

    modelMatrix *= Transform2D::Translate(mx, my);
    RenderMesh2D(meshes[diamondType], shaders["VertexColor"], modelMatrix);

    //render pistols
    RenderPistols(deltaTimeSeconds);

    //spawn hexagoons
    RenderEnemy(deltaTimeSeconds);

    //spawn stars
    SpawnStars(deltaTimeSeconds);

    //collect stars
    CollectStars(deltaTimeSeconds);

    AddProiectils(deltaTimeSeconds);
    
    //render proiectil
    RenderProiectils(deltaTimeSeconds);
    

    //collision beetwen proiectil and hexagon
    for(int j = 0; j < hexagonsList.size(); j++) {
             for(int i = 0; i < proiectilList.size(); i++) {
                float distance = glm::distance(glm::vec2(proiectilList[i].z + proiectilList[i].x, proiectilList[i].y), glm::vec2(hexagonsList[j].x, hexagonsList[j].line));
                float hexagonRadius = CalculateHexagonRadius(hexagonWidth, hexagonHeight);
                float proiectilRadius = CalculateStarRadius(proiectilWidth, proiectilHeight);
                if(distance < hexagonRadius + proiectilRadius && proiectilList[i].hexagonType == hexagonsList[j].type) {
                    if(hexagonsList[j].starsNr != i + 1) {
                        hexagonsList[j].proiectilNr = i;
                        hexagonsList[j].count++;
                    }
                    if(hexagonsList[j].count == 3) {
                        hexagonsList[j].destroy = true;
                        hexagonsList[j].proiectilNr = i;
                        hexagonsList[j].starsNr = -1;
                    }
                    hexagonsList[j].starsNr = i;
                    proiectilList.erase(proiectilList.begin() + i);
                }
        }
    }

    //collision between pistol and hexagon
     for(int i = 0; i < pistols.size(); i ++) {
        for(int j = 0; j < hexagonsList.size(); j++) {
            float distace = glm::distance(glm::vec2(pistols[i].x + 50, pistols[i].y + 100), glm::vec2(hexagonsList[j].x, hexagonsList[j].line));
             if(distace <= 2) {
                pistols[i].destroy = true;
            }
         }
     }

}



void Game::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Game::OnInputUpdate(float deltaTime, int mods)
{
}


void Game::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Game::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Game::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
  
}


void Game::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    mouseX = ((mouseX * 5120) / 1280) / 2;
    mouseY = (mouseY * 2880) / 720;
    mouseY = (2880 - mouseY)/2;
    float deltaTimeSeconds = Engine::GetElapsedTime();
    //verificam daca s a dat click pe un romb
    // Check if the left mouse button is pressed
    if (button == 1)
    { 
      // Check if the mouse click is within the boundaries of the diamond
        diamondType = IsMouseInsideDiamond(mouseX, mouseY);
        starNumber = IsMouseInsideStar(mouseX, mouseY);
    } else if (button == 2) {
        // Check if the mouse click is within the boundaries of the square
        if (IsMouseInsideSquare(mouseX, mouseY) != -1 && squareList[IsMouseInsideSquare(mouseX, mouseY)].selected == true)
        {   
            // Mark the square as selected
            squareNumber = IsMouseInsideSquare(mouseX, mouseY);
            squareList[IsMouseInsideSquare(mouseX, mouseY)].selected = false;
            pistolNumber--;
            for(int i = 0; i < pistols.size(); i++) {
                if(pistols[i].squareNumber == squareNumber) {
                    pistols[i].pressed = true;
                }
            }
        } 

    }

}


int Game::findPistolPoints(std::string type) {
    if(type == "orange_diamond") {
        return 1;
    } else if (type == "blue_diamond") {
        return 2;
    } else if (type == "yellow_diamond") {
        return 2;
    } else if (type == "purple_diamond") {
        return 3;
    }
    return 0;
}

void Game::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    // Check if the left mouse button is released

  
    mouseX = ((mouseX * 5120) / 1280) / 2;
    mouseY = (mouseY * 2880) / 720;
    mouseY = (2880 - mouseY) / 2;

    if (button == 1)
    {   
        // Check if the mouse click is within the boundaries of the square
        if (IsMouseInsideSquare(mouseX, mouseY) != -1 && starPoints >= findPistolPoints(diamondType)
           && squareList[IsMouseInsideSquare(mouseX, mouseY)].selected == false && diamondType != "")
        {  
            // Mark the square as selected
            squareNumber = IsMouseInsideSquare(mouseX, mouseY);
            diamondRelease[squareNumber] = diamondType;
            squareList[IsMouseInsideSquare(mouseX, mouseY)].selected = true;

            starType = getStarColor(diamondType);
            hexagonType = connectColors(diamondType);
            pistols.push_back(Pistol(50, 100, squareList[squareNumber].x , squareList[squareNumber].y, 0, 2.0f, 1, 1, false,false, squareNumber, starType, hexagonType));
            pistolNumber++;
            starPoints -= findPistolPoints(diamondType);
            if(starPoints < 0) {
                starPoints = 0;
            } 
            starsPointsList.erase(starsPointsList.begin() + starPoints);    
        } else if (IsMouseInsideStar(mouseX, mouseY) != -1) {
            starNumber = IsMouseInsideStar(mouseX, mouseY);
            starsList.erase(starsList.begin() + starNumber);
            starPoints++;
        }
        diamondType = "";
    }
}

std::string Game::getStarColor(std::string type) {
    if(type == "orange_diamond") {
        return "orangeBullet";
    } else if (type == "blue_diamond") {
        return "blueBullet";
    } else if (type == "yellow_diamond") {
        return "yellowBullet";
    } else if (type == "purple_diamond") {
        return "purpleBullet";
    }       
    return "";
}

std::string Game::connectColors(std::string type) {
    if(type == "orange_diamond") {
        return "hexagonOrange";
    } else if (type == "blue_diamond") {
        return "hexagonBlue";
    } else if (type == "yellow_diamond") {
        return "hexagonYellow";
    } else if (type == "purple_diamond") {
        return "hexagonPurple";
    }       
    return "";
}

std::string Game::IsMouseInsideDiamond(int mouseX, int mouseY)
{   

    if(mouseX >= emptySquareList[0].x && mouseX <= emptySquareList[0].x + emptySquareList[0].width 
       && mouseY >= emptySquareList[0].y && mouseY <= emptySquareList[0].y + emptySquareList[0].height) {
       return "orange_diamond";
    } else if (mouseX >= emptySquareList[1].x && mouseX <= emptySquareList[1].x + emptySquareList[1].width 
       && mouseY >= emptySquareList[1].y && mouseY <= emptySquareList[1].y + emptySquareList[1].height) {
       return "blue_diamond";
    } else if (mouseX >= emptySquareList[2].x && mouseX <= emptySquareList[2].x + emptySquareList[2].width 
       && mouseY >= emptySquareList[2].y && mouseY <= emptySquareList[2].y + emptySquareList[2].height) {
       return "yellow_diamond";
    } else if (mouseX >= emptySquareList[3].x && mouseX <= emptySquareList[3].x + emptySquareList[3].width 
       && mouseY >= emptySquareList[3].y && mouseY <= emptySquareList[3].y + emptySquareList[3].height) {
       return "purple_diamond";
    }
    


    return "";
}

int Game::IsMouseInsideSquare(int mouseX, int mouseY)
{   
    if(mouseX >= squareList[0].x && mouseX <= squareList[0].x + squareList[0].width 
       && mouseY >= squareList[0].y && mouseY <= squareList[0].y + squareList[0].height) {
       return 0;
    } else if (mouseX >= squareList[1].x && mouseX <= squareList[1].x + squareList[1].width 
       && mouseY >= squareList[1].y && mouseY <= squareList[1].y + squareList[1].height) {
       return 1;
    } else if (mouseX >= squareList[2].x && mouseX <= squareList[2].x + squareList[2].width 
       && mouseY >= squareList[2].y && mouseY <= squareList[2].y + squareList[2].height) {
       return 2;
    } else if (mouseX >= squareList[3].x && mouseX <= squareList[3].x + squareList[3].width 
       && mouseY >= squareList[3].y && mouseY <= squareList[3].y + squareList[3].height) {
       return 3;
    } else if (mouseX >= squareList[4].x && mouseX <= squareList[4].x + squareList[4].width 
       && mouseY >= squareList[4].y && mouseY <= squareList[4].y + squareList[4].height) {
       return 4;
    } else if (mouseX >= squareList[5].x && mouseX <= squareList[5].x + squareList[5].width 
       && mouseY >= squareList[5].y && mouseY <= squareList[5].y + squareList[5].height) {
       return 5;
    } else if (mouseX >= squareList[6].x && mouseX <= squareList[6].x + squareList[6].width 
       && mouseY >= squareList[6].y && mouseY <= squareList[6].y + squareList[6].height) {
       return 6;
    } else if (mouseX >= squareList[7].x && mouseX <= squareList[7].x + squareList[7].width
         && mouseY >= squareList[7].y && mouseY <= squareList[7].y + squareList[7].height) {
         return 7;
     } else if (mouseX >= squareList[8].x && mouseX <= squareList[8].x + squareList[8].width 
         && mouseY >= squareList[8].y && mouseY <= squareList[8].y + squareList[8].height) {
         return 8;
     }

    return -1;
}

int Game::IsMouseInsideStar(int mouseX, int mouseY) {
    for(int i = 0; i < starsList.size(); i++) {
        if(mouseX + 80  >= starsList[i].x && mouseX - 30  <= starsList[i].x + starsList[i].height
       && mouseY + 80 >= starsList[i].y && mouseY - 30 <= starsList[i].y + starsList[i].width) {
            return i;
    }
    }
    return -1;
}



void Game::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Game::OnWindowResize(int width, int height)
{
}

