/**
*@file FallingRock.cpp
*@brief���Ύ��̂���������Ă���\�[�X�t�@�C��
*@author Kaito Isii
*@details ���Ύ��̂̎���
*/

#include "stdafx.h"
#include "Project.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {
	//!�p�����[�^�̏�����
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
		AddComponent<StaticModelComponent>(m_fallingRockModelData);	//!���f���f�[�^����

		auto group3 = GetStage()->GetSharedObjectGroup(L"FallingRock_Group1");  //!�I�u�W�F�N�g�̃O���[�v�𓾂�
        group3->IntoGroup(GetThis < FallingRock > ());                          //!�O���[�v�Ɏ������g��ǉ�
		GetStage()->SetSharedGameObject(L"FallingRock", GetThis<FallingRock>());//!�ǂݍ��݂̐ݒ������		
	}

	void FallingRock::OnUpdate()
	{
		//!������ꂽ��
		if (m_Falling)
		{
			auto ptrGra = AddComponent<Gravity>();//!�d�͂�����
		}
	}
}