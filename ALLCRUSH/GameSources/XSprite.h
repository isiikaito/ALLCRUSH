/*!
@file XSprite.h
@brief アイテムボタン
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class XSprite : public GameObject {
		bool m_Trace;        //透明
		Vec2 m_StartScale;   //大きさ
		Vec3 m_StartPos;     //位置
		wstring m_TextureKey;//テクスチャ
		float m_TotalTime;   //時間の取得
		vector<VertexPositionTexture> m_BackupVertices;//バックアップ頂点データ
		const Vec2 m_LeftUpperSummit;	//!左上の頂点
		const Vec2 m_LeftLowerSummit;	//!左下の頂点
		const Vec2 m_RightUpperSummit;	//!右上の頂点
		const Vec2 m_RightLowerSummit;	//!右下の頂点
	public:

		XSprite(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//デストラクタ
		virtual ~XSprite();
		//初期化
		virtual void OnCreate() override;

	};
}
