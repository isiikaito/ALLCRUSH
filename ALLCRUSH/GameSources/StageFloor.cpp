/**
*@file StageFloor.cpp
*@brief ステージの床実体が実装されているソースファイル
*@author Kaito Isii
*@details ステージの床実体の実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	StageFloor::StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_floorModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.045f, 1.0f, 0.13f),
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   
				Vec3(0.0f, 0.0f, -0.05f),  
				L"STAGEFLOOR_MESH"

			}
		)

	{}

	void StageFloor::OnCreate()
	{
		AddComponent<StaticModelComponent>(m_floorModelData);//!モデルデータ生成

	}

}