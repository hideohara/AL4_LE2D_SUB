#include "Title.h"
#include "TextureManager.h"

void Title::Initialize(
    Sprite* spriteTitle, Sprite* spriteKey, uint32_t textureHandleTitle,
    uint32_t textureHandleKey) {

	// ファイル名を指定してテクスチャを読み込む
	textureHandleTitle_ = textureHandleTitle;
	textureHandleKey_ = textureHandleKey;

	// スプライトの生成
	spriteTitle_ = spriteTitle;
	spriteKey_ = spriteKey;
}

bool Title::Update() {

	// spriteKey_->SetColor({1, 1, 1, 0.2f});
	timer_++;
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		return true;
	}
	return false;
}

void Title::Draw() {
	spriteTitle_->Draw();
	if (timer_ % 40 < 20) {
		spriteKey_->Draw();
	}
}
