#pragma once


#include "Component.h"

struct AABB {
    XMFLOAT3 min;
    XMFLOAT3 max;
};

class Component;
class GameObject;

struct Vertex;

class ColliderComponent : public Component
{
public:
    ColliderComponent(std::string name);
    void Update(Renderer* renderer) override;

    void OnEnter();
    void OnStay();
    void OnExit();


    void InitializeBoundingBox(GameObject* gameObject, Vertex* vertices, int numVertices);
    //AABB TransformBoundingBoxLocalToGlobal(AABB localBoundingBox, GameObject* gameObject);

    bool CheckCollision(GameObject* gameObject);
      
    int m_collideState;
    GameObject* m_colliderObject;
private:
    GameObject* m_pGameObject;
    AABB m_localAxisAlignedBoundingBox;
    XMFLOAT3 m_halfSize;
    

};
