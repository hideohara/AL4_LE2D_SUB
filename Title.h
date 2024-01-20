#pragma once
#include "Sprite.h"
#include "Input.h"
#include <memory>

class Title {
public:
	// 初期化
	void Initialize(
	    Sprite* spriteTitle, Sprite* spriteKey, 
		uint32_t textureHandleTitle, uint32_t textureHandleKey);

	// 更新
	bool Update();

	// 描画
	void Draw();

private:
	Input* input_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandleTitle_ = 0;
	uint32_t textureHandleKey_ = 0;

	// スプライト
	Sprite* spriteTitle_;
	Sprite* spriteKey_;

	// タイマー
	int timer_ = 0;
};
