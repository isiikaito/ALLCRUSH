/**
* @file Player.cpp
* @brief プレイヤークラスの実装が記述されているソースファイルファイル
*/

#include "stdafx.h"
#include "Project.h"
#include "AnimationComponent.h"

namespace basecross {

	//定数
	constexpr float PLAYERBREAKESP = 2.0f;					//!プレイヤーが壊せる
	constexpr float MAXPBDISTANCE = -3.0f;					//!プレイヤーとボスの距離
	constexpr int MAXWALLDAMAGE = 10;						//!パワーアップ時の壁に与えるダメージ
	constexpr int MAXPOWERCOUNT = 3;						//!パワーアップの最大値
	constexpr float PLAYERMAXSPEED = 2.0f;					//!プレイヤーの最大スピード
	constexpr float TELOPFIRSTPLAYERPOSITION = 22.0f;		//!テロップの出る位置1
	constexpr float TELOPSECONDPLAYERPOSITION = -52.0f;		//!テロップの出る位置2
	constexpr float TELOPTREEDPLAYERPOSITION = -83.0f;		//!テロップの出る位置3
	constexpr float MAXTELOPTIME = 2.0f;					//!テロップの出る時間
	constexpr float MAXITEMTIME = 4.0f;						//!アイテムの効果時間
	constexpr float DEFAULTSPEED = 1.0f;					//!通常の時間
	constexpr float SLOWSPEED = 0.5;						//!遅くなった時の時間
	constexpr float LOUDNESS = 0.5f;						//!サウンドの大きさ
	constexpr int DEFULT = 1;								//!通常
	void Player::OnCreate()
	{

		m_transform = GetComponent<Transform>();
		AddComponent<BoneModelComponent>(m_playerBoneModelDeta);

		//描画コンポーネントの設定
		auto ptrDraw = AddComponent<BcPNTnTBoneModelDraw>();
		ptrDraw->SetFogEnabled(true);
		AddComponent<AnimationComponent>(L"Player", L"Default");									//!アニメーションの読み込み

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
	//プレイヤーが特定の物体に当たったら
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
		//パワーアップ時の処理
		switch (m_Power)
		{
		case 0:
			wallHp -= MAXWALLDAMAGE;
			m_Power = DEFULT;//!パワーを1にする
			m_powerCount = 0;//!パワー
			m_Gageflash = DEFULT;
			break;
			//パワーアップ前の処理
		case 1:
			wallHp--;
			break;
		}


		//!壁のHpが0以下の時
		if (wallHp <= 0)
		{
			auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
			if (PtrSpark) {
				auto pos = m_transform.lock()->GetPosition();
				PtrSpark->InsertSplash(pos);
				PtrSpark->InsertSpark(pos);
			}

			m_powerCount++;
			//!パワーが最大になったら
			if (m_powerCount >= MAXPOWERCOUNT)
			{
				m_powerCount = MAXPOWERCOUNT;//パワーが最大以上にならないように設定
			}

			auto& BrakeSound = App::GetApp()->GetXAudio2Manager();
			//サウンドの再生
			BrakeSound->Start(L"BrakeWall", 0, LOUDNESS);

		}

		//!壁のHpが0以上の時
		else
		{
			auto& AttackSound = App::GetApp()->GetXAudio2Manager();
			AttackSound->Start(L"AttackWall", 0, LOUDNESS);
		}

		return wallHp;//変更後のhp
	}

	//壁を破壊する
	void Player::BreakWall()
	{
		auto transComp = GetComponent<Transform>();
		auto position = transComp->GetPosition(); // 現在の位置座標を取得する
		SPHERE playerSp(position, PLAYERBREAKESP);

		//壊れる壁のグループの取得
		auto group = GetStage()->GetSharedObjectGroup(L"Wall_Group");
		auto& vec = group->GetGroupVector();

		//壁の破壊処理
		for (auto& v : vec) {
			//グループの１つを取り出す
			auto shPtr = v.lock();
			Vec3 ret;
			//壊れる壁の取得
			auto ptrWall = dynamic_pointer_cast<Wall>(shPtr);
			if (ptrWall) {
				auto wallObb = ptrWall->GetComponent<CollisionObb>()->GetObb();//壊れる壁の衝突判定取得
				auto wallHP = ptrWall->GetHP();                                //壊れる壁のHP取得
                 /*近づいたら*/
				if (HitTest::SPHERE_OBB(playerSp, wallObb, ret)) {
					//壁との距離が2.0以下になった
					auto& ctrlVec = App::GetApp()->GetInputDevice().GetControlerVec();
					ptrWall->SetHP(BrokenWall(wallHP));
				}
			}
		}

	}


	void Player::Enemydistance()
	{
		//アニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();//描画コンポーネントの取得
		auto AnimationName = ptrDraw->GetCurrentAnimation();//現在のアニメーション名を取得する
		auto transComp = GetComponent<Transform>();			//トランスフォームの取得
		auto position = transComp->GetPosition();			// 現在の位置座標を取得する
		auto rotation = transComp->GetRotation();
		//ボスの座標取得
		auto ptrEnemy = GetStage()->GetSharedGameObject<EnemyObject>(L"EnemyObject");
		//クラスには（）が必要である引数があるときと無い時どっちでも必要
		auto EnemyPositon = ptrEnemy->GetComponent<Transform>()->GetPosition();

		//ボスとプレイヤーが一定の距離に達したら
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
			float elapsedTime1 = App::GetApp()->GetElapsedTime();//!エルパソタイムの取得
			m_itemtime += elapsedTime1;
			if (m_itemtime >= MAXITEMTIME)
			{
				m_maxMoveSpeed = DEFAULTSPEED;//!アイテム使用前のスピードに戻す
			}
		}
	}
	
	void Player::PlayerAction()
	{

		//アニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		auto& ptrXA = App::GetApp()->GetXAudio2Manager();
		auto AnimationNow = ptrDraw->UpdateAnimation(elapsedTime);	//現在のアニメーションが終了したら、true
		auto& ActionName = ptrDraw->GetCurrentAnimation();

		if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPullのときこのif文に入ったら、ChangeCurrentAnimationをActionPuhにする
				ptrDraw->ChangeCurrentAnimation(L"ActionPush");
				ptrXA->Start(L"Hammer", 0, LOUDNESS);
				//プレイヤーが壁を壊す処理
				BreakWall();
				
				//プレイヤーが攻撃をしている
				m_playerAttack = true;
				return;
			}
		}

		//攻撃処理
		else if (ActionName == L"ActionPull") {
			if (ptrDraw->IsTargetAnimeEnd()) {
				//ActionPushのときこのif文に入ったら、ChangeCurrentAnimationをActionPuhにする
				ptrDraw->ChangeCurrentAnimation(L"Default");
				auto ptrXA = App::GetApp()->GetXAudio2Manager();
				//サウンドの再生
				ptrXA->Start(L"Hammer", 0, LOUDNESS);
			}
		}

		else {
			if (AnimationNow) {
				ptrDraw->ChangeCurrentAnimation(L"Default");
				ptrXA->Stop(m_BGM);
				//プレイヤーが攻撃し終えた
				m_playerAttack = false;
				m_moveStop = true;//移動停止解除

			}
		}

	}

	void Player::OpeningCamera()
	{
		if (m_opningCamera == true)
		{
			auto ptrGameStage = dynamic_pointer_cast<GameStage>(GetStage());
			float elapsedTime = App::GetApp()->GetElapsedTime();
			m_moveStop = false;//!オープニングカメラを止める
			m_opningStop += elapsedTime;
			if (m_opningStop >= XM_PI) {
				m_opningCamera = false;//!オープニングカメラを追える
				m_moveStop = true;//プレイヤーの動きを解放する
			}
			
		}
		
		
	}

	void Player::PlayerMove()
	{

		// アプリケーションオブジェクトを取得する
		auto& app = App::GetApp();
		// デルタタイムを取得する
		float delta = app->GetElapsedTime(); // 前フレームからの「経過時間」
		// カメラを取得する
		auto stage = GetStage(); // このオブジェクトが追加されているステージ
		auto& camera = stage->GetView()->GetTargetCamera(); // カメラを取得する
		// カメラの回り込み
		float rad = XM_PI * 0.5f;

		// ゲームコントローラーオブジェクトを取得する
		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0]; // ゼロ番目のコントローラーを取得する
		m_moveDir = Vec3(pad.fThumbLX, 0.0f, pad.fThumbLY); // 大きさが 0.0f ～ 1.0f;
		auto m = Mat3x3( // Y軸中心で回転させる行列
			Vec3(cosf(rad), 0.0f, sinf(rad)),   // X軸の向き
			Vec3(0.0f, 0.0f, 0.0f),   // Y軸の向き
			Vec3(-sinf(rad), 0.0f, cosf(rad))); // Z軸の向き
		m_moveDir = m_moveDir * m; // スティックの入力をangleYラジアン回転させる
		m_speed = m_maxMoveSpeed * m_moveDir.length() * m_moveStop; // 最大速×スティックベクトルの大きさ×停止させるかどうかの判定
		m_moveDir.normalize(); // 移動方向を正規化する
		auto transComp = m_transform.lock();
		auto position = transComp->GetPosition(); // 現在の位置座標を取得する
		auto rotation = transComp->GetRotation();
		auto scale = transComp->GetScale();

		// プレイヤーの移動
		position += m_moveDir * m_speed * delta; // デルタタイムを掛けて「秒間」の移動量に変換する
		transComp->SetPosition(position); // 更新した値で再設定する


	}

	void Player::WalkAnimation()
	{
		auto transComp = m_transform.lock();
		float elapsedTime = App::GetApp()->GetElapsedTime();
		//アニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& AnimationName = ptrDraw->GetCurrentAnimation();

		if (m_speed > 0.0f) // スティックが倒れていたら・・
		{
			float rotY = atan2f(-m_moveDir.z, m_moveDir.x); // アークタンジェントを使うとベクトルを角度に変換できる
			transComp->SetRotation(0.0f, rotY, 0.0f); // ラジアン角で設定
			//歩くアニメーション
			if (AnimationName == L"Default") {
				ptrDraw->ChangeCurrentAnimation(L"Move");
				//サウンドの再生
				auto& ptrXA = App::GetApp()->GetXAudio2Manager();
				m_BGM = ptrXA->Start(L"run", 0, LOUDNESS);
			}
		}
		else {
			//立ち止まるアニメーション
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

		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());
		m_InputHandler2.PushHandle(GetThis<Player>());
		if (ptrGameStage->GetCameraSelect() == CameraSelect::openingCamera) {
			return;
		}
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());

	}
	
	//Aボタン
	void Player::OnPushA() 
	{
		//ハンマーを振るアニメーション
		auto ptrDraw = GetComponent<BcPNTnTBoneModelDraw>();
		auto& action = ptrDraw->GetCurrentAnimation();

		if (action != L"ActionPull") {
			ptrDraw->ChangeCurrentAnimation(L"ActionPull");

			auto& ptrXA = App::GetApp()->GetXAudio2Manager();
			ptrXA->Stop(m_BGM);//bgm(足音の停止)

			m_moveStop = false;//移動の停止
		}
	}


	
	void Player::OnPushY() {
		auto PtrSpark = GetStage()->GetSharedGameObject<InsertEffect>(L"MultiEffect", false);
		auto& PowerUpSound = App::GetApp()->GetXAudio2Manager();
		//ゲージが溜まったら
		if (m_powerCount >= MAXPOWERCOUNT)
		{
			auto pos = GetComponent<Transform>()->GetPosition();
			PowerUpSound->Start(L"PowerUp", 0, LOUDNESS);
			m_Power = 0;
			PtrSpark->InsertPowerUp(pos);
		}
	}

	//Xボタン
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
			//サウンドの再生
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
		//コントローラチェックして入力があればコマンド呼び出し
		m_InputHandler.PushHandle(GetThis<Player>());

		//!柱を壊せのテロップ
		if (pos.x < TELOPSECONDPLAYERPOSITION) {
			auto ptrStage1 = GetStage()->GetSharedGameObject<Telop>(L"Telop");
			ptrStage1->SetDrawActive(true);
			// 時間の変数に足す
			m_TelopTime += elapsedTime;
			if (m_TelopTime >= MAXTELOPTIME)
			{
				// 1秒後に表示がオフになる
				ptrStage1->SetDrawActive(false);

			}
		}

		// 出口テロップ
		if (pos.x < TELOPTREEDPLAYERPOSITION) {
			auto ptrStage3 = GetStage()->GetSharedGameObject<Telop3>(L"Telop3");
			ptrStage3->SetDrawActive(true);
			// 時間の変数に足す
			m_Telop3Time += elapsedTime;
			if (m_Telop3Time >= MAXTELOPTIME)
			{
				// 1秒後に表示がオフになる
				ptrStage3->SetDrawActive(false);

			}
		}
		
		if (Select == 0)
		{
        // 壁を壊せ！！テロップ
		if (pos.x < TELOPFIRSTPLAYERPOSITION) {
			auto ptrStage4 = GetStage()->GetSharedGameObject<Telop4>(L"Telop4");
			ptrStage4->SetDrawActive(true);
			// 時間の変数に足す
			m_Telop4Time += elapsedTime;
			if (m_Telop4Time >= MAXTELOPTIME)
			{
				// 1秒後に表示がオフになる
				ptrStage4->SetDrawActive(false);

			}
		}
		}
		

	}
	void Player::OnDestroy() {
		//BGMのストップ
		auto& PtrXA = App::GetApp()->GetXAudio2Manager();
		PtrXA->Stop(m_BGM);
	}
}
	//end basecross