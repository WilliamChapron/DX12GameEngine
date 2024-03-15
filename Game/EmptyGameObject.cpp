#include "stdafx.h"
#include "EmptyGameObject.h"
#include "pch.h"

EmptyGameObject::EmptyGameObject(ComponentManager* componentManager, std::string name) : GameObject(componentManager, name), m_pComponentManager(componentManager)
{
}

void EmptyGameObject::Update(Renderer* renderer, Camera* camera)
{
	m_pComponentManager->UpdateComponents(this);
}
