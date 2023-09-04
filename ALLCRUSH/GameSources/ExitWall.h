/**
*@file ExitWall.h
*@brief 出口の壁の実装が定義されているヘッダーファイル
*@author Kaito Isii
*@details 出口の壁の実装
*/

#pragma once
#include "stdafx.h"
#include "StaticModelComponent.h"

/** basecross共通のネームスペース */
namespace basecross {

	class ExitWall : public GameObject {
		StaticModelDeta m_exitWallModelData;//!出口のモデルデータ

	public:

		/**
		* コンストラクタ
		*/
		ExitWall(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~ExitWall() {}

		/**
		* 出口の壁の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

	};
}
