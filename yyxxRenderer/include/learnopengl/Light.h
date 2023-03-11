#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
class Light
{
public:
	glm::vec3 pos;
	glm::vec3 amb;
	glm::vec3 dif;
	glm::vec3 spe;
	Light() {}
	Light(glm::vec3 pos,
		glm::vec3 amb,
		glm::vec3 dif,
		glm::vec3 spe ) :pos(pos), amb(amb), dif(dif), spe(spe) {}
};
#endif // !LIGHT_H
