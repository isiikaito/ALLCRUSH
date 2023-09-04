/*!
@file Wall.h
@brief 壁の実体
*@author Kaito Isii
*/

#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"
namespace basecross {

	class Wall : public GameObject {
		
		int m_HP;										//壁のHP
		StaticModelDeta m_wallModelData;				//!壁のモデルデータ
		Vec3 m_playerPos;								//プレイヤーの座標
		Vec3 m_cameraPos;								//カメラの座標
		Vec3 modelScale;								//!メッシュの大きさ
		Vec3 modelRotOrigin;							//!回転の起源
		Vec3 modelRotation;								//!メッシュの回転
		Vec3 modelPosition;								//!メッシュの位置
		weak_ptr<Transform> m_palyerTransform;			//プレイヤ―のトランスフォーム
		weak_ptr<PNTStaticModelDraw> m_wallModelDraw;	//壁のモデルの描画データ
		InputHandler2<Wall> m_InputHandler;				//入力ハンドラー

		void WallChangeMesh(wstring meshName);					//!壁のメッシュの変更
	public:
		//構築と破棄
		Wall(const shared_ptr<Stage>& StagePtr,
			const Vec3& Scale,
			const Vec3& Rotation,
			const Vec3& Position,
			const int HP
		);
		
		//初期化
		virtual void OnCreate() override;

		//コントローラーのボタン判定X
		void OnPushX(){}
		//コントローラーのボタン判定A
		void OnPushA() {}   
		//コントローラーのボタン判定十字キー上
		void OnPushUP() {}  
		//コントローラーのボタン判定十字キー下
		void OnPushDOWN() {} 
		//コントローラーのボタン判定Y
		void OnPushY(){}     
		//コントローラーのボタン判定B
		void OnPushB(){}     
		//更新
		void OnUpdate();

		//HPの取得
		int GetHP()const {
			return m_HP;
		}
		//HPの管理
		void SetHP(int HP) {
			m_HP = HP;
		}
	};

}
// namespace basecross
