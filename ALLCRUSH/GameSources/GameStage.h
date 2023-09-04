/*!
@file GameStage.h
@brief 
*/

#pragma once
#include "stdafx.h"


namespace basecross {
	enum class CameraSelect {
		openingCamera,
		myCamera,
	};
	//--------------------------------------------------------------------------------------
	// ゲームステージクラス
	//--------------------------------------------------------------------------------------
	class GameStage : public Stage {
		bool m_createGameOverObjectFlg = false;
	CsvFile m_CsvC;           //CSVファイルそのC

	
	float m_idleTime;         //テロップの表示時間0
	float m_TelopTime;        //テロップの表示時間1
	float m_Telop2Time;       //テロップの表示時間2
	float m_Telop3Time;       //テロップの表示時間3
	float m_Telop4Time;       //テロップの表示時間4
	float m_TotalTime;        //トータル時間
	float m_ExitTime;         //出口からムービーへの移動時間
	int m_Exit;               //出口に触れているか
	
		
	shared_ptr<SingleView> m_OpeningCameraView;//OpeningCamera用のビュー
	shared_ptr<SingleView> m_MyCameraView;     //MyCamera用のビュー
	CameraSelect m_CameraSelect;               //カメラを切り替える
	InputHandler<GameStage> m_InputHandler;    //入力ハンドラー
	ResetHandler<GameStage> ResetHandler;	   //リセットハンドラー
	shared_ptr<SoundItem> m_BGM;               //BGM

	//ビューの作成
	void CreateViewLight();   
	//スパークエフェクト1の作成
	void CreateMultiSpark(); 
	//スパークエフェクト2の作成
	void CreateMultiSpark1(); 
	//柱の作成
	void CreatePillar(); 
	//マヤによるステージの壁作成
	void CreateStageWall();  
	//マヤによるステージの床作成
	void CreateStageFloor(); 
	//壊れる壁の作成
	void CreateWall();      
	//障害物１
	void CreateObstacle1();   
	//障害物2
	void CreateObstacle2();  
	//落石
	void CreateFallingRock(); 
	//トラップの作成
	void CreateTrap();   
	//アイテムスプライト作成
	void CreateMyitem1();  
	//Xボタンスプライトの作成
	void CreateXSprite();
	//Yボタンスプライトの作成
	void CreateYSprite();
	//ゲージの枠の作成
	void CreateMygage();    
	//ゲージのスプライトの作成
	void CreateGageSprite();  
	//ゲージの背景の作成
	void CreateGageWhite();   
	//出口の作成
	void CreateExitWall();    
	//タイム作成
	void CreateTime();    
	//テロップ0
	void CreateTickerSprite();
	//テロップ1
	void CreateTelop();     
	//テロップ2
	void CreateTelop2();  
	//テロップ3
	void CreateTelop3();  
	//テロップ4
	void CreateTelop4(); 
	//プレイヤーの作成
	void CreatePlayer();  
	//BGMの再生1
	void BGM();      
	//音楽を止める
	void OnDestroy();      
	//リセット
	void GameReset();
	//カメラマンの作成
	void CreateCameraman();  
		
	public:
		//構築と破棄
		GameStage() :Stage(),
			m_TotalTime(0),
			m_CameraSelect(),
			m_Exit(0),
			m_TelopTime(0.0f),
			m_Telop2Time(0.0f),
			m_Telop3Time(0.0f),
			m_Telop4Time(0.0f),
			m_idleTime(0.0f),
			m_ExitTime(0.0f)


		{}
		//デストラクタ
		virtual ~GameStage() {}
		//初期化
		virtual void OnCreate()override;
		//更新
		virtual void OnUpdate()override;
		//Aボタンなにもしない
		void OnPushA() {}   
		//スキップボタン
		void OnPushSkip(){}
		//リセットボタン
		void OnPushReset();

		CameraSelect GetCameraSelect() const {
			return m_CameraSelect;
		}
		//カメラ
		void ToMyCamera();
	};

}
//end basecross