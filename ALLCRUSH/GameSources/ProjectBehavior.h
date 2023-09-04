/*!
@file ProjectBehavior.h
@brief プロジェク定義の行動クラス
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	///	コントローラのボタンのハンドラ
	//--------------------------------------------------------------------------------------
	template<typename T>
	struct InputHandler {
		void PushHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Aボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_A) {
					Obj->OnPushA();
				}			
			}
		}
	};

	template<typename T>
	struct InputHandler2 {
		void PushHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//Bボタン
				if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_B) {
					Obj->OnPushB();
				}
				//Xボタン
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_X) {
					Obj->OnPushX();
				}
				 //Yボタン
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_Y) {
					 Obj->OnPushY();
				 }
				 //十字キーの上
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
					Obj->OnPushUP();
				}
				 //十字キーの下
				 if (cntlVec[0].wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
					 Obj->OnPushDOWN();
				 }
			}
		}
	};

	template<typename T>
	struct ResetHandler {
		void ResetHandle(const shared_ptr<T>& Obj) {
			//コントローラの取得
			auto cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
			if (cntlVec[0].bConnected) {
				//リセットコマンド
				if ((cntlVec[0].wButtons & XINPUT_GAMEPAD_START) && (cntlVec[0].wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					&&(cntlVec[0].wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER))
				{
					Obj->OnPushReset();
				}
				//スキップコマンド
				if (cntlVec[0].wButtons & XINPUT_GAMEPAD_START) {
					Obj->OnPushSkip();
				}
			}
		}
	};
}

//end basecross