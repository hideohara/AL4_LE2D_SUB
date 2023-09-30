#include "FollowCamera.h"
#include "MathUtilityForText.h"
#include "Input.h"

void FollowCamera::Initialize() {
	viewProjection_.farZ = 2000.0f;
	viewProjection_.Initialize();
}

void FollowCamera::Update() {

	// 回転
	// if (Input::GetInstance()->GetJoystickState(0, joyState)) {

	//	const float speed = 0.03f;

	//	viewProjection_.rotation_.y += (float)joyState.Gamepad.sThumbRX / SHRT_MAX * speed;
	//}

	if (Input::GetInstance()->PushKey(DIK_SPACE)) {
		viewProjection_.rotation_.y += 0.03f;
	}

	// 追従対象がいれば
	if (target_) {
		// 追従対象からカメラまでのオフセット
		Vector3 offset = {0.0f, 2.0f, -10.0f};

		// 座標をコピーしてオフセット分ずらす
		viewProjection_.translation_ = target_->translation_ + offset;
	}

	// ビュー行列の更新
	viewProjection_.UpdateViewMatrix();
}
