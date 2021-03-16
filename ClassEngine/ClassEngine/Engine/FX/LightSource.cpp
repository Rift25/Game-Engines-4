#include "LightSource.h"


LightSource::LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, float specularValue_, glm::vec3 lightColour_) : position(glm::vec3()), ambientValue(0.0f), diffuseValue(0.0f), specularValue(0.0f), lightColour(glm::vec3())
{
	position = position_;
	ambientValue = ambientValue_;
	diffuseValue = diffuseValue_;
	specularValue = specularValue_;
	lightColour = lightColour_;
}

LightSource::~LightSource()
{
}

glm::vec3 LightSource::GetPosition() const
{
	return position;
}

float LightSource::GetAmbientValue() const
{
	return ambientValue;
}

float LightSource::GetDiffuseValue() const
{
	return diffuseValue;
}

float LightSource::GetSpecularValue() const
{
	return specularValue;
}

glm::vec3 LightSource::GetLightColour() const
{
	return lightColour;
}

void LightSource::SetPosition(glm::vec3 position_)
{
	position = position_;
}

void LightSource::SetAmbientValue(float ambientValue_)
{
	ambientValue = ambientValue_;
}

void LightSource::SetDiffuseValue(float diffuseValue_)
{
	diffuseValue = diffuseValue_;
}

void LightSource::SetSpecularValue(float specularValue_)
{
	specularValue = specularValue_;
}

void LightSource::SetLightColour(glm::vec3 lightColour_)
{
	lightColour = lightColour_;
}