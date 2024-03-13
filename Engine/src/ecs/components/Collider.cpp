
#include "pch.h"

//#include "../entities/GameObject.hpp"
//
#include "Component.h"
//#include "Transform.h"
//#include "Mesh.h"
//#include "Collider.h"

//using namespace DirectX;


ColliderComponent::ColliderComponent(std::string name) : Component(name, ComponentType::ColliderComponent), m_collideState(0), m_colliderObject(nullptr) {

}


void ColliderComponent::InitializeBoundingBox(GameObject* gameObject, Vertex* vertices, int numVertices) {
    m_pGameObject = gameObject;

    float minX = FLT_MAX;
    float minY = FLT_MAX;
    float minZ = FLT_MAX;
    float maxX = -FLT_MAX;
    float maxY = -FLT_MAX;
    float maxZ = -FLT_MAX;

    for (int i = 0; i < numVertices; ++i) {
        XMFLOAT3 vertexPos = vertices[i].Pos;

        minX = (minX < vertexPos.x) ? minX : vertexPos.x;
        minY = (minY < vertexPos.y) ? minY : vertexPos.y;
        minZ = (minZ < vertexPos.z) ? minZ : vertexPos.z;

        maxX = (maxX > vertexPos.x) ? maxX : vertexPos.x;
        maxY = (maxY > vertexPos.y) ? maxY : vertexPos.y;
        maxZ = (maxZ > vertexPos.z) ? maxZ : vertexPos.z;
    }

    m_halfSize.x = abs(maxX - minX) / 2;
    m_halfSize.y = abs(maxY - minY) / 2;
    m_halfSize.z = abs(maxZ - minZ) / 2;
}


void ColliderComponent::Update(Renderer* renderer) {
    //PRINT("Update Collider");

}







bool ColliderComponent::CheckCollision(GameObject* collideObject) {

    Transform* transformBox1 = m_pGameObject->GetComponent<Transform>(ComponentType::Transform);
    Transform* transformBox2 = collideObject->GetComponent<Transform>(ComponentType::Transform);

    XMFLOAT3 gPosBox1 = transformBox1->GetPosition();
    XMFLOAT3 gPosBox2 = transformBox2->GetPosition();

    XMFLOAT4 rotQBox1 = transformBox1->GetRotationQuaternion();
    XMFLOAT4 rotQBox2 = transformBox2->GetRotationQuaternion();


    XMFLOAT3 halfSizeBox1 = m_halfSize;
    XMFLOAT3 halfSizeBox2 = collideObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent)->m_halfSize;

    float halfSizeX1 = halfSizeBox1.x;
    float halfSizeY1 = halfSizeBox1.y;
    float halfSizeZ1 = halfSizeBox1.z;

    float halfSizeX2 = halfSizeBox2.x;
    float halfSizeY2 = halfSizeBox2.y;
    float halfSizeZ2 = halfSizeBox2.z;

    XMFLOAT3 cornersBox1[8] = {
        { gPosBox1.x - halfSizeX1, gPosBox1.y - halfSizeY1, gPosBox1.z - halfSizeZ1 },
        { gPosBox1.x + halfSizeX1, gPosBox1.y - halfSizeY1, gPosBox1.z - halfSizeZ1 },
        { gPosBox1.x - halfSizeX1, gPosBox1.y + halfSizeY1, gPosBox1.z - halfSizeZ1 },
        { gPosBox1.x + halfSizeX1, gPosBox1.y + halfSizeY1, gPosBox1.z - halfSizeZ1 },
        { gPosBox1.x - halfSizeX1, gPosBox1.y - halfSizeY1, gPosBox1.z + halfSizeZ1 },
        { gPosBox1.x + halfSizeX1, gPosBox1.y - halfSizeY1, gPosBox1.z + halfSizeZ1 },
        { gPosBox1.x - halfSizeX1, gPosBox1.y + halfSizeY1, gPosBox1.z + halfSizeZ1 },
        { gPosBox1.x + halfSizeX1, gPosBox1.y + halfSizeY1, gPosBox1.z + halfSizeZ1 }
    };


    XMFLOAT3 cornersBox2[8] = {
        { gPosBox2.x - halfSizeX2, gPosBox2.y - halfSizeY2, gPosBox2.z - halfSizeZ2 },
        { gPosBox2.x + halfSizeX2, gPosBox2.y - halfSizeY2, gPosBox2.z - halfSizeZ2 },
        { gPosBox2.x - halfSizeX2, gPosBox2.y + halfSizeY2, gPosBox2.z - halfSizeZ2 },
        { gPosBox2.x + halfSizeX2, gPosBox2.y + halfSizeY2, gPosBox2.z - halfSizeZ2 },
        { gPosBox2.x - halfSizeX2, gPosBox2.y - halfSizeY2, gPosBox2.z + halfSizeZ2 },
        { gPosBox2.x + halfSizeX2, gPosBox2.y - halfSizeY2, gPosBox2.z + halfSizeZ2 },
        { gPosBox2.x - halfSizeX2, gPosBox2.y + halfSizeY2, gPosBox2.z + halfSizeZ2 },
        { gPosBox2.x + halfSizeX2, gPosBox2.y + halfSizeY2, gPosBox2.z + halfSizeZ2 }
    };


    XMFLOAT3 minBox1(FLT_MAX, FLT_MAX, FLT_MAX);
    XMFLOAT3 maxBox1(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (int i = 0; i < 8; ++i) {
        minBox1.x = (cornersBox1[i].x < minBox1.x) ? cornersBox1[i].x : minBox1.x;
        minBox1.y = (cornersBox1[i].y < minBox1.y) ? cornersBox1[i].y : minBox1.y;
        minBox1.z = (cornersBox1[i].z < minBox1.z) ? cornersBox1[i].z : minBox1.z;

        maxBox1.x = (cornersBox1[i].x > maxBox1.x) ? cornersBox1[i].x : maxBox1.x;
        maxBox1.y = (cornersBox1[i].y > maxBox1.y) ? cornersBox1[i].y : maxBox1.y;
        maxBox1.z = (cornersBox1[i].z > maxBox1.z) ? cornersBox1[i].z : maxBox1.z;
    }

    XMFLOAT3 minBox2(FLT_MAX, FLT_MAX, FLT_MAX);
    XMFLOAT3 maxBox2(-FLT_MAX, -FLT_MAX, -FLT_MAX);

    for (int i = 0; i < 8; ++i) {
        minBox2.x = (cornersBox2[i].x < minBox2.x) ? cornersBox2[i].x : minBox2.x;
        minBox2.y = (cornersBox2[i].y < minBox2.y) ? cornersBox2[i].y : minBox2.y;
        minBox2.z = (cornersBox2[i].z < minBox2.z) ? cornersBox2[i].z : minBox2.z;

        maxBox2.x = (cornersBox2[i].x > maxBox2.x) ? cornersBox2[i].x : maxBox2.x;
        maxBox2.y = (cornersBox2[i].y > maxBox2.y) ? cornersBox2[i].y : maxBox2.y;
        maxBox2.z = (cornersBox2[i].z > maxBox2.z) ? cornersBox2[i].z : maxBox2.z;
    }


    bool collisionX = maxBox1.x >= minBox2.x && minBox1.x <= maxBox2.x;
    bool collisionY = maxBox1.y >= minBox2.y && minBox1.y <= maxBox2.y;
    bool collisionZ = maxBox1.z >= minBox2.z && minBox1.z <= maxBox2.z;


    // Instance of Component Collider of other object
    ColliderComponent* colliderComponentObject = collideObject->GetComponent<ColliderComponent>(ComponentType::ColliderComponent);

    if (collisionX && collisionY && collisionZ) {
        // Set collide info self
        m_collideState = 1;
        m_colliderObject = collideObject;

        // Set collide info other object
        colliderComponentObject->m_collideState = 1;
        colliderComponentObject->m_colliderObject = m_pGameObject;

        std::cout << "Collision detected! Collided with object: " << collideObject->m_name << std::endl;
        std::cout << "Self - m_collideState: " << m_collideState << ", m_colliderObject: " << m_colliderObject->m_name << std::endl;

        // Print collide info of the other object
        std::cout << "Other - m_collideState: " << colliderComponentObject->m_collideState << ", m_colliderObject: " << colliderComponentObject->m_colliderObject->m_name << std::endl;

        std::cout << "----" << std::endl;
        return true;
    }
    else {
        // Set collide info self
        //m_collideState = 0;

        //// Set collide info other object
        //colliderComponentObject->m_collideState = 0;

        std::cout << "No collision detected." << std::endl;
        std::cout << "Self - m_collideState: " << m_collideState << ", m_colliderObject: " << (m_colliderObject ? m_colliderObject->m_name : "nullptr") << std::endl;

        // Print collide info of the other object
        std::cout << "Other - m_collideState: " << colliderComponentObject->m_collideState << ", m_colliderObject: " << (colliderComponentObject->m_colliderObject ? colliderComponentObject->m_colliderObject->m_name : "nullptr") << std::endl;

        std::cout << "----" << std::endl;
        return false;
    }


}


