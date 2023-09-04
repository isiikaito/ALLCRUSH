/*!
@file GageSprite.cpp
@brief �Q�[�W�̎���a
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//�Q�[�W
	constexpr float HELFSIZE = 0.5f;//!�|���S���T�C�Y
	constexpr float STARTSCALEZ = 1.0f;//!z�̑傫��

	GageSprite::GageSprite(const shared_ptr<Stage>& StagePtr, bool Trace,
		const Vec2& StartScale, const Vec3& StartPos) :
		GameObject(StagePtr),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_TotalTime(0),
		m_BreakCount(2),
		m_PowerON(0),
		m_PowerOFF(1),
		firstScale(40.0f, 50.0f, 1.0f),
		firstpos(550.0f, -310.0f, 0.1f),
		secondScale(40.0f, 90.0f, 1.0f),
		secondpos(550.0f, -290.0f, 0.1f),
		treedScale(40.0f, 130.0f, 1.0f),
		treedpos(550.0f, -270.0f, 0.1f),
		m_TextureColor(Col4(1.0f, 1.0f, 1.0f, 1.0f)),
		m_gageTextureColor(Col4(1.0f, 0.0, 0.0f, 1.0f))

	{}

	GageSprite::~GageSprite() {}
	void GageSprite::OnCreate() {


		
		//���_�z��
		m_BackupVertices = 
		{
			                                                        
         { VertexPositionColor(Vec3(-HELFSIZE, HELFSIZE, 0),m_TextureColor) },
         { VertexPositionColor(Vec3(HELFSIZE, HELFSIZE, 0), m_TextureColor) },
         { VertexPositionColor(Vec3(-HELFSIZE, -HELFSIZE, 0),m_TextureColor) },
         { VertexPositionColor(Vec3(HELFSIZE, -HELFSIZE, 0), m_TextureColor) },
	    };
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };
		SetAlphaActive(m_Trace);
		
		//�����ʒu�̐ݒ�
		auto ptrTrans = GetComponent<Transform>();
		ptrTrans->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		ptrTrans->SetRotation(0, 0, 0);
		ptrTrans->SetPosition(m_StartPos);

        //���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto ptrDraw = AddComponent<PCSpriteDraw>(m_BackupVertices, indices);
		SetAlphaActive(true);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		AddComponent<PCSpriteDraw>(m_BackupVertices, indices);


		ptrDraw->SetDiffuse(m_gageTextureColor);

		SetDrawActive(false);
	}

	//�_�ŏ����iElapsedtime�𗘗p���Ă���j
	void GageSprite::OnUpdate() {

	//�v���C���[�̎擾
	auto ptrPlayer = GetStage()->GetSharedGameObject<Player>(L"Player");
	auto PowerCount = ptrPlayer->GetPowerCount();
		//�ǂ���������
		ptrPlayer->SetPowerCount(PowerCount);
		//�p���[�A�b�v���Ă��邩�ǂ���
		auto Power = ptrPlayer->GetPower();
		ptrPlayer->SetPower(Power);
		//�A�C�e�����g�������ǂ���
		auto Gageflash = ptrPlayer->GetGageflash();
		ptrPlayer->SetGageflash(Gageflash);
		
		auto ptrTrans = GetComponent<Transform>();
		
		switch (PowerCount)
		{
		case first://!�ǂ���󂵂���
			ptrTrans->SetScale(firstScale);
			ptrTrans->SetPosition(firstpos);
			SetDrawActive(true);
			break;
		case second:
			ptrTrans->SetScale(secondScale);
			ptrTrans->SetPosition(secondpos);
			break;
		case treed:
			ptrTrans->SetScale(treedScale);
			ptrTrans->SetPosition(treedpos);
			break;

		default:
			break;
		}
		



		//�p���[�A�b�v������
		if (Power == m_PowerON)
		{
			//�_��

			//���Ԃ̎擾
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_TotalTime += elapsedTime;
			if (m_TotalTime >= XM_PI) {
				m_TotalTime = 0;
			}
			//���_�̎擾
			vector<VertexPositionColor> newVertices;
			for (size_t i = 0; i < m_BackupVertices.size(); i++) {
				Col4 col = m_BackupVertices[i].color;
				//sin��0�`�P�܂łɂ���0�̎��͓����P�̎��͕\���Ƃ��Ă���
				col.w = sin(m_TotalTime);
				auto v = VertexPositionColor(
					m_BackupVertices[i].position,
					col
				);
				newVertices.push_back(v);
			}
			auto ptrDraw = GetComponent<PCSpriteDraw>();
			ptrDraw->UpdateVertices(newVertices);

		}
		//�A�C�e�����g������
		if (Gageflash == m_PowerOFF)
		{
			//�Q�[�W������
			SetDrawActive(false);
			Gageflash = m_PowerON;
		}

	}

}
