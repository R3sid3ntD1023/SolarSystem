#pragma once

#include "SolarSystemModule.h"
#include "world/GameObject.h"

BEGIN_NAMESPACE(BHive)

struct SOLAR_SYSTEM_API FAstroidData
{
	uint32_t Seed = 0;
	uint32_t Instances = 0;
	float Radius = 100.f;
	float Offset = 2.5f;
	FTransform BaseTransform;

	template<typename A>
	void Serialize(A& ar)
	{
		ar(Seed, Instances, Radius, Offset, BaseTransform);
	}
};

class SOLAR_SYSTEM_API Astroids : public GameObject
{
public:
	Astroids(const entt::entity& handle, World* world);

	virtual void Save(cereal::BinaryOutputArchive& ar) const override;

	virtual void Load(cereal::BinaryInputArchive& ar) override;

	void SetAstroidsData(const FAstroidData& data);

	const FAstroidData& GetAstroidsData() const { return mCreateAstroidsData; }

	REFLECTABLEV(GameObject)

private:
	void CalculateMatrices();

	FAstroidData mCreateAstroidsData;

};

REFLECT_EXTERN(Astroids)

END_NAMESPACE