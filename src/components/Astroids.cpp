#include "Astroids.h"
#include "world/components/InstancedStaticMeshComponent.h"

BEGIN_NAMESPACE(BHive)

float GetRandomDisplacement(float offset)
{
	return (rand() % (int)(2 * offset * 100)) / 100.f - offset;
}


Astroids::Astroids(const entt::entity& handle, World* world)
	:GameObject(handle, world)
{
	AddComponent<InstancedStaticMeshComponent>();
}

void Astroids::Save(cereal::BinaryOutputArchive& ar) const
{
	GameObject::Save(ar);

	ar(mCreateAstroidsData);
}

void Astroids::Load(cereal::BinaryInputArchive& ar)
{
	GameObject::Load(ar);

	ar(mCreateAstroidsData);

	CalculateMatrices();

}

void Astroids::SetAstroidsData(const FAstroidData& data)
{
	mCreateAstroidsData = data;
	CalculateMatrices();
}

void Astroids::CalculateMatrices()
{
	const auto& count = glm::max(mCreateAstroidsData.Instances, (uint32_t)0);

	std::vector<FTransform> transforms(count);

	const float& radius = mCreateAstroidsData.Radius;
	const float& offset = mCreateAstroidsData.Offset;
	srand(mCreateAstroidsData.Seed);

	const auto& base_matrix = mCreateAstroidsData.BaseTransform;
	for (uint32_t i = 0; i < count; i++)
	{
		glm::mat4 model = glm::mat4(1.0f);
		float angle = (float)i / (float)count * 360.f;
		float displacement = GetRandomDisplacement(offset);
		float x = sin(angle) * radius + displacement;
		displacement = GetRandomDisplacement(offset);
		float y = displacement * 0.4f;
		displacement = GetRandomDisplacement(offset);
		float z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		float scale = float(rand() / RAND_MAX) + 0.01f;
		model = glm::scale(model, glm::vec3(scale));

		float rot = (float)(rand() % 360);
		model = glm::rotate(model, rot, glm::vec3(0.4f, 0.6f, 0.8f));

		transforms[i] = model * base_matrix.to_mat4();

	}

	GetComponent<InstancedStaticMeshComponent>()->SetInstances(transforms);
}

REFLECT(Astroids)
{
	{
		BEGIN_REFLECT(FAstroidData)
			REFLECT_PROPERTY(Seed)
			REFLECT_PROPERTY(Instances)
			REFLECT_PROPERTY(Radius)
			REFLECT_PROPERTY(Offset)
			REFLECT_PROPERTY(BaseTransform);
	}
	{
		BEGIN_REFLECT(Astroids)(META_DATA(EClassMetaData::ClassMetaData_Spawnable, true))
			REFLECT_CONSTRUCTOR(const entt::entity&, World*)REFLECT_PROPERTY("Astroids", GetAstroidsData, SetAstroidsData);
	}
}

END_NAMESPACE