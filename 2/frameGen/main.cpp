#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "frameGenerator.h"
#include <SDL_image.h>
#include "Face.h"
/*
Image source : https://www.pinterest.com/pin/506584658076889395/
*/
const std::string TITLE = "Expressions";
const std::string NAME = "Varshac";

const int WIDTH = 650;
const int HEIGHT = 520;

SDL_Surface* loadImage(std::string path, SDL_Surface* surface) {
  SDL_Surface* img = IMG_Load(path.c_str());
  if (img == NULL) {
    fprintf(stderr, "could not load image: %s\n", IMG_GetError());
    return NULL;
  }
  SDL_Surface* optimizedImg = SDL_ConvertSurface(img, surface->format, 0);
  if (optimizedImg == NULL) fprintf(stderr, "could not optimize image: %s\n", SDL_GetError());
  SDL_FreeSurface(img);
  return optimizedImg;
}


void writeName(SDL_Renderer* renderer) {
  TTF_Init();
  TTF_Font* font = TTF_OpenFont("fonts/arial.ttf", 24);
  if (font == NULL) {
    throw std::string("error: font not found");
  }
  SDL_Color textColor = {0xff, 0, 0, 0};
  SDL_Surface* surface = 
    TTF_RenderText_Solid(font, TITLE.c_str(), textColor);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

  int textWidth = surface->w;
  int textHeight = surface->h;
  SDL_FreeSurface(surface);
  SDL_Rect dst = {20, HEIGHT-40, textWidth, textHeight};

  SDL_RenderCopy(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}


int main(void) {
  try {
    if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
      std::cout << "Failed to initialize SDL2" << std::endl;
      return EXIT_FAILURE;
    }
    SDL_Window* window = SDL_CreateWindow(
      TITLE.c_str(),
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      WIDTH,
      HEIGHT,
      SDL_WINDOW_SHOWN
    );
    // Apparently we can't use hardware acceleration with
    // SDL_GetWindowSurface
    SDL_Renderer* renderer = SDL_CreateRenderer( 
      window, -1, SDL_RENDERER_SOFTWARE
    );
    //SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    SDL_RenderClear(renderer);
    Face face(renderer, {90, 90}, 80, "equal", "smile" );
    face.drawFace();    
    Face face2(renderer, {250,90}, 80, "equal", "open" );
    face2.drawFace();
    Face face3(renderer, {410,90}, 80, "laugh", "teeth" );
    face3.drawFace();
    Face face4(renderer, {570,90}, 80, "googly", "smile" );
    face4.drawFace();
	SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Surface* img = loadImage("image.jpg",surface);
   if (img == NULL) return 1;
    SDL_Rect DestR;
 
    DestR.x = 200;
    DestR.y = 317;
    SDL_BlitSurface(img, NULL, surface, &DestR);
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(img); img = NULL;
    SDL_FreeSurface(surface);
    Face face5(renderer, {90,250}, 80, "unequal", "tongue" );
    face5.drawFace();
    Face face6(renderer, {250,250}, 80, "equal", "sad" );
    face6.drawFace();
    Face face7(renderer, {410,250}, 80, "wonder", "wonder" );
    face7.drawFace();
    Face face8(renderer, {570,250}, 80, "chasma", "smile" );
    face8.drawFace();
    writeName(renderer);
    SDL_RenderPresent(renderer);
    FrameGenerator frameGen(renderer, window, WIDTH, HEIGHT, NAME);
    frameGen.makeFrame();

    SDL_Event event;
    const Uint8* keystate;
    while ( true ) {
      keystate = SDL_GetKeyboardState(0);
      if (keystate[SDL_SCANCODE_ESCAPE]) { break; }
      if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
          break;
        }
      }
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  }
  catch (const std::string& msg) { std::cout << msg << std::endl; }
  catch (...) {
    std::cout << "Oops, someone threw an exception!" << std::endl;
  }
  return EXIT_SUCCESS;
}
