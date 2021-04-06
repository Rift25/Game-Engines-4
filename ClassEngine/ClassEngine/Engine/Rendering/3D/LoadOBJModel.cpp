#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel() : vertices(std::vector <glm::vec3>()), normals(std::vector < glm::vec3>()), textureCoords(std::vector<glm::vec2>()), indices(std::vector<unsigned int>()),
	normalIndices(std::vector<unsigned int>()), textureIndices(std::vector<unsigned int>()), meshVertices(std::vector<Vertex>()), subMeshes(std::vector<SubMesh>()), currentMaterial(Material())
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureCoords.clear();
	meshVertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in)
	{
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}
	std::string line;

	while (std::getline(in, line))
	{
		//VERTEX DATA
		if (line.substr(0, 2) == "v ")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
		}
		//TEXTURE DATA
		else if (line.substr(0, 2) == "vt")
		{
			std::stringstream v(line.substr(2));
			float x, y;
			v >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		//NORMAL DATA
		else if (line.substr(0, 2) == "vn")
		{
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}
		//FACE DATA
		else if (line.substr(0, 2) == "f ")
		{
			std::stringstream v(line.substr(2));
			unsigned int vertexIndex[3], textureIndex[3], normalIndex[3];
			char slash;

			v >> vertexIndex[0] >> slash >> textureIndex[0] >> slash >> normalIndex[0] >>
				vertexIndex[1] >> slash >> textureIndex[1] >> slash >> normalIndex[1] >>
				vertexIndex[2] >> slash >> textureIndex[2] >> slash >> normalIndex[2];

			indices.push_back(vertexIndex[0] - 1);
			indices.push_back(vertexIndex[1] - 1);
			indices.push_back(vertexIndex[2] - 1);

			textureIndices.push_back(textureIndex[0] - 1);
			textureIndices.push_back(textureIndex[1] - 1);
			textureIndices.push_back(textureIndex[2] - 1);
			
			normalIndices.push_back(normalIndex[0] - 1);
			normalIndices.push_back(normalIndex[1] - 1);
			normalIndices.push_back(normalIndex[2] - 1);
		}
		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ")
		{
			if (indices.size() > 0)
			{
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}
	}
	in.close();
	PostProcessing();
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++)
	{
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
	
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}