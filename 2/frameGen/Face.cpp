#include <iostream>
#include <SDL2/SDL.h>
#include "Face.h"
#include <string>
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color YELLOW = {250,250,0, 255};
const SDL_Color WHITE = {255,255,255, 255};
void Face::drawFace()
{
	if(this->renderer == NULL)
		return;
	drawCircle( Radius, center, BLACK ); 
	drawCircle(Radius-5, center, YELLOW);
	drawEyes();
	drawMouth();
}
void Face::drawEyes()
{
	SDL_Point E1 = {center.x-20, center.y-20};
    	SDL_Point E2 = {center.x+20, center.y-20};
	int R_1 = 16;
	int R_2 = 16;
	if(Eye_type == "equal")
	{
		drawCircle(R_1,E1,BLACK);
		drawCircle(R_2,E2,BLACK);
	}
	if(Eye_type == "unequal")
	{
		drawCircle(R_1,E1,BLACK);
		drawCircle(R_2+5,E2,BLACK);
	}
	if(Eye_type == "laugh")
	{
	    drawCircleInverted(R_1,E1,BLACK);
	    drawCircleInverted(R_1-10,E1,YELLOW);
	    drawCircleInverted(R_2,E2,BLACK);
	    drawCircleInverted(R_2-10,E2,YELLOW);
	}
	if(Eye_type == "googly")
	{
		drawFilledRectangle(E1.x-20,E1.y,10,40,BLACK,BLACK);
		drawCircle(R_2,E2,BLACK);
	}
	if(Eye_type == "chasma")
	{
	    drawFilledRectangle(center.x-Radius,E1.y,10,Radius*2-5,BLACK,BLACK);
	    drawFilledRectangle(E1.x-20,E1.y-20,40,40,BLACK,BLACK);
	    drawFilledRectangle(E2.x-10,E2.y-20,40,40,BLACK,BLACK);
	    //drawCircleInverted(R_2-5,E2,YELLOW,true);
	}
       if(Eye_type == "wonder")
	{
	    drawCircle(R_1,E1,BLACK);
	    drawCircle(R_2,E2,BLACK);
	    drawCircle(R_1-5,E1,WHITE);
	    drawCircle(R_2-5,E2,WHITE);
	}
}
void Face::drawMouth()
{
	SDL_Point M = {center.x, center.y+10};
	float R_1 = 16;
	float R_2 = 16;
	if(mouth_type == "smile")
	{
		drawCircle(Radius-30,M,BLACK,true);
		drawCircle(Radius-40,M,YELLOW,true);
	}
	if(mouth_type == "open")
	{
		drawCircle(Radius-30,M,BLACK,true);
		drawCircle(Radius-40,M,WHITE,true);
                drawFilledRectangle(M.x-Radius+30,M.y,5,2*(Radius-30),BLACK,BLACK);
		
	}
	if(mouth_type == "teeth")
	{
		drawCircle(Radius-35,M,BLACK,true);
		drawCircle(Radius-45,M,WHITE,true);                
		drawFilledRectangle(M.x-10,M.y,35,25,BLACK,BLACK);
		drawFilledRectangle(M.x-9,M.y,35,20,WHITE,BLACK);
		drawFilledRectangle(M.x-Radius+35,M.y,5,2*(Radius-35),BLACK,BLACK);
	}
	if(mouth_type == "googly")
	{
		//drawRectangle();
		//drawRectangle();
	}
	if(mouth_type == "closed")
	{
	    drawCircleInverted(R_1,M,BLACK);
	    drawCircleInverted(R_1-10,M,YELLOW);
	    drawCircleInverted(R_2,M,BLACK);
	    drawCircleInverted(R_2-10,M,YELLOW);
	}
	if(mouth_type == "tongue")
	{
           SDL_Color color = {255, 0, 144, 255};
           SDL_Color color1 = {254,127, 156, 255};
	   drawFilledRectangle(M.x-Radius+60,M.y,40,(Radius-40),color1,color);
           drawFilledRectangle(M.x-Radius+90,M.y,40,10,color,color);
	   drawFilledRectangle(M.x-Radius+30,M.y,5,2*(Radius-30),BLACK,BLACK);		
		
	}
	if(mouth_type == "sad")
	{
	   M.y+=40;// = {Center.x,Center.y+40};
	   drawCircleInverted(Radius-30,M,BLACK,true);
	   drawCircleInverted(Radius-40,M,YELLOW,true);	
		
	}
	if(mouth_type == "wonder")
	{
	   SDL_Point E1 = {center.x, center.y+30};
	   drawCircle(30,E1,BLACK);
	   drawCircle(20,E1,WHITE);
		
	}
}

void Face::drawCircle( int radius, SDL_Point center, SDL_Color color, bool Semi) 
{
	if(this->renderer == NULL)
		return;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int x_gr = 2;
  int y_gr = 2;
  if(Semi)
	y_gr = 1;
  for (int w = 0; w < radius*x_gr ; w++) {
    for (int h = 0; h < radius*y_gr; h++) {
      int dx = radius - w; 
      int dy = radius - h;
      if ((dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}
void Face::drawCircleInverted( int radius, SDL_Point center, SDL_Color color, bool Semi) 
{
	if(this->renderer == NULL)
		return;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  int x_gr = 2;
  int y_gr = 2;
  if(Semi)
	x_gr = 2;
  for (int w = 0; w <=radius*x_gr ; w++) {
    for (int h = 0; h <radius*y_gr; h++) {
      int dx = radius - w; 
      int dy = radius - h;
      if ((dy<0)&&(dx*dx + dy*dy) <= (radius * radius)) {
        SDL_RenderDrawPoint(renderer, center.x + dx, center.y + dy);
      }
    }
  }
}

void Face::drawRectangle(float x, float y, float h, float w, SDL_Color color)
{
		SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
  SDL_RenderDrawRect( renderer, &r );
}

void Face::drawFilledRectangle(float x, float y, float h, float w, SDL_Color fill,SDL_Color border )
{
		SDL_Rect r;
  r.x = x;
  r.y = y;
  r.w = w;
  r.h = h;
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor( renderer, fill.r, fill.g, fill.b, fill.a );
  SDL_RenderFillRect( renderer, &r );
  SDL_SetRenderDrawColor( renderer, border.r, border.g, border.b, border.a );
  SDL_RenderDrawRect( renderer, &r );
}
