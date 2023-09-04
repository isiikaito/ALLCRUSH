/*!
@file Myitem1.h
@brief アイテム
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class Myitem1 : public GameObject {
		bool m_Trace;        //透明
		Vec2 m_StartScale;   //大きさ
		Vec3 m_StartPos;     //位置
		wstring m_TextureKey;//テクスチャ
		float m_TotalTime;   //時間
		vector<VertexPositionTexture> m_BackupVertices;	//バックアップ頂点データ
		const Vec2 m_LeftUpperSummit;	//!左上の頂点
		const Vec2 m_LeftLowerSummit;	//!左下の頂点
		const Vec2 m_RightUpperSummit;	//!右上の頂点
		const Vec2 m_RightLowerSummit;	//!右下の頂点
	public:
		
		Myitem1(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);
		//デストラクタ
		virtual ~Myitem1();
		//初期化
		virtual void OnCreate() override;
		
	};
}
