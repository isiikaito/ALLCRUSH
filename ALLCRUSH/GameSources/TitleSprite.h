/*!
@file TitleStage.h
@brief タイトルスプライト
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	タイトルスプライトクラス
	//--------------------------------------------------------------------------------------
	class TitleSprite : public GameObject {
		bool m_Trace;//透明になるかどうか
		Vec2 m_StartScale;//スケーリング
		Vec2 m_StartPos;//場所
		wstring m_TextureKey;//テクスチャの名前
	public:
		TitleSprite(const shared_ptr<Stage>& StagePtr,
					const wstring& TextureKey,
					bool Trace,
					const Vec2& StartScale,
					const Vec2& StartPos);
		//破壊
		virtual ~TitleSprite();
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross