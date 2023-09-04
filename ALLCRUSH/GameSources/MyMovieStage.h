/*!
@file MyMovieStage.h
@brief 
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ムービーステージクラス
	//--------------------------------------------------------------------------------------
	class MyMovieStage : public MovieStage {
		InputHandler<MyMovieStage> m_InputHandler;		//入力ハンドラー
		ResetHandler<MyMovieStage> ResetHandler;	   //リセットハンドラー
		void MovieSkip();
		float MovieTime;
		float m_Time;
	public:
		//構築と破棄
		MyMovieStage() :MovieStage(),
		MovieTime(43.6f),
		m_Time(0.0f){}
		//デストラクタ
		virtual ~MyMovieStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate() override;
		//リセット
		void OnPushReset(){}
		//動画のスキップ
		void OnPushSkip();
	};
}
//end namespace basecross
