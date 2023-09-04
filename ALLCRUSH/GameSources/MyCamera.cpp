/**
* @file MyCamera.cpp
* @brief �J�����N���X�̒�`���L�q����Ă���\�[�X�t�@�C��
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float MAXDISTANCE = 5.0f;//!���ƃv���C���[�̋߂Â�������̍ő勗��
	constexpr float TURNTIME = 4.0f;//!�U������Ă��鎞��
	constexpr float EYEPOSY = 2.0f;//!�J������y�ʒu
	constexpr float PLAYERPOSY = 0.5f;//!�v���C���[��
	constexpr int ENEMYSETDRAWACTIVECOUNT = 1;//!�G�̕\�������邩�ǂ���
	constexpr float ENEMYPAYERDISTANCE = -3.0f;//!�G�ƃv���C���[�̋���
	constexpr float PLAYERPOSX = 5.0f;//!B�{�^�����������Ƃ��̃v���C���[�̈ʒu�������l

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	// �J����
	void MyCamera::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];


		// �v���C���[�̍��W���擾����
		Vec3 playerPos(0.0f); // �v���C���[�̍��W�i���j
		Vec3 pillarPos(0.0f);
		Vec3 enemyPos(0.0f);//�G�̍��W�i���j
		int EnemySetDrawActiveCount(0);
		int PillarCount(0);
		auto stage = app->GetScene<Scene>()->GetActiveStage(); // �X�e�[�W�I�u�W�F�N�g���擾����
		auto objs = stage->GetGameObjectVec(); // �X�e�[�W�ɒǉ�����Ă��邷�ׂẴI�u�W�F�N�g
		for (auto& obj : objs)
		{
			// �v���C���[�ւ̃L���X�g�����݂�
			auto player = dynamic_pointer_cast<Player>(obj);
			auto pillar = dynamic_pointer_cast<Pillar>(obj);
			auto Enemy = dynamic_pointer_cast<EnemyObject>(obj);
			if (player)
			{
				// �L���X�g�ɐ������Ă�������W���擾����
				auto playerTrans = player->GetComponent<Transform>();
				playerPos = playerTrans->GetPosition();
				PillarCount = player->GetPillarCount();
				player->SetPillarCount(PillarCount);
			}

			// ���ւ̃L���X�g�����݂�
			else if (pillar)
			{
				// �L���X�g�ɐ������Ă�������W���擾����
				auto pillarTrans = pillar->GetComponent<Transform>();
				pillarPos = pillarTrans->GetPosition();
			}
			//�{�X�ւ̃L���X�g�����݂�
			else if (Enemy)
			{
				EnemySetDrawActiveCount = Enemy->GetEnemySetDrawActiveCount();
				Enemy->SetEnemySetDrawActiveCount(EnemySetDrawActiveCount);
				enemyPos = Enemy->GetComponent<Transform>()->GetPosition();
			}
			
		}

		float ed = playerPos.x - enemyPos.x;//�v���C���[�ƃG�l�~�[�̋���

		auto eye = playerPos + Vec3(cosf(0.0f), 0.0f, sinf(0.0f)) * distance;
		eye.y = EYEPOSY;
		playerPos.y = PLAYERPOSY;


		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B|| ed >= ENEMYPAYERDISTANCE)
		{
			eye.x = playerPos.x - PLAYERPOSX;
		}


		SetEye(eye);
		SetAt(playerPos); // �v���C���[�𒆎~����悤�ɂ���

		//�v���C���[�ƒ��̋���
		PPdistance = playerPos.x - pillarPos.x;
		//�v���C���[�ƒ��̈ʒu�����̋����ɂȂ�����U��Ԃ�
		auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();

		//sutge1�̎�
		if (Select == 0)
		{
			//�������݂���Ƃ�
			if (m_Turn == true)
			{
				//���ƃv���C���[�̋�����5�ȉ��ɂȂ�����
				if (PPdistance <= MAXDISTANCE)
				{
					EnemySetDrawActiveCount = 0;
					auto CameraAngleY = XM_PI;

					auto eye = playerPos + Vec3(cosf(CameraAngleY), 0.0f, sinf(0.0f)) * distance;
					eye.y = EYEPOSY;
					SetEye(eye);

					m_front = true;
				}
			}

			//������ꂽ��
			if (m_front)
			{

				//elapsedTime���擾���邱�Ƃɂ�莞�Ԃ��g����
				float elapsedTime = App::GetApp()->GetElapsedTime();
				//���Ԃ�ϐ��ɑ���
				m_TurnTime += elapsedTime;
				//�������Ă����b���
				if (m_TurnTime > TURNTIME && m_TurnTime < TURNTIME+0.1f)
				{
					EnemySetDrawActiveCount = ENEMYSETDRAWACTIVECOUNT;
					//�J���������ʂ�����
					auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // �v���C���[�̍��W�𒆐S�ɁAangleY����荞�ށi�v���C���[����̋�����distance�j
					eye.y = EYEPOSY;
					playerPos.y = PLAYERPOSY;

					m_Turn = false;

					SetEye(eye);
					SetAt(playerPos); // �v���C���[�𒍎�����悤�ɂ���

				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	�I�[�v�j���O�J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	OpeningCamera::OpeningCamera() :
		Camera()
	{}
	OpeningCamera::~OpeningCamera() {}

	void OpeningCamera::OnUpdate() {
		auto ptrOpeningCameraman = dynamic_pointer_cast<OpeningCameraman>(GetCameraObject());
		if (ptrOpeningCameraman) {
			auto pos = ptrOpeningCameraman->GetAtPos();
			SetAt(pos);
		}
		Camera::OnUpdate();
	}
	//--------------------------------------------------------------------------------------
	//	���C���J�����i�R���|�[�l���g�ł͂Ȃ��j
	//--------------------------------------------------------------------------------------
	//�\�z�Ɣj��
	ObjCamera::ObjCamera() :
		Camera()
	{}
	ObjCamera::~ObjCamera() {}

	void ObjCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	void ObjCamera::OnUpdate() {
		auto ptrTarget = m_TargetObject.lock();
		if (ptrTarget) {
			auto pos = ptrTarget->GetComponent<Transform>()->GetPosition();
			pos.y += 1.0f;
			SetAt(pos);
		}
		Camera::OnUpdate();
	}
}

//end basecross