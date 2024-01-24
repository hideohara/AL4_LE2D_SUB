#pragma once
#include "Input.h"
#include "Sprite.h"
#include <memory>

class Fade {
public:
	// 初期化
	void Initialize(Sprite* spriteTitle, uint32_t textureHandle);

	// 更新
	void Update();

	// 描画
	void Draw();

	void StartFadeIn();
	void StartFadeOut();

	int GetMode() { return mode_; }

	bool IsEndFadeOut() { return endFadeOut_; }

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// スプライト
	Sprite* sprite_;

	// タイマー
	float timer_ = 1u;

	uint32_t mode_ = 0;

	bool endFadeOut_ = false;
};
