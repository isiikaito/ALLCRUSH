/*!
@file Wall.cpp
@brief カベの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	Wall::Wall(const shared_ptr<Stage>& StagePtr,
		const Vec3& Scale,
		const Vec3& Rotation,
		const Vec3& Position,
		const int HP

	) :
		GameObject(StagePtr),
		m_HP(HP),
		m_wallModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.3f, 0.095f, 0.09f),
				Vec3(0.0f, 5.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),   
				Vec3(-0.4f, -0.7f, 0.0f), 
				L"UNBREAKWALL_MESH"
			}
		),
		m_playerPos(0.0f),
		m_cameraPos(0.0f),
		modelScale(0.3f, 0.095f, 0.09f),
		modelRotOrigin(0.0f, 5.0f, 0.0f),
		modelRotation(0.0f, 0.0f, 0.0f),
		modelPosition(-0.4f, -0.7f, 0.0f)
	{}
	

	void Wall::OnCreate() {
		AddComponent<StaticModelComponent>(m_wallModelData);	//!モデルデータ生成
		//オブジェクトのグループを得る
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");

		//グループに自分自身を追加
		group->IntoGroup(GetThis<Wall>());
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_palyerTransform = player->GetComponent<Transform>();
		m_wallModelDraw = GetComponent<PNTStaticModelDraw>();
	}

	void Wall::OnUpdate()
	{
		m_InputHandler.PushHandle(GetThis<Wall>());
		auto player=GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerTrans = m_palyerTransform.lock();
		m_playerPos = playerTrans->GetPosition();
		//カメラの座標を取得する
		m_cameraPos = player->OnGetDrawCamera()->GetEye();
			
		
		// カメラの座標がプレイヤーよりも後ろなら、
		if (m_cameraPos.x > m_playerPos.x){
			//壁の描画の表示
			SetDrawActive(true);
		}
		else {
			//壁の描画の非表示
			SetDrawActive(false);
		}
		
		
		//壁の残り耐久値についての処理
		
		switch (m_HP)
		{
		case 0:
			GetStage()->RemoveGameObject<Wall>(GetThis<Wall>());
			break;
		case 1:
			WallChangeMesh(L"DAMAGEWALL3_MESH");
			
			break;

		case 2:
			WallChangeMesh(L"DAMAGEWALL2_MESH");

			
			break;
		case 3:
			WallChangeMesh(L"DAMAGEWALL1_MESH");

			break;
		case 4:
			WallChangeMesh(L"UNBREAKWALL_MESH");
			break;

		}
		


	}
	void Wall::WallChangeMesh(wstring meshName)
	{
		auto ptrDraw = m_wallModelDraw.lock();
		Mat4x4 spanMat; // モデルとトランスフォームの間の差分行列
		spanMat.affineTransformation(
			modelScale,
			modelRotOrigin,
			modelRotation,
			modelPosition
		);
		ptrDraw->SetMeshResource(meshName);
		ptrDraw->SetMeshToTransformMatrix(spanMat);
	}
}
//end basecross
