#include "Game1.h"

Game1::Game1() : GameInterface(), currentSceneNum(0), currentScene(nullptr)
{
}

Game1::~Game1()
{
	delete currentScene;
	currentScene = nullptr;
}

bool Game1::OnCreate()
{
	if (CoreEngine::GetInstance()->GetCurrentScene() == 0)
	{
		currentScene = new StartScene();
		currentSceneNum = 0;
		CoreEngine::GetInstance()->SetCurrentScene(1);
		return currentScene->OnCreate();
	}
	std::cout << "Engine's scene is not initialized to 0" << std::endl;
	return false;
	
}

void Game1::Update(const float deltaTime_)
{
	if (currentSceneNum != CoreEngine::GetInstance()->GetCurrentScene())
	{
		BuildScene();
	}
	currentScene->Update(deltaTime_);
}

void Game1::Render()
{
	currentScene->Render();
}

void Game1::BuildScene()
{
	delete currentScene;
	currentScene = nullptr;

	switch (CoreEngine::GetInstance()->GetCurrentScene())
	{
	case 1:
		currentScene = new GameScene();
		break;
	default: //case 0
		currentScene = new StartScene();
		break;
	}

	currentSceneNum = CoreEngine::GetInstance()->GetCurrentScene();
	if (!currentScene->OnCreate())
	{
		std::cout << "Scene failed to be created" << std::endl;
		CoreEngine::GetInstance()->Exit();
	}
}