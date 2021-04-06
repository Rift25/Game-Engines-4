#include "Mesh.h"

Mesh::Mesh(SubMesh& subMesh_, GLuint shaderProgram_) : VAO(0), VBO(0), shaderProgram(0), modelLoc(0), viewLoc(0), projectionLoc(0),
viewPosition(0), lightPosition(0), lightAmbient(0), lightDiffuse(0), lightSpecular(0), lightColour(0)
{
	subMesh = subMesh_;
	shaderProgram = shaderProgram_;
	GenerateBuffers();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	if (subMesh.vertexList.size() > 0)
	{
		subMesh.vertexList.clear();
	}

	if (subMesh.meshIndices.size() > 0)
	{
		subMesh.meshIndices.clear();
	}
}

void Mesh::Render(Camera* camera_, std::vector<glm::mat4>& instances_)
{
	glUniform1i(diffuseMap, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, subMesh.material.diffuseMap);

	glUniform3fv(viewPosition, 1, glm::value_ptr(camera_->GetPosition()));
	glUniform3fv(lightPosition, 1, glm::value_ptr(camera_->GetlightSourcesList()[0]->GetPosition()));
	glUniform1f(lightAmbient, camera_->GetlightSourcesList()[0]->GetAmbientValue());
	glUniform1f(lightDiffuse, camera_->GetlightSourcesList()[0]->GetDiffuseValue());
	glUniform1f(lightSpecular, camera_->GetlightSourcesList()[0]->GetSpecularValue());
	glUniform3fv(lightColour, 1, glm::value_ptr(camera_->GetlightSourcesList()[0]->GetLightColour()));

	glUniform1f(shininess, subMesh.material.shininess);
	glUniform1f(transparency, subMesh.material.transparency);
	glUniform3fv(ambient, 1, glm::value_ptr(subMesh.material.ambient));
	glUniform3fv(diffuse, 1, glm::value_ptr(subMesh.material.diffuse));
	glUniform3fv(specular, 1, glm::value_ptr(subMesh.material.specular));

	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetView()));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(camera_->GetPerspective()));

	glBindVertexArray(VAO);

	glEnable(GL_DEPTH_TEST);

	for (int i = 0; i < instances_.size(); i++)
	{
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(instances_[i]));
		glDrawArrays(GL_TRIANGLES, 0, subMesh.vertexList.size());
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Mesh::GenerateBuffers()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, subMesh.vertexList.size() * sizeof(Vertex), &subMesh.vertexList[0], GL_STATIC_DRAW);

	//POSITION
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	//NORMAL
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));

	//TEX COORDS
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, textureCoordinates));
	
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	modelLoc = glGetUniformLocation(shaderProgram, "model");
	viewLoc = glGetUniformLocation(shaderProgram, "view");
	projectionLoc = glGetUniformLocation(shaderProgram, "projection");
	viewPosition = glGetUniformLocation(shaderProgram, "viewPosition");
	lightPosition = glGetUniformLocation(shaderProgram, "light.lightPos");
	lightAmbient = glGetUniformLocation(shaderProgram, "light.ambient");
	lightDiffuse = glGetUniformLocation(shaderProgram, "light.diffuse");
	lightSpecular = glGetUniformLocation(shaderProgram, "light.specular");
	lightColour = glGetUniformLocation(shaderProgram, "light.lightColor");
	diffuseMap = glGetUniformLocation(shaderProgram, "material.diffuseMap");
	shininess = glGetUniformLocation(shaderProgram, "material.shininess");
	transparency = glGetUniformLocation(shaderProgram, "material.transparency");
	ambient = glGetUniformLocation(shaderProgram, "material.ambient");
	diffuse = glGetUniformLocation(shaderProgram, "material.diffuse");
	specular = glGetUniformLocation(shaderProgram, "material.specular");
}
