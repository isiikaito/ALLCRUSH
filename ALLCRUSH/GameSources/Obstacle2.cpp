/**
*@file Obstacle2.cpp
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


	//!������
	void Obstacle2::OnCreate() {
		AddComponent<StaticModelComponent>(m_obstacleModelData);				//!���f���f�[�^����

	}

	void Obstacle2::OnUpdate()
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
				//!�A�C�e����j�󂷂�
				GetStage()->RemoveGameObject<Obstacle2>(GetThis<Obstacle2>());
			}

		}
	}

}