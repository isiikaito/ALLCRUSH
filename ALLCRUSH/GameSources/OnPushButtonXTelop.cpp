/*!
@file OnPushButtonXTelop.cpp
@brief ゲームオーバースプライト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float STARTSCALEZ = 1.0f;//!zの大きさ

	
	PushButtonXTelop::PushButtonXTelop(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey,
		bool Trace,
		const Vec2& StartScale,
		const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f))
	{}

	PushButtonXTelop::~PushButtonXTelop() {}
	void PushButtonXTelop::OnCreate() {
		float HelfSize = 0.5f;
		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0),m_TextureColor, m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), m_TextureColor, m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),m_TextureColor, m_RightLowerSummit) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		//透明処理
		SetAlphaActive(m_Trace);

		//初期位置の設定
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//頂点とインデックスを指定してスプライト作成
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//テクスチャの読み込み
		PtrDraw->SetTextureResource(m_TextureKey);
	}
}
