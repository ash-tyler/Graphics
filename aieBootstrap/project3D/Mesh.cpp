#include "Mesh.h"
#include <gl_core_4_4.h>


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}


void Mesh::initialise(unsigned int vertexCount,	const Vertex* vertices,	unsigned int indexCount /* = 0 */, unsigned int* indices /* = nullptr*/)
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);	glDisableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,	sizeof(Vertex), (void*)32);	if (indexCount != 0) 
	{
		glGenBuffers(1, &ibo);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		triCount = indexCount / 3;
	}	else 
		triCount = vertexCount / 3;
	

	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);}

void Mesh::initializeQuad()
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);


	Vertex vertices[6];

	vertices[0].position = { -0.5f, 0,  0.5f, 1 };
	vertices[1].position = {  0.5f, 0,  0.5f, 1 };
	vertices[2].position = { -0.5f, 0, -0.5f, 1 };
	vertices[3].position = { -0.5f, 0, -0.5f, 1 };
	vertices[4].position = {  0.5f, 0,  0.5f, 1 };
	vertices[5].position = {  0.5f, 0, -0.5f, 1 };

	vertices[0].normal	 = { 0, 1, 0, 0 };
	vertices[1].normal	 = { 0, 1, 0, 0 };
	vertices[2].normal	 = { 0, 1, 0, 0 };
	vertices[3].normal	 = { 0, 1, 0, 0 };
	vertices[4].normal	 = { 0, 1, 0, 0 };
	vertices[5].normal	 = { 0, 1, 0, 0 };

	vertices[0].texCoord = { 0, 1 };
	vertices[1].texCoord = { 1, 1 };
	vertices[2].texCoord = { 0, 0 };
	vertices[3].texCoord = { 0, 0 };
	vertices[4].texCoord = { 1, 1 };
	vertices[5].texCoord = { 1, 0 };


	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex), vertices, GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)16);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);

	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount, GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);
}