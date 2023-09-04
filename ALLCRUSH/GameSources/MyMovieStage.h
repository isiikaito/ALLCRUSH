/*!
@file MyMovieStage.h
@brief 
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	//--------------------------------------------------------------------------------------
	//	���[�r�[�X�e�[�W�N���X
	//--------------------------------------------------------------------------------------
	class MyMovieStage : public MovieStage {
		InputHandler<MyMovieStage> m_InputHandler;		//���̓n���h���[
		ResetHandler<MyMovieStage> ResetHandler;	   //���Z�b�g�n���h���[
		void MovieSkip();
		float MovieTime;
		float m_Time;
	public:
		//�\�z�Ɣj��
		MyMovieStage() :MovieStage(),
		MovieTime(43.6f),
		m_Time(0.0f){}
		//�f�X�g���N�^
		virtual ~MyMovieStage() {}
		//������
		virtual void OnCreate()override;
		//�X�V
		virtual void OnUpdate() override;
		//���Z�b�g
		void OnPushReset(){}
		//����̃X�L�b�v
		void OnPushSkip();
	};
}
//end namespace basecross
