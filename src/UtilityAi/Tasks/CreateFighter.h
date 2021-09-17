#pragma once
#include "../Village.h"
#include "../Task.h"

class CreateFighter : public Task{
public:
	CreateFighter() {}
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};