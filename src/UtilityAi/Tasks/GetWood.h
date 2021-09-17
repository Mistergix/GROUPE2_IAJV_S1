#pragma once
#include "../Village.h"
#include "../Task.h"

class GetWood : public Task{
public:
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};