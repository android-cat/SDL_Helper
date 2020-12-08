#include"main.h"
#ifdef _WIN32
std::string SjistoUTF8(std::string Sjis)//Change UTF8
{
	//UTF16�֕ϊ���̕����񒷂𓾂�
	int lenghtUTF16 = MultiByteToWideChar(CP_THREAD_ACP, 0, Sjis.c_str(), Sjis.size() + 1, NULL, 0);

	//�K�v�ȕ�����Unicode������̃o�b�t�@���m��
	wchar_t* bufUnicode = new wchar_t[lenghtUTF16];

	//ShiftJIS����Unicode�֕ϊ�
	MultiByteToWideChar(CP_THREAD_ACP, 0, Sjis.c_str(),Sjis.size() + 1, bufUnicode, lenghtUTF16);

	//UTF8�֕ϊ���̕����񒷂𓾂�
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//�K�v�ȕ�����UTF8������̃o�b�t�@���m��
	char* bufUTF8 = new char[lengthUTF8];

	//Unicode����UTF8�֕ϊ�
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenghtUTF16 - 1, bufUTF8, lengthUTF8, NULL, NULL);

	std::string UTF8(bufUTF8);

	delete[lenghtUTF16] bufUnicode;
	delete[lengthUTF8] bufUTF8;

	return UTF8;
}
#endif

int DrawString(SDL_Renderer** renderer, TTF_Font* font,std::string string,int x, int y) {//Show string
	SDL_Surface *surface=NULL;
	SDL_Texture* texture = NULL;

#ifdef _WIN32
	std::string shiftjis=string;
	string=SjistoUTF8(shiftjis);
#endif

	surface = TTF_RenderUTF8_Blended(font,string.c_str(),{ 255, 255, 255, 255 });
    if (surface == NULL)return 1;

	texture = SDL_CreateTextureFromSurface(*renderer, surface);
    if (texture == NULL)return 1;

    //������`�ʂ���Texture�̃T�C�Y���擾����      
    int text_x,text_y;
    SDL_QueryTexture(texture, NULL, NULL, &text_x, &text_y);
    SDL_Rect txtRect = { 0,0,text_x,text_y};
    SDL_Rect pasteRect = {x,y,text_x,text_y};

    //Texture��`�ʂ���            
    SDL_RenderCopy(*renderer, texture, &txtRect, &pasteRect);
    //window�Ƀ����_�����O����      
    SDL_RenderPresent(*renderer);
    SDL_DestroyTexture(texture);//�����g��Ȃ��̂ŏ���
    return 0;
}