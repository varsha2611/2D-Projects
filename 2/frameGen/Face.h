#include <string>
#include <SDL.h>

class Face {
public:	
  Face(SDL_Renderer *renderer, SDL_Point center, int Radius, std::string Eye_type, std::string mouth_type ):
	renderer(renderer),center(center), Radius(Radius), Eye_type(Eye_type), mouth_type(mouth_type){};
~Face() = default;

Face(const Face &face)=default;
Face & operator=(const Face&face)
{
	if ( this == &face ) return *this;
		return *this;
	renderer = face.renderer;
	center = face.center;
	Radius = face.Radius;
	Eye_type = face.Eye_type;
	mouth_type = face.mouth_type;
	return *this;
}
  void drawFace();
  void drawEyes();
  void drawMouth();
  void drawFilledCircle();
  void drawCircle(int radius, SDL_Point cent, SDL_Color color, bool Semi = false);
  void drawCircleInverted( int radius,SDL_Point cent, SDL_Color color, bool Semi=false) ;
  void drawRectangle(float x, float y, float h, float w, SDL_Color color);
  void drawFilledRectangle(float x, float y, float h, float w, SDL_Color fill,SDL_Color border );
private:
   SDL_Renderer *renderer;
   SDL_Point center;
   int Radius;
   std::string Eye_type;
   std::string mouth_type;
};
