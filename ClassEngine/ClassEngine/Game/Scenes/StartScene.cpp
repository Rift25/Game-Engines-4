#include "StartScene.h"

StartScene::StartScene()
{
}


StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	CoreEngine::GetInstance()->SetCurrentScene(1);
	std::cout << "start scene" << std::endl;
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}