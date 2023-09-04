/**
*@file Pillar.cpp
*@brief ���I�u�W�F�N�g����������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details ���I�u�W�F�N�g�̎���
*/

#include "stdafx.h"
#include "Project.h"
#include "Player.h"
/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	constexpr float MAXPLAYERDISTANCE = 5.0f;//!�v���C���[�Ƃ̋���
	//!�p�����[�^�̏�����
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
		AddComponent<StaticModelComponent>(m_pillarModelData);				//!���f���f�[�^����
		GetStage()->SetSharedGameObject(L"Pillar", GetThis<Pillar>());   //!SetSharedGameObject�֓ǂݍ��݂̐ݒ������

	}

	void Pillar::OnUpdate()
	{
		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerAttack = player->GetPlayerAttack();
		if (playerAttack)
		{
			auto playerpos = player->GetComponent<Transform>()->GetPosition();//�v���C���[�̈ʒu
			auto pillarpos = GetComponent<Transform>()->GetPosition();//���̈ʒu
			auto playerdistance = bsm::length(pillarpos - playerpos);//�v���C���[�Ƃ̋���

			if (playerdistance<= MAXPLAYERDISTANCE)
			{
				auto ptrFallingRock = GetStage()->GetSharedGameObject<FallingRock>(L"FallingRock");
				ptrFallingRock->SetFalling(true);
				//!����j�󂷂�
				GetStage()->RemoveGameObject<Pillar>(GetThis<Pillar>());
			}

		}
	}

}