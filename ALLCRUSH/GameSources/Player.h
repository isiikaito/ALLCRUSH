/**
* @file Player.h
* @brief �v���C���[�N���X�̒�`���L�q����Ă���w�b�_�[�t�@�C��
*/

#pragma once
#include "stdafx.h"
#include "BoneModelComponent.h"
/** basecross���ʂ̃l�[���X�y�[�X */
namespace basecross{
	enum class  GameState {
		Game,
		Down,
		FadeStart,
		FadeOut,
		ChangeStage,
		GameExit
	};

	/** �v���C���[�̑���E��ԁE���̑�*/
	class Player : public GameObject
	{
		float m_maxMoveSpeed;				//�ړ��̍ő呬
		bool m_moveStop;							//Player�̈ړ���~�̔���(true�Ȃ�ړ��\,false�Ȃ�ړ���~)
		Vec3 m_moveDir;							//�ړ������x�N�g���i�P�ʃx�N�g���j
		float m_EndPos;							//�Q�[���I�[�o�[���̃v���C���[���W
		float m_EndAngle;							//�Q�[���I�[�o�[���̃v���C���[�̌���
		float m_speed;							//�ړ��̑���
		float m_accel;							//�����x
		int m_gameOver;							//�Q�[���I�[�o�[�𔻒肷��
		bool m_itemCondition;					//�A�C�e���������Ă��邩�ǂ���
		bool m_itemDisplay;						//�A�C�e���̌��ʂ𔭊����Ă��邩�ǂ���
		float m_itemtime;							//�A�C�e���̎�������
		int m_powerCount;							//�p���[�A�b�v�A�C�e��
		bool m_pillarCount;						//�������Ă��邩�ǂ���
		int m_ExitCount;							//�o���ɂԂ�����
	    float m_PBdistance;						//�v���C���[�ƃ{�X�Ƃ̋���
		float m_TurnTime;						//�U��������璼��܂ł̎���
		int m_Power;								//�p���[�A�b�v�����邩�Ȃ���
		int m_Gageflash;							//�p���[�A�b�v���g�������ǂ���
		bool m_Trapdecision;					//�g���b�v�ɓ����������ǂ���
		GameState m_State;						//�Q�[���I�[�o�[�p�̃X�e�[�g
		bool m_Event;							//���̃C�x���g���s�����ǂ���
		float m_TelopTime;						//�e���b�v
		float m_Telop2Time;						//�e���b�v2	
		float m_Telop3Time;						//�e���b�v3
		float m_Telop4Time;						//�e���b�v4
        float m_opningStop;						//�I�[�v�j���O
		bool m_playerAttack;					//�v���C���[���A�^�b�N���Ă��邩�ǂ���
		bool m_opningCamera;					//�J������؂�ւ������ǂ���
		std::weak_ptr<Transform> m_transform;	//�g�����X�t�H�[��
		BoneModelDeta m_playerBoneModelDeta;	//!�G�̃��f���f�[�^

		InputHandler<Player> m_InputHandler;  //�R���g���[���[�̃{�^���̎擾1
		InputHandler2<Player> m_InputHandler2;//�R���g���[���[�̃{�^���̎擾2
		shared_ptr<SoundItem> m_BGM;          //BGM�̎擾
	
		//�e���b�v���o��
		void TelopManager();
		//�ǂ��󂷏���
		void BreakWall();
		//�v���C���[�ƃ{�X�Ƃ̋���
		void Enemydistance();
		//!�A�C�e�����g������ɃX�s�[�h��߂�����
		void ItemDisplay();
		//�v���C���[�A�N�V����
		void PlayerAction();
		//�R���g���[���[�̏���
		void PlayerMove();
		//�����A�j���[�V����
		void WalkAnimation();
		//�R���g���[���[�̔���
		void ControllerCheck();
		//�ǂ���ꂽ��̏���
		int BrokenWall(int wallHp);

	public:

		// �X�e�[�W��n����R���X�g���N�^���K�{
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage),//�X�e�[�W�͐e�N���X�ɓ�����
			m_maxMoveSpeed(6.0f),
			m_moveStop(1.0f),	
			m_EndPos(1.0f),
			m_EndAngle(180.0f * XM_PI / 180.0f),
			m_moveDir(0.0f, 0.0f, 0.0f),
			m_gameOver(0),
			m_speed(0.0f),
			m_accel(0.0f),
			m_itemCondition(false),
			m_itemDisplay(false),
			m_powerCount(0),
			m_Power(1),
			m_ExitCount(0),
			m_Gageflash(0),
			m_pillarCount(false),
			m_PBdistance(0),
			m_itemtime(0.0f),
			m_TelopTime(0.0f),
			m_Telop2Time(0.0f),
			m_Telop3Time(0.0f),
			m_Telop4Time(0.0f),
			m_opningStop(0.0f),
			m_TurnTime(0.0f),
			m_Event(false),
			m_Trapdecision(false),
			m_State(GameState::Game),
			m_playerAttack(false),
			m_opningCamera(true),
			m_playerBoneModelDeta
			(
				{
			Vec3(0.4f, 0.4f, 0.4f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(40.0f, 0.25f, 0.0f),
			Vec3(0.2f, 0.2f, 0.2f),
			Vec3(0.0f, 0.0f, 0.0f),
			Vec3(0.0f, XM_PI * -0.5f, 0.0f),
			Vec3(0.0f, -1.0f, 0.0f),
			L"Object_WalkAnimation_MESH",
			L"Object_WalkAnimation_MESH_WITH_TAN",
			L"OBJECT_NORMAL_TX"

				}
			)
			
			
		{}

		//�R���g���[���[�̃{�^������X
		void OnPushX(); 
		//�R���g���[���[�̃{�^������A
		void OnPushA(); 
		//�R���g���[���[�̃{�^������\���L�[��
		void OnPushUP() {}    
		//�R���g���[���[�̃{�^������\���L�[��
		void OnPushDOWN(){}  
		//�R���g���[���[�̃{�^������Y
		void OnPushY();   
		//�R���g���[���[�̃{�^������B
		void OnPushB() {}   
		//�I�u�W�F�N�g�̏������p�֐��iUnity��Start�֐��j
		void OnCreate() override; 
		//�I�u�W�F�N�g�̃t���[�����Ƃ̏����iUnity��Update�֐��j
		void OnUpdate() override; 
		//BGM���~�߂�
        void OnDestroy();  
		
		//�I�[�v�j���O�J����
		void OpeningCamera();     
		//�G�̍U���ɂԂ������Ƃ�
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		
		
		//�������Ă��邩����̎擾
		//return �������ă��邩�ǂ����̎擾
		bool GetPillarCount()const {
			return m_pillarCount;
		}
		//�������Ă��邩����̐ݒ�
		//���� �������ă��邩�ǂ���
		void SetPillarCount(bool PillarCount) {
			PillarCount = PillarCount;
		}

		//�ǂ��������񐔂̎擾
		//return �ǂ��������񐔂̎擾
		int GetPowerCount()const {
			return m_powerCount;
		}
		//�ǂ��������񐔂̐ݒ�
		//���� �ǂ���������
		void SetPowerCount(int PowerCount)
		{
			PowerCount = PowerCount;
		}

		//���ݍU�����[�V�����ɂȂ��Ă��邩�ǂ���
		//return ���ݍU�����[�V�����ɂȂ��Ă��邩�ǂ����̎擾
		bool GetPlayerAttack()
		{
			return m_playerAttack;
		}

		//���ݍU�����[�V�����ɂȂ��Ă��邩�ǂ����̐ݒ�
		//���� ���ݍU�����[�V�����ɂȂ��Ă��邩�ǂ���
		void SetItemCondition(bool itemCondition)
		{
			m_itemCondition = itemCondition;
		}
		
		//�p���[�A�b�v�̎擾
		//return �p���[�A�b�v�̎擾
		int GetPower() const {
			return m_Power;
		}
		//�p���[�A�b�v�̐ݒ�
		//���� �p���[�A�b�v��
		void SetPower(int Power)
		{
			Power = Power;
		}

		//�p���[�A�b�v���g�������ǂ������肷��
		//return �p���[�A�b�v���g�������ǂ���
		int GetGageflash() const {
			return m_Gageflash;
		}
		//�p���[�A�b�v���g�������ǂ������肷��
		//���� �p���[�A�b�v���g�������ǂ���
		void SetGageflash(int Gageflash)
		{
			Gageflash = Gageflash;
		}

		//�o���ɓ����������ǂ����̎擾
		//return �o���ɓ����������ǂ���
		int GetExitCount() const {
			return m_ExitCount;
		}

		//�o���ɓ����������ǂ����̐ݒ�
		//���� �o���ɓ����������ǂ���
		void SetExitCount(int ExitCount)
		{
			ExitCount = ExitCount;
		}

		//���C�x���g�������������ǂ����̎擾
		//return ���C�x���g�������������ǂ�
		bool GetPEvent()const {
			return m_Event;
		}

		//���C�x���g�������������ǂ����̐ݒ�
		//���� ���C�x���g�������������ǂ���
		void SetPEvent(bool m_Event)
		{
			m_Event = m_Event;
		}

		//�Q�[���I�[�o�[����̔���
		//return �Q�[���I�[�o�[����̔���
		int GetGameOver()const {
			return m_gameOver;
		}

		//�Q�[���I�[�o�[����̔���̐ݒ�
		//���� �Q�[���I�[�o�[����̔���
		void SetGameOver(int GameOver) {
			GameOver = GameOver;
		}

		//�X�e�[�W��؂�ւ��̎擾
		//return �X�e�[�W��؂�ւ���
		GameState GetGameState() const
		{
			return m_State;
		}

		//�X�e�[�W��؂�ւ��̐ݒ�
		//���� �X�e�[�W��؂�ւ�
		void SetGameState(GameState s) {
			m_State = s;
		}

	};
}
//end basecross

