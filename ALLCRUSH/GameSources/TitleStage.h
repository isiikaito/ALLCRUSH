/*!
@file TitleStage.h
@brief タイトルステージ
*@author Kaito Isii
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルステージクラス
	//--------------------------------------------------------------------------------------
	class TitleStage : public Stage {
		//ビューの作成
		void CreateViewLight();
	
		bool  OnPushBCheck; //Bボタンの判定1
		bool  OnPushBCheck1;//Bボタンの判定2
		bool m_OnPushB;     //Bボタンが押されたかどうか
		//入力ハンドラー
		InputHandler2<TitleStage> m_InputHandler;

	public:
		//構築と破棄
		TitleStage() :Stage(),
			OnPushBCheck(false),
			OnPushBCheck1(false),
			m_OnPushB(true)
		{}
		virtual ~TitleStage() {}


		virtual void OnCreate()override;//初期化
		virtual void OnUpdate()override;//更新
		//入力イベントに応答する関数
		void OnPushX() {}               //コントローラーのボタン判定X
		void OnPushUP() {}              //コントローラーのボタン判定十字キー上
		void OnPushDOWN(){}             //コントローラーのボタン判定十字キー下
		void OnPushY() {}               //コントローラーのボタン判定Y
		void OnPushB();                 //コントローラーのボタン判定B
	};
}
//end namespace basecross
