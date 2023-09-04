/**
*@file Obstacle1.cpp
*@brief ��Q���I�u�W�F�N�g����������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details ��Q���I�u�W�F�N�g�̎���
*/
#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	constexpr float MAXPLAYERDISTANCE = 3.0f;//!�v���C���[�Ƃ̋���
	//!�p�����[�^�̏�����
	Obstacle1::Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position) :
		GameObject(StagePtr),
		m_obstacleModelData
		(
			{
				Scale ,
				Rotation ,
				Position,
				Vec3(0.5f, 0.5f, 0.5f),  
				Vec3(0.0f, 0.0f, 0.0f),
				Vec3(0.0f, 0.0f, 0.0f),  
				Vec3(-0.4f, -0.5f, -0.6f),
				L"OBSTACLE1_MESH"
			}
		)
	{}


	
	void Obstacle1::OnCreate() 
	{
		AddComponent<StaticModelComponent>(m_obstacleModelData);//!���f���f�[�^����

	}

	void Obstacle1::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerAttack = player->GetPlayerAttack();
		if (playerAttack)
		{
			auto playerpos = player->GetComponent<Transform>()->GetPosition();
			auto obstaclepos = GetComponent<Transform>()->GetPosition();
			auto playerdistance = bsm::length(obstaclepos - playerpos);//�v���C���[�Ƃ̋���

			if (playerdistance <= MAXPLAYERDISTANCE)
			{
				auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
				Shitem->SetDrawActive(true);
				auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
				XSprite1->SetDrawActive(true);
				player->SetItemCondition(true);
				//!�N���X�^����j�󂷂�
				GetStage()->RemoveGameObject<Obstacle1>(GetThis<Obstacle1>());
			}

		}
	}

}