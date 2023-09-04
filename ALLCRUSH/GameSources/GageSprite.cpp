/*!
@file GageSprite.cpp
@brief ゲージの実体a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//ゲージ
	constexpr float HELFSIZE = 0.5f;//!ポリゴンサイズ
	constexpr float STARTSCALEZ = 1.0f;//!zの大きさ

	GageSprite::GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_BreakCount(2),
		m_PowerON(0),
		m_PowerOFF(1),
		firstScale(40.0f, 50.0f, 1.0f),
		firstpos(550.0f, -310.0f, 0.1f),
		secondScale(40.0f, 90.0f, 1.0f),
		secondpos(550.0f, -290.0f, 0.1f),
		treedScale(40.0f, 130.0f, 1.0f),
		treedpos(550.0f, -270.0f, 0.1f),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_gageTextureColor(Col4(1.0f, 0.0, 0.0f, 1.0f))

	{}

	GageSprite::~GageSprite() {}
	void GageSprite::OnCreate() {


		
		//頂点配列
		m_BackupVertices = 
		{
			                                                        
         { VertexPositionColor(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor) },
         { VertexPositionColor(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor) },
         { VertexPositionColor(Vec3(-HELFSIZE, -HELFSIZE, 0),m_TextureColor) },
         { VertexPositionColor(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
	    };
		//インデックス配列
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		
		//初期位置の設定
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

        //頂点とインデックスを指定してスプライト作成
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		SetAlphaActive(true);

		//頂点とインデックスを指定してスプライト作成
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);


		ptrDraw->SetDiffuse(m_gageTextureColor);

		SetDrawActive(false);
	}

	//点滅処理（Elapsedtimeを利用している）
	void GageSprite::OnUpdate() {

	//プレイヤーの取得
	auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
	auto PowerCount = ptrPlayer->GetPowerCount();
		//壁を殴った回数
		ptrPlayer->SetPowerCount(PowerCount);
		//パワーアップしているかどうか
		auto Power = ptrPlayer->GetPower();
		ptrPlayer->SetPower(Power);
		//アイテムを使ったかどうか
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		
		auto ptrTrans = GetComponent<Transform>();
		
		switch (PowerCount)
		{
		case first://!壁を一つ壊したら
			ptrTrans->SetScale(firstScale);
			ptrTrans->SetPosition(firstpos);
			SetDrawActive(true);
			break;
		case second:
			ptrTrans->SetScale(secondScale);
			ptrTrans->SetPosition(secondpos);
			break;
		case treed:
			ptrTrans->SetScale(treedScale);
			ptrTrans->SetPosition(treedpos);
			break;

		default:
			break;
		}
		



		//パワーアップした時
		if (Power == m_PowerON)
		{
			//点滅

			//時間の取得
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;
			if (m_TotalTime >= XM_PI) {
				m_TotalTime = 0;
			}
			//頂点の取得
			vector<VertexPositionColor> newVertices;
			for (size_t i = 0; i < m_BackupVertices.size(); i++) {
				Col4 col = m_BackupVertices[i].color;
				//sinで0～１までにして0の時は透明１の時は表示としている
				col.w = sin(m_TotalTime);
				auto v = VertexPositionColor(
					m_BackupVertices[i].position,
					col
				);
				newVertices.push_back(v);
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->UpdateVertices(newVertices);

		}
		//アイテムを使った後
		if (Gageflash == m_PowerOFF)
		{
			//ゲージを消す
			SetDrawActive(false);
			Gageflash = m_PowerON;
		}

	}

}
