#pragma once
#include "../Village.h"
#include "../Task.h"

class CreateVillager : public Task{
public:
	CreateVillager(){}
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};