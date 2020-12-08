#include"main.h"
#define SCREEN_X 1280//SCREEN_X�Ƒł�1280�����͂����悤�ɂ���
#define SCREEN_Y 720//SCREEN_Y�Ƒł�720�����͂����悤�ɂ���
int Init(SDL_Window **window,SDL_Renderer**renderer,TTF_Font **font) {//Initialize
	if (SDL_Init(SDL_INIT_AUDIO) == -1 || SDL_Init(SDL_INIT_VIDEO)==-1||IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)==-1||TTF_Init()==-1||Mix_Init(MIX_INIT_MP3)) {//������
		TTF_Quit();
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}
	*window = SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, 0);//�E�B���h�E�쐬
	if (*window == NULL) {//�E�B���h�E���쐬�ł��Ă��Ȃ������Ƃ�
		SDL_DestroyWindow(*window);//�E�B���h�E���̂Ă鏈��
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (*renderer == NULL) {//�����_�[���쐬�ł��Ă��Ȃ������Ƃ�
		SDL_DestroyRenderer(*renderer);//�E�B���h�E�̕`�悷�邽�߂̏����폜����
		SDL_DestroyWindow(*window);//�E�B���h�E���̂Ă鏈��
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Mix_CloseAudio();
		SDL_DestroyRenderer(*renderer);//�E�B���h�E�̕`�悷�邽�߂̏����폜����
		SDL_DestroyWindow(*window);//�E�B���h�E���̂Ă鏈��
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return -1; 
	}
	*font = TTF_OpenFont(FONT_PATH, 40);
	if (*font == NULL) {
		Mix_CloseAudio();
		SDL_DestroyRenderer(*renderer);//�E�B���h�E�̕`�悷�邽�߂̏����폜����
		SDL_DestroyWindow(*window);//�E�B���h�E���̂Ă鏈��
		TTF_Quit();
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}
	return 0;
}

void Quit() {//Exit programs
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();//SDL_IMage���I�����鏈��
	SDL_Quit();//SDL���I�����鏈��
}


/*int main(int argc, char** argv) {//Sample
	SDL_Surface* image=NULL;//�摜������p
	SDL_Surface* image2 = NULL;
	Mix_Music* music;
	SDL_Window* window=NULL;//�E�B���h�E�̏������p
	SDL_Renderer* renderer=NULL;//�E�B���h�E���g���ׂ̃f�[�^�p
	SDL_Event event;
	TTF_Font* font=NULL;
	bool breakflag = false;
	//��������
	if (Init(&window,&renderer,&font))return 1;//�v���O�����ɃG���[������I������Ɠ`����

	//�摜�ǂݍ��ޕ�
	if (LoadImage(&image, "Resource/"))return 1;//�v���O�����ɃG���[������I������Ɠ`����
	if (LoadImage(&image2, "Resource/"))return 1;//�v���O�����ɃG���[������I������Ɠ`����
	if(LoadSound(&music,"Resource/"))return 1;
	//�`�敔
	while (1) {
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) {
				breakflag = true;
				break;
		}
		if (breakflag)break;
		CleanScreen(&renderer);
		SDL_Delay(33);//2000�~���b(2�b)�҂Ɠ`����
		DrawPicture(&renderer, image, 0, 0);
		SDL_Delay(33);//2000�~���b(2�b)�҂Ɠ`����
		CleanScreen(&renderer);
		SDL_Delay(33);
		DrawPicture(&renderer, image2,300,300);
		SDL_Delay(33);
		CleanScreen(&renderer);
		SDL_Delay(33);
		DrawString(&renderer,font,"�w������unti",100, 100);
		playSound(&music,NORMAL);
		SDL_Delay(33);
	}
	//�I������
	SDL_UnlockSurface(image);//�摜�f�[�^���̂Ă鏈��
	SDL_DestroyRenderer(renderer);//�E�B���h�E�̕`�悷�邽�߂̏����폜����
	SDL_DestroyWindow(window);//�E�B���h�E���폜����
	TTF_CloseFont(font);
	Quit();
	return 0;//�v���O�����ɏI��肾����I������Ɠ`����
}*/