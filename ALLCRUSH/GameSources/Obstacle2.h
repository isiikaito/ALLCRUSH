/**
*@file Obstacle2.h
*@brief 障害物オブジェクトの実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details 障害物オブジェクトの実装
*/
#pragma once
#include "stdafx.h"

/** basecross共通のネームスペース */
namespace basecross {

	class Obstacle2 : public GameObject {
		StaticModelDeta m_obstacleModelData;			//!障害物のモデルデータ
	public:
		/**
	    * コンストラクタ
	    */
		Obstacle2(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Obstacle2() {}

		/**
		* 障害物オブジェクトの初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

		/**
		* 障害物オブジェクトの更新をする関数
		*/
		virtual void OnUpdate() override;

	};
}
