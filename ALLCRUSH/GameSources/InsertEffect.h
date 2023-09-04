/*!
@file ImpactSmoke.h
@brief　エフェクト
*/

#pragma once
#include "stdafx.h"

namespace basecross {

	//--------------------------------------------------------------------------------------
	/// 複数のスパーククラス
	//--------------------------------------------------------------------------------------
	class InsertEffect : public MultiParticle {
	public:
		//構築と破棄
		InsertEffect(shared_ptr<Stage>& StagePtr);
		virtual ~InsertEffect();
		//初期化
		virtual void OnCreate() override;
		void InsertSplash(const Vec3& Pos);
		void InsertSpark(const Vec3& Pos);
		void InsertSpeedUp(const Vec3& Pos);
		void InsertImpact(const Vec3& Pos);
		void InsertPowerUp(const Vec3& Pos);

		virtual void OnUpdate() override;

	};


}
// end namespace basecross
