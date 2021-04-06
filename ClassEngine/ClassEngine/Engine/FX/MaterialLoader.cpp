#include "MaterialLoader.h"

MaterialLoader::~MaterialLoader()
{
}


void MaterialLoader::LoadMaterial(std::string filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open MTL file: " + filePath_, "MaterialLoader.cpp", __LINE__);
		return;
	}
	Material m = Material();
	std::string matName = "";
	std::string line;
	while (std::getline(in, line))
	{
		if (line.substr(0, 7) == "newmtl ")
		{
			if (m.diffuseMap != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(7);
			m.diffuseMap = LoadTexture(matName);
			m.name = matName;
		}
		else if (line.substr(0, 2) == "Ns")
		{
			if (m.shininess != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(2);
			m.shininess = LoadTexture(matName);
			m.name = matName;
		}
		else if (line.substr(0, 2) == "d ")
		{
			if (m.transparency != 0)
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(2);
			m.transparency = LoadTexture(matName);
			m.name = matName;
		}
		else if (line.substr(0, 2) == "Ka")
		{
			if (m.ambient != glm::vec3(0.0f, 0.0f, 0.0f))
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(2);
			m.ambient = glm::vec3(LoadTexture(matName));
			m.name = matName;
		}
		else if (line.substr(0, 2) == "Kd")
		{
			if (m.diffuse != glm::vec3(0.0f, 0.0f, 0.0f))
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(2);
			m.diffuse = glm::vec3(LoadTexture(matName));
			m.name = matName;
		}
		else if (line.substr(0, 2) == "Ks")
		{
			if (m.specular != glm::vec3(0.0f, 0.0f, 0.0f))
			{
				MaterialHandler::GetInstance()->AddMaterial(m);
				m = Material();
			}
			matName = line.substr(2);
			m.specular = glm::vec3(LoadTexture(matName));
			m.name = matName;
		}
	}

	if (m.diffuseMap != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();

	if (m.shininess != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();

	if (m.transparency != 0)
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();

	if (m.ambient != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();

	if (m.diffuse != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();

	if (m.specular != glm::vec3(0.0f, 0.0f, 0.0f))
	{
		MaterialHandler::GetInstance()->AddMaterial(m);
	}
	in.close();
}

GLuint MaterialLoader::LoadTexture(std::string fileName_)
{
	GLuint currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	if (currentTexture == 0)
	{
		TextureHandler::GetInstance()->CreateTexture(fileName_, "./Resources/Textures/" + fileName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(fileName_);
	}
	return currentTexture;
}