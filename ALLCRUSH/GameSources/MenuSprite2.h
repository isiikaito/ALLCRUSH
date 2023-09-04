/*!
@file MenuSprite2.h
*@author Kaito Isii
@brief 文字
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	class MenuSprite2 : public GameObject {
		bool m_Trace;         //透明
		Vec2 m_StartScale;    //大きさ
		Vec3 m_StartPos;      //位置
		wstring m_TextureKey; //テクスチャ
		float m_idleTime;     //時間の取得


		//バックアップ頂点データ
		vector< VertexPositionColorTexture> m_BackupVertices;
	public:

		MenuSprite2(const shared_ptr<Stage>& StagePtr, const wstring& TextureKey, bool Trace,
			const Vec2& StartScale, const Vec3& StartPos);

		virtual ~MenuSprite2();

		virtual void OnCreate() override;



	};
}

