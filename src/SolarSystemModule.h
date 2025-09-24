#pragma once

#include "Module/Module.h"

#define SOLAR_SYSTEM_API __declspec(dllexport)

class SOLAR_SYSTEM_API SolarSystemModule : public BHive::Module
{
public:
	void OnInitialize() override;

	void OnShutdown() override;
};
