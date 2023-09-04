/**
* @file MyCamera.cpp
* @brief カメラクラスの定義が記述されているソースファイル
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {

	constexpr float MAXDISTANCE = 5.0f;//!柱とプレイヤーの近づいた判定の最大距離
	constexpr float TURNTIME = 4.0f;//!振り向いている時間
	constexpr float EYEPOSY = 2.0f;//!カメラのy位置
	constexpr float PLAYERPOSY = 0.5f;//!プレイヤーの
	constexpr int ENEMYSETDRAWACTIVECOUNT = 1;//!敵の表示をするかどうか
	constexpr float ENEMYPAYERDISTANCE = -3.0f;//!敵とプレイヤーの距離
	constexpr float PLAYERPOSX = 5.0f;//!Bボタンを押したときのプレイヤーの位置を引く値

	shared_ptr<GameObject> MyCamera::GetTargetObject() const {
		if (!m_TargetObject.expired()) {
			return m_TargetObject.lock();
		}
		return nullptr;
	}

	void MyCamera::SetTargetObject(const shared_ptr<GameObject>& Obj) {
		m_TargetObject = Obj;
	}

	// カメラ
	void MyCamera::OnUpdate()
	{
		auto& app = App::GetApp();

		float delta = app->GetElapsedTime();

		auto& device = app->GetInputDevice();
		const auto& pad = device.GetControlerVec()[0];


		// プレイヤーの座標を取得する
		Vec3 playerPos(0.0f); // プレイヤーの座標（仮）
		Vec3 pillarPos(0.0f);
		Vec3 enemyPos(0.0f);//敵の座標（仮）
		int EnemySetDrawActiveCount(0);
		int PillarCount(0);
		auto stage = app->GetScene<Scene>()->GetActiveStage(); // ステージオブジェクトを取得する
		auto objs = stage->GetGameObjectVec(); // ステージに追加されているすべてのオブジェクト
		for (auto& obj : objs)
		{
			// プレイヤーへのキャストを試みる
			auto player = dynamic_pointer_cast<Player>(obj);
			auto pillar = dynamic_pointer_cast<Pillar>(obj);
			auto Enemy = dynamic_pointer_cast<EnemyObject>(obj);
			if (player)
			{
				// キャストに成功していたら座標を取得する
				auto playerTrans = player->GetComponent<Transform>();
				playerPos = playerTrans->GetPosition();
				PillarCount = player->GetPillarCount();
				player->SetPillarCount(PillarCount);
			}

			// 柱へのキャストを試みる
			else if (pillar)
			{
				// キャストに成功していたら座標を取得する
				auto pillarTrans = pillar->GetComponent<Transform>();
				pillarPos = pillarTrans->GetPosition();
			}
			//ボスへのキャストを試みる
			else if (Enemy)
			{
				EnemySetDrawActiveCount = Enemy->GetEnemySetDrawActiveCount();
				Enemy->SetEnemySetDrawActiveCount(EnemySetDrawActiveCount);
				enemyPos = Enemy->GetComponent<Transform>()->GetPosition();
			}
			
		}

		float ed = playerPos.x - enemyPos.x;//プレイヤーとエネミーの距離

		auto eye = playerPos + Vec3(cosf(0.0f), 0.0f, sinf(0.0f)) * distance;
		eye.y = EYEPOSY;
		playerPos.y = PLAYERPOSY;


		auto& cntlVec = App::GetApp()->GetInputDevice().GetControlerVec();
		if (cntlVec[0].wButtons & XINPUT_GAMEPAD_B|| ed >= ENEMYPAYERDISTANCE)
		{
			eye.x = playerPos.x - PLAYERPOSX;
		}


		SetEye(eye);
		SetAt(playerPos); // プレイヤーを中止するようにする

		//プレイヤーと柱の距離
		PPdistance = playerPos.x - pillarPos.x;
		//プレイヤーと柱の位置が一定の距離になったら振り返る
		auto  Select = App::GetApp()->GetScene<Scene>()->GetStageSelect();

		//sutge1の時
		if (Select == 0)
		{
			//柱が存在するとき
			if (m_Turn == true)
			{
				//柱とプレイヤーの距離が5以下になったら
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

			//柱が壊れたら
			if (m_front)
			{

				//elapsedTimeを取得することにより時間を使える
				float elapsedTime = App::GetApp()->GetElapsedTime();
				//時間を変数に足す
				m_TurnTime += elapsedTime;
				//柱が壊れてから二秒後に
				if (m_TurnTime > TURNTIME && m_TurnTime < TURNTIME+0.1f)
				{
					EnemySetDrawActiveCount = ENEMYSETDRAWACTIVECOUNT;
					//カメラが正面を向く
					auto eye = playerPos + Vec3(cosf(angleY), 0.0f, sinf(angleY)) * distance; // プレイヤーの座標を中心に、angleY分回り込む（プレイヤーからの距離はdistance）
					eye.y = EYEPOSY;
					playerPos.y = PLAYERPOSY;

					m_Turn = false;

					SetEye(eye);
					SetAt(playerPos); // プレイヤーを注視するようにする

				}
			}
		}
	}

	//--------------------------------------------------------------------------------------
	//	オープニングカメラ（コンポーネントではない）
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
	//	メインカメラ（コンポーネントではない）
	//--------------------------------------------------------------------------------------
	//構築と破棄
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