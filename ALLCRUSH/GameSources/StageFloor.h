/**
*@file StageFloor.h
*@brief ゲームステージの床の実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details ゲームステージの床の実装
*/
#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"
/** basecross共通のネームスペース */
namespace basecross {

	class StageFloor : public GameObject {
		StaticModelDeta m_floorModelData;//!床のモデルデータ

	public:
		/**
		* コンストラクタ
		*/
		StageFloor(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~StageFloor() {}

		/**
		* ゲームステージの床の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

	};
}

