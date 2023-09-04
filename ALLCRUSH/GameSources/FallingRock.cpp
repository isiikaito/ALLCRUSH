/**
*@file FallingRock.cpp
*@brief落石実体が実装されているソースファイル
*@author Kaito Isii
*@details 落石実体の実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	FallingRock::FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_Falling(false),
		m_fallingRockModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.2f, 0.2f, 0.2f),
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, -0.5f, 0.5f),
				L"IWA_MESH"
			}
		)
	{}


	
	void FallingRock::OnCreate() {
		AddComponent<StaticModelComponent>(m_fallingRockModelData);	//!モデルデータ生成

		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");  //!オブジェクトのグループを得る
        group3->IntoGroup(GetThis < FallingRock > ());                          //!グループに自分自身を追加
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());//!読み込みの設定をする		
	}

	void FallingRock::OnUpdate()
	{
		//!柱が壊れたら
		if (m_Falling)
		{
			auto ptrGra = AddComponent<Gravity>();//!重力をつける
		}
	}
}