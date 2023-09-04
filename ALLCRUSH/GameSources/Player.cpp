/**
* @file Player.cpp
* @brief �v���C���[�N���X�̎������L�q����Ă���\�[�X�t�@�C���t�@�C��
*/

#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross {

	//�萔
	constexpr float PLAYERBREAKESP = 2.0f;					//!�v���C���[���󂹂�
	constexpr float MAXPBDISTANCE = -3.0f;					//!�v���C���[�ƃ{�X�̋���
	constexpr int MAXWALLDAMAGE = 10;						//!�p���[�A�b�v���̕ǂɗ^����_���[�W
	constexpr int MAXPOWERCOUNT = 3;						//!�p���[�A�b�v�̍ő�l
	constexpr float PLAYERMAXSPEED = 2.0f;					//!�v���C���[�̍ő�X�s�[�h
	constexpr float TELOPFIRSTPLAYERPOSITION = 22.0f;		//!�e���b�v�̏o��ʒu1
	constexpr float TELOPSECONDPLAYERPOSITION = -52.0f;		//!�e���b�v�̏o��ʒu2
	constexpr float TELOPTREEDPLAYERPOSITION = -83.0f;		//!�e���b�v�̏o��ʒu3
	constexpr float MAXTELOPTIME = 2.0f;					//!�e���b�v�̏o�鎞��
	constexpr float MAXITEMTIME = 4.0f;						//!�A�C�e���̌��ʎ���
	constexpr float DEFAULTSPEED = 1.0f;					//!�ʏ�̎���
	constexpr float SLOWSPEED = 0.5;						//!�x���Ȃ������̎���
	constexpr float LOUDNESS = 0.5f;						//!�T�E���h�̑傫��
	constexpr int DEFULT = 1;								//!�ʏ�
	void Player::OnCreate()
	{

		m_transform = GetComponent<Transform>();
		AddComponent<BoneModelComponent>(m_playerBoneModelDeta);

		//�`��R���|�[�l���g�̐ݒ�
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		AddComponent<AnimationComponent>(L"Player", L"Default");									//!�A�j���[�V�����̓ǂݍ���

	}

	void Player::OnUpdate()
	{
		OpeningCamera();
		Enemydistance();
		ItemDisplay();
		PlayerMove();
		WalkAnimation();
		PlayerAction();
		TelopManager();
		ControllerCheck();
	}
	//�v���C���[������̕��̂ɓ���������
	void Player::OnCollisionEnter(shared_ptr<GameObject>& Other) {
		auto ptr = dynamic_pointer_cast<EnemyObject>(Other);
		if (ptr) {
		}
		auto ptr1 = dynamic_pointer_cast<ExitWall>(Other);
		if (ptr1) {
			SetGameState(GameState::GameExit);
		}

		auto ptr2 = dynamic_pointer_cast<Trap>(Other);
		if (ptr2) {
			m_maxMoveSpeed = SLOWSPEED;
			m_Trapdecision = true;
			GetStage()->RemoveGameObject<Trap>(Other);
		}
	}


	int Player::BrokenWall(int wallHp)
	{
		//�p���[�A�b�v���̏���
		switch (m_Power)
		{
		case 0:
			wallHp -= MAXWALLDAMAGE;
			m_Power = DEFULT;//!�p���[��1�ɂ���
			m_powerCount = 0;//!�p���[
			m_Gageflash = DEFULT;
			break;
			//�p���[�A�b�v�O�̏���
		case 1:
			wallHp--;
			break;
		}


		//!�ǂ�Hp��0�ȉ��̎�
		if (wallHp <= 0)
		{
			auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
			if (PtrSpark) {
				auto pos = m_transform.lock()->GetPosition();
				PtrSpark->InsertSplash(pos);
				PtrSpark->InsertSpark(pos);
			}

			m_powerCount++;
			//!�p���[���ő�ɂȂ�����
			if (m_powerCount >= MAXPOWERCOUNT)
			{
				m_powerCount = MAXPOWERCOUNT;//�p���[���ő�ȏ�ɂȂ�Ȃ��悤�ɐݒ�
			}

			auto& BrakeSound = App::GetApp()->GetXAudio2Manager();
			//�T�E���h�̍Đ�
			BrakeSound->Start(L"BrakeWall", 0, LOUDNESS);

		}

		//!�ǂ�Hp��0�ȏ�̎�
		else
		{
			auto& AttackSound = App::GetApp()->GetXAudio2Manager();
			AttackSound->Start(L"AttackWall", 0, LOUDNESS);
		}

		return wallHp;//�ύX���hp
	}

	//�ǂ�j�󂷂�
	void Player::BreakWall()
	{
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		SPHERE playerSp(position, PLAYERBREAKESP);

		//����ǂ̃O���[�v�̎擾
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto& vec = group->GetGroupVector();

		//�ǂ̔j�󏈗�
		for (auto& v : vec) {
			//�O���[�v�̂P�����o��
			auto shPtr = v.lock();
			Vec3 ret;
			//����ǂ̎擾
			auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
			if (ptrWall) {
				auto wallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();//����ǂ̏Փ˔���擾
				auto wallHP = ptrWall->GetHP();                                //����ǂ�HP�擾
                 /*�߂Â�����*/
				if (HitTest::SPHERE_OBB(playerSp, wallObb, ret)) {
					//�ǂƂ̋�����2.0�ȉ��ɂȂ���
					auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
					ptrWall->SetHP(BrokenWall(wallHP));
				}
			}
		}

	}


	void Player::Enemydistance()
	{
		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//�`��R���|�[�l���g�̎擾
		auto AnimationName = ptrDraw->GetCurrentAnimation();//���݂̃A�j���[�V���������擾����
		auto transComp = GetComponent<Transform>();			//�g�����X�t�H�[���̎擾
		auto position = transComp->GetPosition();			// ���݂̈ʒu���W���擾����
		auto rotation = transComp->GetRotation();
		//�{�X�̍��W�擾
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//�N���X�ɂ́i�j���K�v�ł������������Ƃ��Ɩ������ǂ����ł��K�v
		auto EnemyPositon = ptrEnemy->GetComponent<Transform>()->GetPosition();

		//�{�X�ƃv���C���[�����̋����ɒB������
		m_PBdistance = position.x - EnemyPositon.x;
		if (m_PBdistance >= MAXPBDISTANCE)
		{
			position.z = m_EndPos;
			transComp->SetRotation(m_EndAngle, 0.0f, m_EndAngle);

			if (AnimationName != L"GameOver") {
				ptrDraw->ChangeCurrentAnimation(L"GameOver");
				m_gameOver = 1;
				m_moveStop = false;
				if (m_moveStop == false)
				{
					if (m_State == GameState::Game)
					{
						m_State = GameState::Down;
					}
				}
			}
		}
	}

	void Player::ItemDisplay()
	{
		if (m_itemDisplay)
		{
			float elapsedTime1 = App::GetApp()->GetElapsedTime();//!�G���p�\�^�C���̎擾
			m_itemtime += elapsedTime1;
			if (m_itemtime >= MAXITEMTIME)
			{
				m_maxMoveSpeed = DEFAULTSPEED;//!�A�C�e���g�p�O�̃X�s�[�h�ɖ߂�
			}
		}
	}
	
	void Player::PlayerAction()
	{

		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();
		auto AnimationNow = ptrDraw->UpdateAnimation(elapsedTime);	//���݂̃A�j���[�V�������I��������Atrue
		auto& ActionName = ptrDraw->GetCurrentAnimation();

		if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPull�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");
				ptrXA->Start(L"Hammer", 0, LOUDNESS);
				//�v���C���[���ǂ��󂷏���
				BreakWall();
				
				//�v���C���[���U�������Ă���
				m_playerAttack = true;
				return;
			}
		}

		//�U������
		else if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPush�̂Ƃ�����if���ɓ�������AChangeCurrentAnimation��ActionPuh�ɂ���
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//�T�E���h�̍Đ�
				ptrXA->Start(L"Hammer", 0, LOUDNESS);
			}
		}

		else {
			if (AnimationNow) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				ptrXA->Stop(m_BGM);
				//�v���C���[���U�����I����
				m_playerAttack = false;
				m_moveStop = true;//�ړ���~����

			}
		}

	}

	void Player::OpeningCamera()
	{
		if (m_opningCamera == true)
		{
			auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_moveStop = false;//!�I�[�v�j���O�J�������~�߂�
			m_opningStop += elapsedTime;
			if (m_opningStop >= XM_PI) {
				m_opningCamera = false;//!�I�[�v�j���O�J������ǂ���
				m_moveStop = true;//�v���C���[�̓������������
			}
			
		}
		
		
	}

	void Player::PlayerMove()
	{

		// �A�v���P�[�V�����I�u�W�F�N�g���擾����
		auto& app = App::GetApp();
		// �f���^�^�C�����擾����
		float delta = app->GetElapsedTime(); // �O�t���[������́u�o�ߎ��ԁv
		// �J�������擾����
		auto stage = GetStage(); // ���̃I�u�W�F�N�g���ǉ�����Ă���X�e�[�W
		auto& camera = stage->GetView()->GetTargetCamera(); // �J�������擾����
		// �J�����̉�荞��
		float rad = XM_PI * 0.5f;

		// �Q�[���R���g���[���[�I�u�W�F�N�g���擾����
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // �[���Ԗڂ̃R���g���[���[���擾����
		m_moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // �傫���� 0.0f �` 1.0f;
		auto m = Mat3x3( // Y�����S�ŉ�]������s��
			Vec3(cosf(rad), 0.0f, sinf(rad)),   // X���̌���
			Vec3(0.0f, 0.0f, 0.0f),   // Y���̌���
			Vec3(-sinf(rad), 0.0f, cosf(rad))); // Z���̌���
		m_moveDir = m_moveDir * m; // �X�e�B�b�N�̓��͂�angleY���W�A����]������
		m_speed = m_maxMoveSpeed * m_moveDir.length() * m_moveStop; // �ő呬�~�X�e�B�b�N�x�N�g���̑傫���~��~�����邩�ǂ����̔���
		m_moveDir.normalize(); // �ړ������𐳋K������
		auto transComp = m_transform.lock();
		auto position = transComp->GetPosition(); // ���݂̈ʒu���W���擾����
		auto rotation = transComp->GetRotation();
		auto scale = transComp->GetScale();

		// �v���C���[�̈ړ�
		position += m_moveDir * m_speed * delta; // �f���^�^�C�����|���āu�b�ԁv�̈ړ��ʂɕϊ�����
		transComp->SetPosition(position); // �X�V�����l�ōĐݒ肷��


	}

	void Player::WalkAnimation()
	{
		auto transComp = m_transform.lock();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//�A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();

		if (m_speed > 0.0f) // �X�e�B�b�N���|��Ă�����E�E
		{
			float rotY = atan2f(-m_moveDir.z, m_moveDir.x); // �A�[�N�^���W�F���g���g���ƃx�N�g�����p�x�ɕϊ��ł���
			transComp->SetRotation(0.0f, rotY, 0.0f); // ���W�A���p�Őݒ�
			//�����A�j���[�V����
			if (AnimationName == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//�T�E���h�̍Đ�
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();
				m_BGM = ptrXA->Start(L"run", 0, LOUDNESS);
			}
		}
		else {
			//�����~�܂�A�j���[�V����
			if (AnimationName == L"Move") {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();
				ptrXA->Stop(m_BGM);
			}
		}
	}

	void Player::ControllerCheck()
	{
		auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());

		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());
		m_InputHandler2.PushHandle(GetThis<Player>());
		if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());

	}
	
	//A�{�^��
	void Player::OnPushA() 
	{
		//�n���}�[��U��A�j���[�V����
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& action = ptrDraw->GetCurrentAnimation();

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(�����̒�~)

			m_moveStop = false;//�ړ��̒�~
		}
	}


	
	void Player::OnPushY() {
		auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
		auto& PowerUpSound = App::GetApp()->GetXAudio2Manager();
		//�Q�[�W�����܂�����
		if (m_powerCount >= MAXPOWERCOUNT)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			PowerUpSound->Start(L"PowerUp", 0, LOUDNESS);
			m_Power = 0;
			PtrSpark->InsertPowerUp(pos);
		}
	}

	//X�{�^��
	void Player::OnPushX() {
		auto Shitem = GetStage()->GetSharedGameObject<Myitem1>(L"Myitem1");
		auto PlayerPos = GetComponent<Transform>()->GetPosition();
		auto& SpeedUpSound = App::GetApp()->GetXAudio2Manager();

		if (m_itemCondition) {
			m_maxMoveSpeed = PLAYERMAXSPEED;
			m_itemDisplay = true;

			auto XSprite1 = GetStage()->GetSharedGameObject<XSprite>(L"XSprite");
			XSprite1->SetDrawActive(false);

			Shitem->SetDrawActive(false);
			//�T�E���h�̍Đ�
			SpeedUpSound->Start(L"SpeedUp", 0, LOUDNESS);

			auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
			if (PtrSpark) {
				auto pos = GetComponent<Transform>()->GetPosition();
				PtrSpark->InsertSpeedUp(pos);
			}
		}
		if (GetGameState() == GameState::ChangeStage) {
			PostEvent(0.0f, GetThis<Player>(), App::GetApp()->GetScene<Scene>(), L"ToTitleStage");
		}
	}

	void Player::TelopManager() {
		auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();
		auto ptrTrans = GetComponent<Transform>();
		Vec3 pos = ptrTrans->GetPosition();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//�R���g���[���`�F�b�N���ē��͂�����΃R�}���h�Ăяo��
		m_InputHandler.PushHandle(GetThis<Player>());

		//!�����󂹂̃e���b�v
		if (pos.x < TELOPSECONDPLAYERPOSITION) {
			auto ptrStage1 = GetStage()->GetSharedGameObject<Telop>(L"Telop");
			ptrStage1->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_TelopTime += elapsedTime;
			if (m_TelopTime >= MAXTELOPTIME)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage1->SetDrawActive(false);

			}
		}

		// �o���e���b�v
		if (pos.x < TELOPTREEDPLAYERPOSITION) {
			auto ptrStage3 = GetStage()->GetSharedGameObject<Telop3>(L"Telop3");
			ptrStage3->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_Telop3Time += elapsedTime;
			if (m_Telop3Time >= MAXTELOPTIME)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage3->SetDrawActive(false);

			}
		}
		
		if (Select == 0)
		{
        // �ǂ��󂹁I�I�e���b�v
		if (pos.x < TELOPFIRSTPLAYERPOSITION) {
			auto ptrStage4 = GetStage()->GetSharedGameObject<Telop4>(L"Telop4");
			ptrStage4->SetDrawActive(true);
			// ���Ԃ̕ϐ��ɑ���
			m_Telop4Time += elapsedTime;
			if (m_Telop4Time >= MAXTELOPTIME)
			{
				// 1�b��ɕ\�����I�t�ɂȂ�
				ptrStage4->SetDrawActive(false);

			}
		}
		}
		

	}
	void Player::OnDestroy() {
		//BGM�̃X�g�b�v
		auto& PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross