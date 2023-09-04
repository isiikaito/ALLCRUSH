/*!
@file OnPushButtonXTelop.cpp
@brief �Q�[���I�[�o�[�X�v���C�g����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	constexpr float STARTSCALEZ = 1.0f;//!z�̑傫��

	
	PushButtonXTelop::PushButtonXTelop(const shared_ptr<Stage>& StagePtr,
		const wstring& TextureKey,
		bool Trace,
		const Vec2& StartScale,
		const Vec3& StartPos) :
		GameObject(StagePtr),
		m_TextureKey(TextureKey),
		m_Trace(Trace),
		m_StartScale(StartScale),
		m_StartPos(StartPos),
		m_LeftUpperSummit(Vec2(0.0f, 0.0f)),
		m_LeftLowerSummit(Vec2(0.0f, 1.0f)),
		m_RightUpperSummit(Vec2(1.0f, 0.0f)),
		m_RightLowerSummit(Vec2(1.0f, 1.0f))
	{}

	PushButtonXTelop::~PushButtonXTelop() {}
	void PushButtonXTelop::OnCreate() {
		float HelfSize = 0.5f;
		//���_�z��(�c��5���\��)
		vector<VertexPositionColorTexture> vertices = {
			{ VertexPositionColorTexture(Vec3(-HelfSize, HelfSize, 0),m_TextureColor, m_LeftUpperSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, HelfSize, 0),m_TextureColor, m_RightUpperSummit) },
			{ VertexPositionColorTexture(Vec3(-HelfSize, -HelfSize, 0), m_TextureColor, m_LeftLowerSummit) },
			{ VertexPositionColorTexture(Vec3(HelfSize, -HelfSize, 0),m_TextureColor, m_RightLowerSummit) },
		};
		//�C���f�b�N�X�z��
		vector<uint16_t> indices = { 0, 1, 2, 1, 3, 2 };

		//��������
		SetAlphaActive(m_Trace);

		//�����ʒu�̐ݒ�
		auto PtrTransform = GetComponent<Transform>();
		PtrTransform->SetScale(m_StartScale.x, m_StartScale.y, STARTSCALEZ);
		PtrTransform->SetPosition(m_StartPos.x, m_StartPos.y, 0.0f);

		//���_�ƃC���f�b�N�X���w�肵�ăX�v���C�g�쐬
		auto PtrDraw = AddComponent<PCTSpriteDraw>(vertices, indices);
		PtrDraw->SetSamplerState(SamplerState::LinearWrap);
		//�e�N�X�`���̓ǂݍ���
		PtrDraw->SetTextureResource(m_TextureKey);
	}
}
