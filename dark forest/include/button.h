#ifndef BUTTON_H
#define BUTTON_H
#include"texture.h"
enum ButtonState {
	MOUSE_OUT,
	MOUSE_IN,
	MOUSE_DOWN
};
class Button {
	int posX, posY, currentSprite;
	Texture buttonTexture;
public:
	Button() {
		posX = posY = 0;
		currentSprite = MOUSE_OUT;
	}
	void setPosition(int x, int y) {
		posX = x;
		posY = y;
	}
	void handleEvent(SDL_Event* e) {
		if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN) {
			int x, y;
			SDL_GetMouseState(&x, &y);
			if(x < posX || x > posX + buttonTexture.textureWidth() || y < posY || y > posY + buttonTexture.textureHeight()) currentSprite = MOUSE_OUT;
			else switch(e->type) {
				case SDL_MOUSEMOTION: currentSprite = MOUSE_IN; return;
				case SDL_MOUSEBUTTONDOWN: currentSprite = MOUSE_DOWN; return;
			}
		}
	}
	void textureFromFile(std::string path, Uint8 r = 1, Uint8 g = 1, Uint8 b = 1) {
		buttonTexture.loadTextureFromFile(path, r, g, b);
	}
	void textureFromText(std::string text, TTF_Font* font, SDL_Color color = {255,255,255}) {
		buttonTexture.loadTextureFromText(text, font, color);
	}
	void setButtonSize(int w, int h) {
		buttonTexture.setTextureSize(w, h);
	}
	void setButtonColor(Uint8 r, Uint8 g, Uint8 b) {
		buttonTexture.setTextureColor(r, g, b);
	}
	void renderButton(SDL_Rect* clip = nullptr) {
		buttonTexture.renderTexture(posX, posY, clip);
	}
	int getCurrentState() {
		return currentSprite;
	}
	int buttonWidth() {
		return buttonTexture.textureWidth();
	}
	int buttonHeight() {
		return buttonTexture.textureHeight();
	}
	void reset() {
		currentSprite = MOUSE_OUT;
		setButtonColor(255, 255, 255);
	}
	void free() {
		buttonTexture.free();
	}
};

//shared items
Button back;

//menu
Button play, setting, high_score;

//game play
Button easy_mode, normal_mode, hard_mode;
Button pause_game, resume_game, exit_game;

//setting
std::vector<Button> volume_bar(2);

//high score
Button resetScore;
#endif // !BUTTON_H
