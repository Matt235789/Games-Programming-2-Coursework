#pragma once
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct sphere
{
	sphere();
public:
	sphere(glm::vec3& pos, float & radius)
	{
		this->position = pos;
		this->radius = radius;
	}

	//get the position and radius of the spheres
	inline glm::vec3* Getpos() { return &position; }
	inline float* Getradius() { return &radius; }

	//sets the position and radius of the spheres
	inline void Setpos(glm::vec3& pos) { this->position = pos; }
	inline void Setradius(float& radius) { this->radius = radius; }

private:
	glm::vec3 position; //position of the shpere
	float radius; //float to hold the radius of sphere

};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void draw();
	void init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	void loadModel(const std::string& filename);
	void initModel(const IndexedModel& model);

	glm::vec3* shperepos() { return this->meshSphere.Getpos(); }
	float* radius() { return this->meshSphere.Getradius(); }

	void updateTheSphere(glm::vec3& pos, float radius);
	

private:



	enum
	{
		POSITION_VERTEXBUFFER,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFERS
	};

	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[NUM_BUFFERS]; // create our array of buffers
	unsigned int drawCount; //how much of the vertexArrayObject do we want to draw

	sphere meshSphere;

};

