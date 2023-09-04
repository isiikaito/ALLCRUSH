/*!
@file Mygage.cpp
@brief ゲージ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float HELFSIZE = 0.5f;		//!ポリゴンサイズ
	constexpr float STARTSCALEZ = 1.0f;	//!z方向の大きさ

	Mygage::Mygage(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f))

	{}

	Mygage::~Mygage() {}
	void Mygage::OnCreate() {
		//頂点配列
		m_BackupVertices = {
			{ VertexPositionTexture(Vec3(-HELFSIZE, HELFSIZE, 0),m_LeftUpperSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, HELFSIZE, 0),  m_RightUpperSummit) },
			{ VertexPositionTexture(Vec3(-HELFSIZE, -HELFSIZE, 0),m_LeftLowerSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, -HELFSIZE, 0), m_RightLowerSummit) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		//透明処理
		SetAlphaActive(m_Trace);
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetPosition(m_StartPos);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//テクスチャの読み込み
		ptrDraw->SetTextureResource(m_TextureKey);
	}
}
