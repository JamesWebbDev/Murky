#pragma once

#include <Murky.h>

class ModelLayer : public Murky::Layer
{
public:
	virtual ~ModelLayer() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate() override;



private:


};