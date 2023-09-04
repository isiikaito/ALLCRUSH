/**
*@file Obstacle1.h
*@brief ��Q���I�u�W�F�N�g�̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details ��Q���I�u�W�F�N�g�̎���
*/

#pragma once
#include "stdafx.h"

/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class Obstacle1 : public GameObject {
		StaticModelDeta m_obstacleModelData;//!��Q���̃��f���f�[�^

	public:
		/**
		* �R���X�g���N�^
		*/
		Obstacle1(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~Obstacle1() {}

		/**
		* ��Q���I�u�W�F�N�g�̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

		/**
		* ��Q���I�u�W�F�N�g�̍X�V������֐�
		*/
		virtual void OnUpdate() override;

	};
}
