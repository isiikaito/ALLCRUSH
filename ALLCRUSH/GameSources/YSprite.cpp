/*!
@file YSprite.cpp
@brief　パワーボタン
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float HELFSIZE = 0.5f;//!ポリゴンサイズ
	constexpr int POWERMAX = 3;//!ゲージの最大
	constexpr int GAGEFLASHTRUE = 1;//!ゲージの点滅
	constexpr float STARTSCALEZ = 1.0f;//!zの大きさ
	YSprite::YSprite(const shared_ptr<Stage>& StagePtr,
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

	YSprite::~YSprite() {}
	void YSprite::OnCreate() {
		//頂点配列
		m_BackupVertices={
			{ VertexPositionTexture(Vec3(-HELFSIZE, HELFSIZE, 0),m_LeftUpperSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, HELFSIZE, 0), m_RightUpperSummit) },
			{ VertexPositionTexture(Vec3(-HELFSIZE, -HELFSIZE, 0), m_LeftLowerSummit) },
			{ VertexPositionTexture(Vec3(HELFSIZE, -HELFSIZE, 0),m_RightLowerSummit) },
		};
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		//透明処理
		SetAlphaActive(m_Trace);

		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

		//頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PTSpriteDraw>(m_BackupVertices, indices);
		ptrDraw->SetSamplerState(SamplerState::LinearWrap);

		//テクスチャの読み込み
		ptrDraw->SetTextureResource(m_TextureKey);

		//テクスチャの表示をしない
		SetDrawActive(false);

		//読み込みの設定をする
		GetStage()->SetSharedGameObject(L"YSprite", GetThis<YSprite>());
	}

	void YSprite::OnUpdate() 
	{
		//プレイヤーの取得
		auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");

		//壁を壊した回数
		auto PowerCount = ptrPlayer->GetPowerCount();
		ptrPlayer->SetPowerCount(PowerCount);

		//使い終わってるかどうか
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		if (PowerCount == POWERMAX)
		{
			//テクスチャを表示する
			SetDrawActive(true);
		}
		//ゲージを使い終わったら
		if (Gageflash == GAGEFLASHTRUE)
		{
			//テクスチャの表示をしない
			SetDrawActive(false);
			Gageflash = 0;
		}
	}
}