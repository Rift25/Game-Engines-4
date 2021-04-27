#include "CollisionHandler.h"
#include "../Core/CoreEngine.h"

std::unique_ptr<CollisionHandler> CollisionHandler::collisionInstance = nullptr;
std::vector<GameObject*> CollisionHandler::prevCollisions = std::vector<GameObject*>();
OctSpatialPartition* CollisionHandler::scenePartition = nullptr;


CollisionHandler::CollisionHandler()
{
	prevCollisions.reserve(10);
}

CollisionHandler::~CollisionHandler()
{
	OnDestroy();
}

CollisionHandler* CollisionHandler::GetInstance()
{
	if (collisionInstance.get() == nullptr)
	{
		collisionInstance.reset(new CollisionHandler);
	}
	return collisionInstance.get();
}

void CollisionHandler::OnCreate(float worldSize_)
{
	prevCollisions.clear();
	scenePartition = new OctSpatialPartition(worldSize_);
}

void CollisionHandler::AddObject(GameObject* go_)
{
	if (scenePartition != nullptr)
	{	
		scenePartition->AddObject(go_);
	}

}

void CollisionHandler::MouseUpdate(glm::vec2 mousePosition_, int buttonType_)
{
	Ray mouseRay = CollisionDetection::MousePosToWorldRay(mousePosition_,
										CoreEngine::GetInstance()->GetScreenWidth(),
										CoreEngine::GetInstance()->GetScreenHeight(), 
										CoreEngine::GetInstance()->GetCamera());
	GameObject* hitResult = nullptr;
	float shortestDistance = 1000000.0f;
	
	if (scenePartition != nullptr)
	{
		GameObject* hitResult = scenePartition->GetCollision(mouseRay);

		if (hitResult)
		{
			hitResult->SetHit(true, buttonType_);
		}

		for (auto c : prevCollisions)
		{
			if (c != hitResult && c != nullptr)
			{
				c->SetHit(false, buttonType_);
			}
			c = nullptr;
		}
		prevCollisions.clear();

		if (hitResult)
		{
			prevCollisions.push_back(hitResult);
		}
	}
}

void CollisionHandler::OnDestroy()
{
	delete scenePartition;
	scenePartition = nullptr;

	for (auto entry : prevCollisions)
	{
		entry = nullptr;
	}
	prevCollisions.clear();
}


