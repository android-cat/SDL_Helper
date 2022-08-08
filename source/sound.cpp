#include"main.h"
int LoadSound(Mix_Music** music,std::string filename) {//
	*music = Mix_LoadMUS(filename.c_str());
	if (music == NULL)return 1;
	return 0;
}
int playSound(Mix_Music* music,int type) {
	Mix_PlayMusic(music,type);
	return 0;
}
