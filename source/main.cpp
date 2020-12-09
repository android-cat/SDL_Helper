#include"main.h"
#define SCREEN_X 1280//SCREEN_Xと打つと1280が入力されるようにする
#define SCREEN_Y 720//SCREEN_Yと打つと720が入力されるようにする
int Init(SDL_Window **window,SDL_Renderer**renderer,TTF_Font **font) {//Initialize
	if (SDL_Init(SDL_INIT_AUDIO) == -1 || SDL_Init(SDL_INIT_VIDEO)==-1||IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)==-1||TTF_Init()==-1||Mix_Init(MIX_INIT_MP3)) {//初期化
		TTF_Quit();
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}
	*window = SDL_CreateWindow("TestWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_X, SCREEN_Y, 0);//ウィンドウ作成
	if (*window == NULL) {//ウィンドウが作成できていなかったとき
		SDL_DestroyWindow(*window);//ウィンドウを捨てる処理
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}
	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED||SDL_RENDERER_PRESENTVSYNC);
	if (*renderer == NULL) {//レンダーが作成できていなかったとき
		SDL_DestroyRenderer(*renderer);//ウィンドウの描画するための情報を削除する
		SDL_DestroyWindow(*window);//ウィンドウを捨てる処理
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		Mix_CloseAudio();
		SDL_DestroyRenderer(*renderer);//ウィンドウの描画するための情報を削除する
		SDL_DestroyWindow(*window);//ウィンドウを捨てる処理
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return -1; 
	}
	*font = TTF_OpenFont(FONT_PATH, 40);
	if (*font == NULL) {
		Mix_CloseAudio();
		SDL_DestroyRenderer(*renderer);//ウィンドウの描画するための情報を削除する
		SDL_DestroyWindow(*window);//ウィンドウを捨てる処理
		TTF_Quit();
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}
	return 0;
}

void Quit() {//Exit programs
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();//SDL_IMageを終了する処理
	SDL_Quit();//SDLを終了する処理
}


/*int main(int argc, char** argv) {//Sample
	SDL_Surface* image=NULL;//画像を入れる用
	SDL_Surface* image2 = NULL;
	Mix_Music* music;
	SDL_Window* window=NULL;//ウィンドウの情報入れる用
	SDL_Renderer* renderer=NULL;//ウィンドウを使う為のデータ用
	SDL_Event event;
	TTF_Font* font=NULL;
	bool breakflag = false;
	//初期化部
	if (Init(&window,&renderer,&font))return 1;//プログラムにエラーだから終了すると伝える

	//画像読み込む部
	if (LoadImage(&image, "Resource/"))return 1;//プログラムにエラーだから終了すると伝える
	if (LoadImage(&image2, "Resource/"))return 1;//プログラムにエラーだから終了すると伝える
	if(LoadSound(&music,"Resource/"))return 1;
	//描画部
	while (1) {
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) {
				breakflag = true;
				break;
		}
		if (breakflag)break;
		CleanScreen(&renderer);
		SDL_Delay(20);//20ミリ秒待つと伝える
		DrawPicture(&renderer, image, 0, 0);
		SDL_Delay(20);//20ミリ秒待つと伝える
		CleanScreen(&renderer);
		SDL_Delay(20);
		DrawPicture(&renderer, image2,300,300);
		SDL_Delay(20);
		CleanScreen(&renderer);
		SDL_Delay(20);
		DrawString(&renderer,font,"学級うんちunti",100, 100);
		playSound(&music,NORMAL);
		SDL_Delay(20);
		//わかりやすいように20ミリ秒置いているが、自動でモニターのリフレッシュレートと同期する
	}
	//終了処理
	SDL_UnlockSurface(image);//画像データを捨てる処理
	SDL_DestroyRenderer(renderer);//ウィンドウの描画するための情報を削除する
	SDL_DestroyWindow(window);//ウィンドウを削除する
	TTF_CloseFont(font);
	Quit();
	return 0;//プログラムに終わりだから終了すると伝える
}*/
