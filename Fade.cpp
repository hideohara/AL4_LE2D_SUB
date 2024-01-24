#include "Fade.h"
#include "TextureManager.h"

void Fade::Initialize(Sprite* sprite, uint32_t textureHandle) {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = textureHandle;

	// スプライトの生成
	sprite_ = sprite;
}

void Fade::Update() {
	// fadein
	if (mode_ == 1) {
		timer_ -= 0.01f;
		if (timer_ <= 0) {
			timer_ = 0;
		}
	}
	// fadeout
	if (mode_ == 2) {
		timer_ += 0.01f;
		if (timer_ >= 1) {
			timer_ = 1;
			endFadeOut_ = true;
		}
	}

	sprite_->SetColor({1, 1, 1, timer_});
}

void Fade::Draw() { sprite_->Draw(); }

void Fade::StartFadeIn() {
	timer_ = 1.0f;
	mode_ = 1;
	endFadeOut_ = false;
}

void Fade::StartFadeOut() {
	if (mode_ != 2) {
		timer_ = 0;
		mode_ = 2;
		endFadeOut_ = false;
	}
}
