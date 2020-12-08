#include"main.h"

int LoadImage(SDL_Surface** image, const char* filename) {//
	//画像読み込み部
	*image = IMG_Load(filename);// sample.pngをimageに読み込む
	if (*image == NULL) {//画像が読み込めなかった時
		SDL_UnlockSurface(*image);//画像データを捨てる処理
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}
	return 0;
}

int DrawPicture(SDL_Renderer** renderer, SDL_Surface* image, int x, int y) {
	SDL_Texture* image_texture = NULL;//画像を使うためのデータ用
	image_texture = SDL_CreateTextureFromSurface(*renderer, image);
	if (image_texture == NULL) {//テクスチャが作成できていなかったとき
		SDL_UnlockSurface(image);//画像データを捨てる処理
		SDL_DestroyTexture(image_texture);//画像を使う為のデータを削除する
		SDL_DestroyRenderer(*renderer);//ウィンドウの描画するための情報を削除する
		IMG_Quit();//SDL_IMageを終了する処理
		SDL_Quit();//SDLを終了する処理
		return 1;//プログラムにエラーだから終了すると伝える
	}

	int image_x, image_y;//画像の大きさを保存するための変数
	SDL_QueryTexture(image_texture, NULL, NULL, &image_x, &image_y);//テクスチャ(画像)の大きさを知る関数
	SDL_Rect imageRect = { 0,0,image_x,image_y };//画像の標準の大きさの指定
	SDL_Rect drawRect = { x,y,image_x,image_y};//画像を描画する時の場所の指定

	SDL_RenderCopy(*renderer, image_texture, &imageRect, &drawRect);//画像をウィンドウに描画するための情報の描画部分に送る
	SDL_RenderPresent(*renderer);//ここで描画！
	SDL_DestroyTexture(image_texture);//もう使わないので消す
	return 0;
}

void CleanScreen(SDL_Renderer** renderer) {//Screen change all black
	SDL_SetRenderDrawColor(*renderer, 0, 0, 0, 0);//指定のカラーで画面を塗る設定をする
	SDL_RenderClear(*renderer);//実際にぬる
	SDL_RenderPresent(*renderer);//ここで描画！
}