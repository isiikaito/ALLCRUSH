/*!
@file GameOverSprite.h
@brief ゲームオーバースプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	ゲームオーバースプライトクラス
	//--------------------------------------------------------------------------------------
	class GameOverSprite : public GameObject {
		bool m_Trace;					//透明になるかどうか
		Vec2 m_StartScale;				//スケーリング
		Vec3 m_StartPos;				//場所
		wstring m_TextureKey;			//テクスチャの名前
		const Vec2 m_LeftUpperSummit;	//!左上の頂点
		const Vec2 m_LeftLowerSummit;	//!左下の頂点
		const Vec2 m_RightUpperSummit;	//!右上の頂点
		const Vec2 m_RightLowerSummit;	//!右下の頂点
		Col4 m_TextureColor;			//!テクスチャの色
	public:
		GameOverSprite(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos);
		//破壊
		virtual ~GameOverSprite();
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross
