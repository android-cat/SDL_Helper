#ifdef _WIN32
#include <SDL.h>//SDLを使う為にインクルードする
#include<sdl_image.h>//SDL_Imageを使う為にインクルードする
#include<sdl_ttf.h>//SDL_TTFを使う為にインクルードする
#include<sdl_mixer.h>
#include<Windows.h>
#pragma comment(lib, "winmm.lib")
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#endif
#include<iostream>
#include<string>
#define FONT_PATH "Font/Mamelon-4-Hi-Regular.otf"
#define LOOP -1
#define NORMAL 0
//#define FONT_PATH "Font/ipaexg.ttf"
//#define FONT_PATH "Font/VL-PGothic-Regular.ttf"
int LoadImage(SDL_Surface** image, const char* filename);
int DrawPicture(SDL_Renderer** renderer, SDL_Surface* image, int x, int y);
void CleanScreen(SDL_Renderer** renderer);
int DrawString(SDL_Renderer** renderer,TTF_Font* font,std::string string,int x, int y);
int LoadSound(Mix_Music** music, std::string filename);
int playSound(Mix_Music* music, int type);