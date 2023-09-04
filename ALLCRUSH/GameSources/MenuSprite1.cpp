/*!
@file memuSprite.cpp
@brief 文字テクスチャ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float HELFSIZE = 0.5f;//!ポリゴンサイズ

	MenuSprite1::MenuSprite1(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_idleTime(0)
	
		
	{}

	MenuSprite1::~MenuSprite1() {}
	void MenuSprite1::OnCreate() {


		//頂点配列(縦横5個ずつ表示)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, HELFSIZE, 0),Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, HELFSIZE, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 0.0f)) },
			{ VertexPositionColorTexture(Vec3(-HELFSIZE, -HELFSIZE, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(0.0f, 1.0f)) },
			{ VertexPositionColorTexture(Vec3(HELFSIZE, -HELFSIZE, 0), Col4(1.0f,1.0f,1.0f,1.0f), Vec2(1.0f, 1.0f)) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, 1.0f);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);
		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);
		//テクスチャの設定
		ptrDraw->SetTextureResource(m_TextureKey);

		//読み込みの設定をする
		GetStage()->SetSharedGameObject(L"MenuSprite1", GetThis<MenuSprite1>());
	}
	

	
}