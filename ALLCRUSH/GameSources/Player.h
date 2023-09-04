/**
* @file Player.h
* @brief プレイヤークラスの定義が記述されているヘッダーファイル
*/

#pragma once
#include "stdafx.h"
#include "BoneModelComponent.h"
/** basecross共通のネームスペース */
namespace basecross{
	enum class  GameState {
		Game,
		Down,
		FadeStart,
		FadeOut,
		ChangeStage,
		GameExit
	};

	/** プレイヤーの操作・状態・その他*/
	class Player : public GameObject
	{
		float m_maxMoveSpeed;				//移動の最大速
		bool m_moveStop;							//Playerの移動停止の判定(trueなら移動可能,falseなら移動停止)
		Vec3 m_moveDir;							//移動方向ベクトル（単位ベクトル）
		float m_EndPos;							//ゲームオーバー時のプレイヤー座標
		float m_EndAngle;							//ゲームオーバー時のプレイヤーの向き
		float m_speed;							//移動の速さ
		float m_accel;							//加速度
		int m_gameOver;							//ゲームオーバーを判定する
		bool m_itemCondition;					//アイテムを持っているかどうか
		bool m_itemDisplay;						//アイテムの効果を発揮しているかどうか
		float m_itemtime;							//アイテムの持続時間
		int m_powerCount;							//パワーアップアイテム
		bool m_pillarCount;						//柱が壊れているかどうか
		int m_ExitCount;							//出口にぶつかった
	    float m_PBdistance;						//プレイヤーとボスとの距離
		float m_TurnTime;						//振り向きから直るまでの時間
		int m_Power;								//パワーアップがあるかないか
		int m_Gageflash;							//パワーアップを使ったかどうか
		bool m_Trapdecision;					//トラップに当たったかどうか
		GameState m_State;						//ゲームオーバー用のステート
		bool m_Event;							//柱のイベントを行うかどうか
		float m_TelopTime;						//テロップ
		float m_Telop2Time;						//テロップ2	
		float m_Telop3Time;						//テロップ3
		float m_Telop4Time;						//テロップ4
        float m_opningStop;						//オープニング
		bool m_playerAttack;					//プレイヤーがアタックしているかどうか
		bool m_opningCamera;					//カメラを切り替えたかどうか
		std::weak_ptr<Transform> m_transform;	//トランスフォーム
		BoneModelDeta m_playerBoneModelDeta;	//!敵のモデルデータ

		InputHandler<Player> m_InputHandler;  //コントローラーのボタンの取得1
		InputHandler2<Player> m_InputHandler2;//コントローラーのボタンの取得2
		shared_ptr<SoundItem> m_BGM;          //BGMの取得
	
		//テロップを出す
		void TelopManager();
		//壁を壊す処理
		void BreakWall();
		//プレイヤーとボスとの距離
		void Enemydistance();
		//!アイテムを使った後にスピードを戻す処理
		void ItemDisplay();
		//プレイヤーアクション
		void PlayerAction();
		//コントローラーの処理
		void PlayerMove();
		//歩くアニメーション
		void WalkAnimation();
		//コントローラーの判定
		void ControllerCheck();
		//壁が壊れた後の処理
		int BrokenWall(int wallHp);

	public:

		// ステージを渡せるコンストラクタが必須
		Player(const std::shared_ptr<Stage>& stage)
			: GameObject(stage),//ステージは親クラスに投げる
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

		//コントローラーのボタン判定X
		void OnPushX(); 
		//コントローラーのボタン判定A
		void OnPushA(); 
		//コントローラーのボタン判定十字キー上
		void OnPushUP() {}    
		//コントローラーのボタン判定十字キー下
		void OnPushDOWN(){}  
		//コントローラーのボタン判定Y
		void OnPushY();   
		//コントローラーのボタン判定B
		void OnPushB() {}   
		//オブジェクトの初期化用関数（UnityのStart関数）
		void OnCreate() override; 
		//オブジェクトのフレームごとの処理（UnityのUpdate関数）
		void OnUpdate() override; 
		//BGMを止める
        void OnDestroy();  
		
		//オープニングカメラ
		void OpeningCamera();     
		//敵の攻撃にぶつかったとき
		virtual void OnCollisionEnter(shared_ptr<GameObject>& Other);
		
		
		//柱が壊れているか判定の取得
		//return 柱が壊れてリるかどうかの取得
		bool GetPillarCount()const {
			return m_pillarCount;
		}
		//柱が壊れているか判定の設定
		//引数 柱が壊れてリるかどうか
		void SetPillarCount(bool PillarCount) {
			PillarCount = PillarCount;
		}

		//壁を殴った回数の取得
		//return 壁を殴った回数の取得
		int GetPowerCount()const {
			return m_powerCount;
		}
		//壁を殴った回数の設定
		//引数 壁を殴った回数
		void SetPowerCount(int PowerCount)
		{
			PowerCount = PowerCount;
		}

		//現在攻撃モーションになっているかどうか
		//return 現在攻撃モーションになっているかどうかの取得
		bool GetPlayerAttack()
		{
			return m_playerAttack;
		}

		//現在攻撃モーションになっているかどうかの設定
		//引数 現在攻撃モーションになっているかどうか
		void SetItemCondition(bool itemCondition)
		{
			m_itemCondition = itemCondition;
		}
		
		//パワーアップの取得
		//return パワーアップの取得
		int GetPower() const {
			return m_Power;
		}
		//パワーアップの設定
		//引数 パワーアップの
		void SetPower(int Power)
		{
			Power = Power;
		}

		//パワーアップを使ったかどうか判定する
		//return パワーアップを使ったかどうか
		int GetGageflash() const {
			return m_Gageflash;
		}
		//パワーアップを使ったかどうか判定する
		//引数 パワーアップを使ったかどうか
		void SetGageflash(int Gageflash)
		{
			Gageflash = Gageflash;
		}

		//出口に当たったかどうかの取得
		//return 出口に当たったかどうか
		int GetExitCount() const {
			return m_ExitCount;
		}

		//出口に当たったかどうかの設定
		//引数 出口に当たったかどうか
		void SetExitCount(int ExitCount)
		{
			ExitCount = ExitCount;
		}

		//柱イベントが発生したかどうかの取得
		//return 柱イベントが発生したかどう
		bool GetPEvent()const {
			return m_Event;
		}

		//柱イベントが発生したかどうかの設定
		//引数 柱イベントが発生したかどうか
		void SetPEvent(bool m_Event)
		{
			m_Event = m_Event;
		}

		//ゲームオーバー判定の判定
		//return ゲームオーバー判定の判定
		int GetGameOver()const {
			return m_gameOver;
		}

		//ゲームオーバー判定の判定の設定
		//引数 ゲームオーバー判定の判定
		void SetGameOver(int GameOver) {
			GameOver = GameOver;
		}

		//ステージを切り替えの取得
		//return ステージを切り替えの
		GameState GetGameState() const
		{
			return m_State;
		}

		//ステージを切り替えの設定
		//引数 ステージを切り替え
		void SetGameState(GameState s) {
			m_State = s;
		}

	};
}
//end basecross

