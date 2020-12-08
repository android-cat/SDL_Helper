#include"main.h"

int LoadImage(SDL_Surface** image, const char* filename) {//
	//�摜�ǂݍ��ݕ�
	*image = IMG_Load(filename);// sample.png��image�ɓǂݍ���
	if (*image == NULL) {//�摜���ǂݍ��߂Ȃ�������
		SDL_UnlockSurface(*image);//�摜�f�[�^���̂Ă鏈��
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}
	return 0;
}

int DrawPicture(SDL_Renderer** renderer, SDL_Surface* image, int x, int y) {
	SDL_Texture* image_texture = NULL;//�摜���g�����߂̃f�[�^�p
	image_texture = SDL_CreateTextureFromSurface(*renderer, image);
	if (image_texture == NULL) {//�e�N�X�`�����쐬�ł��Ă��Ȃ������Ƃ�
		SDL_UnlockSurface(image);//�摜�f�[�^���̂Ă鏈��
		SDL_DestroyTexture(image_texture);//�摜���g���ׂ̃f�[�^���폜����
		SDL_DestroyRenderer(*renderer);//�E�B���h�E�̕`�悷�邽�߂̏����폜����
		IMG_Quit();//SDL_IMage���I�����鏈��
		SDL_Quit();//SDL���I�����鏈��
		return 1;//�v���O�����ɃG���[������I������Ɠ`����
	}

	int image_x, image_y;//�摜�̑傫����ۑ����邽�߂̕ϐ�
	SDL_QueryTexture(image_texture, NULL, NULL, &image_x, &image_y);//�e�N�X�`��(�摜)�̑傫����m��֐�
	SDL_Rect imageRect = { 0,0,image_x,image_y };//�摜�̕W���̑傫���̎w��
	SDL_Rect drawRect = { x,y,image_x,image_y};//�摜��`�悷�鎞�̏ꏊ�̎w��

	SDL_RenderCopy(*renderer, image_texture, &imageRect, &drawRect);//�摜���E�B���h�E�ɕ`�悷�邽�߂̏��̕`�敔���ɑ���
	SDL_RenderPresent(*renderer);//�����ŕ`��I
	SDL_DestroyTexture(image_texture);//�����g��Ȃ��̂ŏ���
	return 0;
}

void CleanScreen(SDL_Renderer** renderer) {//Screen change all black
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);//�w��̃J���[�ŉ�ʂ�h��ݒ������
	SDL_RenderClear(*renderer);//���ۂɂʂ�
	SDL_RenderPresent(*renderer);//�����ŕ`��I
}