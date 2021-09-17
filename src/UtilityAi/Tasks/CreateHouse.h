#pragma once
#include "Task.h"
#include "Village.h"
class CreateHouse : public Task {
public:
	void Execute(Village& village);
	void Evaluation(Village& village);
private:
};