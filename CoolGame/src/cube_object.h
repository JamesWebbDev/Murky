#ifndef CUBE_OBJECT_H
#define CUBE_OBJECT_H

#include <Murky.h>

class CubeObject
{
public:

	Murky::Model CubeModel = Murky::Model();
	Murky::Transform CubeTransform = Murky::Transform();

	CubeObject()
	{

	}

	void Draw(Murky::Shader& shader)
	{
		CubeModel.Draw(shader, CubeTransform.GetModelMatrix());
	}
};

#endif
