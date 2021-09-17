#pragma once
#include "../Task.h"
#include "../Village.h"
class GetFood : public Task {
public:
	void Execute(Village& village) const override;
	float Evaluation(Village& village) const override;
private:
};