#pragma once

#include "components/simple_scene.h"

struct Square {
      float height;
      float width;
      float x;
      float y;
      bool selected;
      Mesh* square;

    Square(float h, float w, float x, float y, bool selected, Mesh* sq) : 
            height(h), 
            width(w), 
            x(x),
            y(y),
            selected(selected),
            square(sq) {}
};

struct Hexagon {
      float height;
      float width;
      float x;
      float y;
      float destroy;
      float scaleX, scaleY;
      int proiectilNr;
      int count;
      int starsNr;
      std::string type;
      float line;

    Hexagon(float h, float w, float x, float y, float destroy, float scaleX, float scaley, int proiectilNr, int count, int starsNumber, std::string type, float line) : 
            height(h), 
            width(w), 
            x(x),
            y(y),
            destroy(destroy),
            scaleX(scaleX),
            scaleY(scaley),
            proiectilNr(proiectilNr),
            count(count),
            starsNr(starsNumber),
            type(type),
            line(line){}
};

struct Star {
      float width;
      float height;
      float x,y;
      glm::vec3 color;
      Mesh* star;

      Star(float w, float h, float x,float y, glm::vec3 color, Mesh* star) : 
               width(w), 
               height(h), 
               x(x),
               y(y),
               color(color),
               star(star)

               {}



};

struct Pistol {
      float width;
      float height;
      float x,y,z;
      float time;
      float scaleX, scaleY;
      bool destroy;
      bool pressed;
      int squareNumber;
      std::string type;
      std::string diamondType;

      Pistol(float w, float h, float x,float y, float z, float time,
      float scaleX, float scaleY, bool destroy, bool pressed, int squareNumber, std::string type, std::string diamondType) : 
               width(w), 
               height(h), 
               x(x),
               y(y),
               z(z),
               time(time),
               scaleX(scaleX),
               scaleY(scaleY),
               destroy(destroy),
               pressed(pressed),
               squareNumber(squareNumber),
               type(type),
               diamondType(diamondType)
               {}
};

struct Proiectil {
         float width;
         float height;
         float x,y,z;
         float angularStep;
         std::string type;
         std::string hexagonType;
         Mesh* star;

         Proiectil(float w, float h, float x, float y, float z, float angularStep, std::string type, std::string hexagonType,Mesh* star) : 
                  width(w), 
                  height(h), 
                  x(x),
                  y(y),
                  z(z),
                  angularStep(angularStep),
                  type(type),
                  hexagonType(hexagonType),
                  star(star)
                  {}

         
};

namespace m1
{
    class Game : public gfxc::SimpleScene
    {
     public:
        Game();
        ~Game();

        void Init() override;
        void CreateGreenSquares();
        void CreateEmptySquare();
        void RenderGreenSquares();
        void RenderDiamonds();
        void RenderStars();
        void RenderPistols(float deltaTimeSeconds);
        void RenderEnemy(float deltaTimeSeconds);
        void SpawnStars(float deltaTimeSeconds);
        void CollectStars(float deltaTimeSeconds);
        void AddProiectils(float deltaTimeSeconds);
        void RenderProiectils(float deltaTimeSeconds);

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        std::string IsMouseInsideDiamond(int mouseX, int mouseY);
        int IsMouseInsideSquare(int mouseX, int mouseY);
        int IsMouseInsideStar(int mouseX, int mouseY);
        int findPistolPoints(std::string type);
        std::string getStarColor(std::string type) ;
        std::string connectColors(std::string type);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float translateX2, translateY2;
        float scaleX, scaleY, interval;
        float angularStep, sign;

        std::vector<Square> squareList;
        std::vector<Square> emptySquareList;
        std::vector<Hexagon> hexagonsList;
        std::vector<Star> starsList;
        std::vector<Star> starsPointsList;
        std::vector<Pistol> pistols;
         std::vector<Proiectil> proiectilList;
        std::string diamondType = "";
         std::string starType = "";
         std::string hexagonType = "";
        std::string diamondRelease[9];
        std::vector<int> pistolsToDelete;

        glm::vec2 initialMousePos;
        glm::vec2 rezolutie;
        std::vector<glm::vec3> colors;
        int squareNumber = -1;
        int numberOfLifes = 3;
        int starPoints = 0;
        int starNumber = -1;
        int pistolNumber = 0;
   
        float hexagonHeight = 40;
        float hexagonWidth = 80;

         float elapsedTime = 0.0f;
         float elapsedTimeStars = 0.0f;

         float bulletsInterval = 0.0f;

         float proiectilHeight = 50;
         float proiectilWidth = 30;

         int pressed = 0;
         
   


        // TODO(student): If you need any other class variables, define them here.

    };

    
}   // namespace m1
