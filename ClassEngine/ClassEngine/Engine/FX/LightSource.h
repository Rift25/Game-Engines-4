#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <memory>
#include <string>
#include <vector>
#include <glm/glm.hpp>


class LightSource
{
public:
	LightSource(glm::vec3 position_, float ambientValue_, float diffuseValue_, float specularValue_, glm::vec3 lightColour_);
	~LightSource();

	glm::vec3 GetPosition() const;
	float GetAmbientValue() const;
	float GetDiffuseValue() const;
	float GetSpecularValue() const;
	glm::vec3 GetLightColour() const;

	void SetPosition(glm::vec3 position_);
	void SetAmbientValue(float ambientValue_);
	void SetDiffuseValue(float diffuseValue_);
	void SetSpecularValue(float specularValue_);
	void SetLightColour(glm::vec3 lightColour_);


private:
	glm::vec3 position;
	float ambientValue;
	float diffuseValue;
	float specularValue;
	glm::vec3 lightColour;

};

#endif 