/**
*@file Pillar.cpp
*@brief 柱オブジェクトが実装されているソースファイル
*@author Kaito Isii
*@details 柱オブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"
#include "Player.h"
/** basecross共通のネームスペース */
namespace basecross {
	constexpr float MAXPLAYERDISTANCE = 5.0f;//!プレイヤーとの距離
	//!パラメータの初期化
	Pillar::Pillar(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Scale(Scale),
		m_Rotation(Rotation),
		m_Position(Position),
		m_pillarModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.5f, 0.5f, 0.5f),  
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),  
				Vec3(-0.4f, -0.5f, -0.6f),
				L"PILLAR_MESH"
			}
		)
	{}


	void Pillar::OnCreate() {
		AddComponent<StaticModelComponent>(m_pillarModelData);				//!モデルデータ生成
		GetStage()->SetSharedGameObject(L"Pillar", GetThis<Pillar>());   //!SetSharedGameObjectへ読み込みの設定をする

	}

	void Pillar::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerAttack = player->GetPlayerAttack();
		if (playerAttack)
		{
			auto playerpos = player->GetComponent<Transform>()->GetPosition();//プレイヤーの位置
			auto pillarpos = GetComponent<Transform>()->GetPosition();//柱の位置
			auto playerdistance = bsm::length(pillarpos - playerpos);//プレイヤーとの距離

			if (playerdistance<= MAXPLAYERDISTANCE)
			{
				auto ptrFallingRock = GetStage()->GetSharedGameObject<FallingRock>(L"FallingRock");
				ptrFallingRock->SetFalling(true);
				//!柱を破壊する
				GetStage()->RemoveGameObject<Pillar>(GetThis<Pillar>());
			}

		}
	}

}