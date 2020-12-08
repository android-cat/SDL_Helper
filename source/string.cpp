#include"main.h"
#ifdef _WIN32
std::string SjistoUTF8(std::string Sjis)//Change UTF8
{
	//UTF16へ変換後の文字列長を得る
	int lenghtUTF16 = MultiByteToWideChar(CP_THREAD_ACP, 0, Sjis.c_str(), Sjis.size() + 1, NULL, 0);

	//必要な分だけUnicode文字列のバッファを確保
	wchar_t* bufUnicode = new wchar_t[lenghtUTF16];

	//ShiftJISからUnicodeへ変換
	MultiByteToWideChar(CP_THREAD_ACP, 0, Sjis.c_str(),Sjis.size() + 1, bufUnicode, lenghtUTF16);

	//UTF8へ変換後の文字列長を得る
	int lengthUTF8 = WideCharToMultiByte(CP_UTF8, 0, bufUnicode, -1, NULL, 0, NULL, NULL);

	//必要な分だけUTF8文字列のバッファを確保
	char* bufUTF8 = new char[lengthUTF8];

	//UnicodeからUTF8へ変換
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

    //文字を描写したTextureのサイズを取得する      
    int text_x,text_y;
    SDL_QueryTexture(texture, NULL, NULL, &text_x, &text_y);
    SDL_Rect txtRect = { 0,0,text_x,text_y};
    SDL_Rect pasteRect = {x,y,text_x,text_y};

    //Textureを描写する            
    SDL_RenderCopy(*renderer, texture, &txtRect, &pasteRect);
    //windowにレンダリングする      
    SDL_RenderPresent(*renderer);
    SDL_DestroyTexture(texture);//もう使わないので消す
    return 0;
}