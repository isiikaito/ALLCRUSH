/*!
@file GameOverStage.h
@brief �Q�[���I�[�o�[�X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	�Q�[���I�[�o�[�X�v���C�g
	//--------------------------------------------------------------------------------------
	class GMOTelop : public GameObject {
		bool m_Trace;					//�����ɂȂ邩�ǂ���
		Vec2 m_StartScale;				//�X�P�[�����O
		Vec3 m_scale;					//�傫��
		Vec3 m_position;				//�ʒu
		Vec2 m_StartPos;				//�ꏊ
		wstring m_TextureKey;			//�e�N�X�`���̖��O
		const Vec2 m_LeftUpperSummit;	//!����̒��_
		const Vec2 m_LeftLowerSummit;	//!�����̒��_
		const Vec2 m_RightUpperSummit;	//!�E��̒��_
		const Vec2 m_RightLowerSummit;	//!�E���̒��_
		Col4 m_TextureColor;			//!�e�N�X�`���̐F
	public:
		GMOTelop(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec2& StartPos);
		//�j��
		virtual ~GMOTelop();
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross
