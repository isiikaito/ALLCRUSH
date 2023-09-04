/*!
@file MyMovieStage.h
@author isiikaito
@brief 
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class MyClearStage : public MovieStage {
		//���̓n���h���[
		InputHandler<MyMovieStage> m_InputHandler;
		float MovieTime;							//���掞��
		float m_Time ;								//����
	public:
		//�\�z�Ɣj��
		MyClearStage() :MovieStage(),
			MovieTime(21.0f),
			m_Time(0.0f) {}
		//�f�X�g���N�^
		virtual ~MyClearStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate() override;
		
		
	};
}
//end namespace basecross
