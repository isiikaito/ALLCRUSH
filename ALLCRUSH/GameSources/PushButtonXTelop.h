/*!
@file OnPushButtonXTelop.h
@brief X�{�^�������Ă˃X�v���C�g
*/

#pragma once
#include "stdafx.h"

namespace basecross {
	//--------------------------------------------------------------------------------------
	//	OnPushButtonX�X�v���C�g�N���X
	//--------------------------------------------------------------------------------------
	class PushButtonXTelop : public GameObject {
		bool m_Trace;        //�����ɂȂ邩�ǂ���
		Vec2 m_StartScale;   //�X�P�[�����O
		Vec3 m_StartPos;     //�ꏊ
		wstring m_TextureKey;//�e�N�X�`���̖��O
		const Vec2 m_LeftUpperSummit;	//!����̒��_
		const Vec2 m_LeftLowerSummit;	//!�����̒��_
		const Vec2 m_RightUpperSummit;	//!�E��̒��_
		const Vec2 m_RightLowerSummit;	//!�E���̒��_
		Col4 m_TextureColor;			//!�e�N�X�`���̐F
	public:
		PushButtonXTelop(const shared_ptr<Stage>& StagePtr,
			const wstring& TextureKey,
			bool Trace,
			const Vec2& StartScale,
			const Vec3& StartPos);
		//�j��
		virtual ~PushButtonXTelop();
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate()override {}
	};
}
//end namespace basecross
