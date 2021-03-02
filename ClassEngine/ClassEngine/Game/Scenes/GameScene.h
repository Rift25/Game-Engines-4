#ifndef GAMEESCENE_H
#define GAMECENE_H

#include "../../Engine/Core/CoreEngine.h"
class GameScene : public Scene
{
public:
	GameScene();
	virtual ~GameScene();

	bool OnCreate() override;
	void Update(const float deltaTime_) override;
	void Render() override;

private:
	GameObject* shape;
	Model* model;
};

#endif // !STARTSCENE_H