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
	class ImpactSmoke : public MultiParticle {
	public:
		//構築と破棄
		ImpactSmoke(shared_ptr<Stage>& StagePtr);
		virtual ~ImpactSmoke();
		//初期化
		virtual void OnCreate() override;
		void InsertSpark(const Vec3& Pos);
		void InsertSpark1(const Vec3& Pos);
		void InsertSpark2(const Vec3& Pos);
		void InsertSpark3(const Vec3& Pos);
		void InsertSpark4(const Vec3& Pos);

		virtual void OnUpdate() override;

	};


}
// end namespace basecross
