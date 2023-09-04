/**
*@file FallingRock.h
*@brief ���΃I�u�W�F�N�g�̎�������`����Ă���w�b�_�[�t�@�C��
*@author Kaito Isii
*@details ���΃I�u�W�F�N�g�̎���
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"
/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross {

	class FallingRock : public GameObject {
		bool m_Falling;	//�����锻��
		StaticModelDeta m_fallingRockModelData;//!���΂̃��f���f�[�^

	public:

		/**
		* �R���X�g���N�^
		*/
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

        /**
�@�@�@�@* �f�X�g���N�^
�@�@�@�@*/
		virtual ~FallingRock() {}

		
		/**
		* ���΃I�u�W�F�N�g�̏����p�����[�^������������֐�
		*/
		virtual void OnCreate() override;

		/**
		* ���I�u�W�F�N�g���j�󂳂ꂽ�Ƃ��ɗ��΂�������֐�
		*/
		virtual void OnUpdate() override;
		
		/**
         * ���I�u�W�F�N�g���j�󂳂ꂽ���ǂ���
         * @return int ���I�u�W�F�N�g���X�e�[�W��ɑ��݂��邩�ǂ������Ԃ��Ă���
         */
		bool GetFalling()const {
			return m_Falling;
		}

		/**
		 * ���I�u�W�F�N�g���j�󂳂ꂽ���ǂ���
		 * @param[in] int  Falling �X�e�[�W��Ŕj�󂳂�t���ǂ���
		 */
		void SetFalling(bool Falling) {
			m_Falling = Falling;
		}
	};
}
