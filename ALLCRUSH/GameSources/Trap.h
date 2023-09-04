/**
*@file Trap.h
*@briefトラップが定義されているヘッダーファイル
*@author Kaito Isii
*@details トラップの実装
*/

#pragma once
#include "stdafx.h"

/** basecross共通のネームスペース */
namespace basecross {

	class Trap : public GameObject {
		Vec3 m_Scale;   //!大きさ
		Vec3 m_Rotation;//!回転
		Vec3 m_Position;//!位置
	public:

		/**
		* コンストラクタ
		*/
		Trap(const shared_ptr<Stage>& StagePtr, const Vec3& Scale, const Vec3& Rotation, const Vec3& Position);

		/**
　　　　* デストラクタ
　　　　*/
		virtual ~Trap() {}

		/**
		* 出口の壁の初期パラメータを初期化する関数
		*/
		virtual void OnCreate() override;

	};
}

