/**
*@file StageWall.cpp
*@brief出口の壁の実体が実装されているソースファイル
*@author Kaito Isii
*@details 出口の壁の実体の実装
*/

#include "stdafx.h"
#include "Project.h"

/** basecross共通のネームスペース */
namespace basecross {
	//!パラメータの初期化
	ExitWall::ExitWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_exitWallModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(1.0f, 0.15f, 0.08),
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f), 
				Vec3(0.0f, -0.8f, 0.0f),
				L"EXITWALL_MESH"
			}
		)
	{}


	
	void ExitWall::OnCreate() 
	{
		AddComponent<StaticModelComponent>(m_exitWallModelData);	//!モデルデータ生成

	}

}