#pragma once


class EmptyGameObject : public GameObject
{
public:
	EmptyGameObject(ComponentManager* componentManager, std::string name);
	void Update(Renderer* renderer, Camera* camera) override;
private:
	ComponentManager* m_pComponentManager;
};

