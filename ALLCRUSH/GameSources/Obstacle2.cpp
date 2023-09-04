/**
*@file Obstacle2.cpp
*@brief 障害物オブジェクトが実装されているソースファイル
*@author Kaito Isii
*@details 障害物オブジェクトの実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	constexpr float MAXPLAYERDISTANCE = 3.0f;//!プレイヤーとの距離
	//!パラメータの初期化
	Obstacle2::Obstacle2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_obstacleModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.045f, 1.0f, 0.13f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),	  
				Vec3(0.0f, 0.0f, -0.05f),  
				L"OBSTACLE2_MESH"
			}
		)
	{}


	//!初期化
	void Obstacle2::OnCreate() {
		AddComponent<StaticModelComponent>(m_obstacleModelData);				//!モデルデータ生成

	}

	void Obstacle2::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerAttack = player->GetPlayerAttack();
		if (playerAttack)
		{
			auto playerpos = player->GetComponent<Transform>()->GetPosition();
			auto obstaclepos = GetComponent<Transform>()->GetPosition();
			auto playerdistance = bsm::length(obstaclepos - playerpos);//プレイヤーとの距離

			if (playerdistance <= MAXPLAYERDISTANCE)
			{
				//!アイテムを破壊する
				GetStage()->RemoveGameObject<Obstacle2>(GetThis<Obstacle2>());
			}

		}
	}

}