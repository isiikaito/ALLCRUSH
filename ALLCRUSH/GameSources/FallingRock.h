/**
*@file FallingRock.h
*@brief 落石オブジェクトの実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details 落石オブジェクトの実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"
/** basecross共通のネームスペース */
namespace basecross {

	class FallingRock : public GameObject {
		bool m_Falling;	//落ちる判定
		StaticModelDeta m_fallingRockModelData;//!落石のモデルデータ

	public:

		/**
		* コンストラクタ
		*/
		FallingRock(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

        /**
　　　　* デストラクタ
　　　　*/
		virtual ~FallingRock() {}

		
		/**
		* 落石オブジェクトの初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

		/**
		* 柱オブジェクトが破壊されたときに落石が落ちる関数
		*/
		virtual void OnUpdate() override;
		
		/**
         * 柱オブジェクトが破壊されたかどうか
         * @return int 柱オブジェクトがステージ上に存在するかどうかが返ってくる
         */
		bool GetFalling()const {
			return m_Falling;
		}

		/**
		 * 柱オブジェクトが破壊されたかどうか
		 * @param[in] int  Falling ステージ上で破壊されtかどうか
		 */
		void SetFalling(bool Falling) {
			m_Falling = Falling;
		}
	};
}
