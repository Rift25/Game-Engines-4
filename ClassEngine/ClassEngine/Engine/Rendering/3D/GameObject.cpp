#include "GameObject.h"

GameObject::GameObject(Model* model_) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = model_;
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::GameObject(Model* model_, glm::vec3 position_) : model(nullptr), position(glm::vec3()), angle(0.0f), rotation(glm::vec3(0.0f, 1.0f, 0.0f)), scale(glm::vec3(1.0f)), modelInstance(0)
{
	model = model_;
	position = position_;
	if (model)
	{
		modelInstance = model->CreateInstance(position, angle, rotation, scale);
	}
}

GameObject::~GameObject()
{
	if (model)
	{
		delete model;
	}
	model = nullptr;
}

void GameObject::Update(const float deltaTime_)
{
	SetAngle(angle + 0.005f);
}

void GameObject::Render(Camera* camera_)
{
	if (model)
	{
		model->Render(camera_);
	}
}

glm::vec3 GameObject::GetPosition() const
{
	return position;
}

float GameObject::GetAngle() const
{
	return angle;
}

glm::vec3 GameObject::GetRotation() const
{
	return rotation;
}

glm::vec3 GameObject::GetScale() const
{
	return scale;
}

void GameObject::SetPosition(glm::vec3 position_)
{
	position = position_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetAngle(float angle_)
{
	angle = angle_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetRotation(glm::vec3 rotation_)
{
	rotation = rotation_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}

void GameObject::SetScale(glm::vec3 scale_)
{
	scale = scale_;
	if (model)
	{
		model->UpdateInstance(modelInstance, position, angle, rotation, scale);
	}
}