/*!
@file GageSprite.cpp
@brief ゲージの実体a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float HELFSIZE = 0.5f;//!ポリゴンサイズ
	constexpr float STARTSCALEZ = 1.0f;//!zの大きさ

	//ゲージ

	GageSpriteWhite::GageSpriteWhite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f))
	{}

	GageSpriteWhite::~GageSpriteWhite() {}
	void GageSpriteWhite::OnCreate() {
		//頂点配列
		m_BackupVertices = {
			//カラー　透明度
           { VertexPositionColor(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor) },
           { VertexPositionColor(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor) },
           { VertexPositionColor(Vec3(-HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
           { VertexPositionColor(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//透明処理
		SetAlphaActive(m_Trace);
		//初期化
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
	}
}