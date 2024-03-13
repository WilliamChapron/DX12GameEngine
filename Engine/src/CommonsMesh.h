﻿#pragma once

struct Vertex;

class CubeMesh {
public:
    Vertex* cubeVertices;
    UINT* cubeIndices;
    int numElementsV;
    int numElementsI;

    float aabbSizeX;
    float aabbSizeY;
    float aabbSizeZ;

    CubeMesh() {
        // Initialisation des pointeurs
        cubeVertices = new Vertex[8]{
            { {-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
            { {-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
            { {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
            { { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
            { { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { 0.5f,  0.5f, -0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f} },
            { { 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f} }
        };

        cubeIndices = new UINT[36]{
            0, 1, 2,
            2, 1, 3,
            4, 6, 5,
            6, 7, 5,
            0, 2, 4,
            2, 6, 4,
            1, 5, 3,
            3, 5, 7,
            2, 3, 6,
            3, 7, 6,
            0, 4, 1,
            1, 4, 5
        };

        numElementsV = 8;
        numElementsI = 36;
    }

    ~CubeMesh() {
        delete[] cubeVertices;
        delete[] cubeIndices;
    }
};

class TriangleMesh {
public:
    Vertex* cubeVertices;
    UINT* cubeIndices;
    int numElementsV;
    int numElementsI;

    TriangleMesh() {
        // Initialisation des pointeurs
        cubeVertices = new Vertex[8]{
            { {0.5f, 0.9f, 0.9f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
            { {0.9f, 0.9f,  -0.9f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { {0.9f,  0.9f, 0.9f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f} },
            { {0.9f,  0.9f,  0.9f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f} },
            { { 0.9f, 0.9f, 0.9f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f} },
            { { 0.9f, 0.9f,  0.9f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { 0.9f,  0.9f, 0.9f}, {0.9f, 0.5f, 0.5f, 1.0f}, {1.0f, 1.0f} },
            { { 0.5f,  0.5f,  0.5f}, {0.5f, 0.5f, 0.5f, 1.0f}, {1.0f, 0.0f} }
        };

        cubeIndices = new UINT[36]{
            0, 1, 2,
            2, 1, 3,
            4, 6, 5,
            6, 7, 5,
            0, 2, 4,
            2, 6, 4,
            1, 5, 3,
            3, 5, 7,
            2, 3, 6,
            3, 7, 6,
            0, 4, 1,
            1, 4, 5
        };

        numElementsV = 8;
        numElementsI = 36;
    }

    ~TriangleMesh() {
        delete[] cubeVertices;
        delete[] cubeIndices;
    }
};

class SphereMesh {
public:
    Vertex* cubeVertices;
    UINT* cubeIndices;
    int numElementsV;
    int numElementsI;

    SphereMesh(float radius = 1.0f, int latitudeCount = 20, int longitudeCount = 20) {
        numElementsV = (latitudeCount + 1) * (longitudeCount + 1);
        numElementsI = latitudeCount * longitudeCount * 6;

        cubeVertices = new Vertex[numElementsV];
        cubeIndices = new UINT[numElementsI];

        int index = 0;

        // G�n�rer les vertices
        for (int lat = 0; lat <= latitudeCount; ++lat) {
            float theta = lat * XM_PI / latitudeCount;
            float sinTheta = sinf(theta);
            float cosTheta = cosf(theta);

            for (int lon = 0; lon <= longitudeCount; ++lon) {
                float phi = lon * 2 * XM_PI / longitudeCount;
                float sinPhi = sinf(phi);
                float cosPhi = cosf(phi);

                float x = radius * sinTheta * cosPhi;
                float y = radius * cosTheta;
                float z = radius * sinTheta * sinPhi;

                cubeVertices[index].Pos = XMFLOAT3(x, y, z);
                cubeVertices[index].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // Blanc par d�faut
                cubeVertices[index].Uv = XMFLOAT2(static_cast<float>(lon) / longitudeCount, static_cast<float>(lat) / latitudeCount);

                ++index;
            }
        }

        // G�n�rer les indices
        index = 0;
        for (int lat = 0; lat < latitudeCount; ++lat) {
            for (int lon = 0; lon < longitudeCount; ++lon) {
                int current = lat * (longitudeCount + 1) + lon;
                int next = current + 1;
                int below = (lat + 1) * (longitudeCount + 1) + lon;
                int belowNext = below + 1;

                cubeIndices[index++] = current;
                cubeIndices[index++] = below;
                cubeIndices[index++] = next;

                cubeIndices[index++] = next;
                cubeIndices[index++] = below;
                cubeIndices[index++] = belowNext;
            }
        }
    }

    ~SphereMesh() {
        delete[] cubeVertices;
        delete[] cubeIndices;
    }
};



class Skydome {
public:
    Vertex* cubeVertices;
    UINT* cubeIndices;
    int numElementsV;
    int numElementsI;

    Skydome(float radius = 1.0f, int numSegments = 64) {
        numElementsV = (numSegments + 1) * (numSegments + 1);
        numElementsI = numSegments * numSegments * 6;

        cubeVertices = new Vertex[numElementsV];

        for (int i = 0; i <= numSegments; ++i) {
            float phi = static_cast<float>(i) / numSegments * static_cast<float>(XM_PI);
            for (int j = 0; j <= numSegments; ++j) {
                float theta = static_cast<float>(j) / numSegments * static_cast<float>(XM_PI * 2);

                float x = radius * std::sinf(phi) * std::cosf(theta);
                float y = radius * std::cosf(phi);
                float z = radius * std::sinf(phi) * std::sinf(theta);

                float u = static_cast<float>(j) / numSegments;
                float v = static_cast<float>(i) / numSegments;

                cubeVertices[i * (numSegments + 1) + j] = { {x, y, z}, {1.0f, 1.0f, 1.0f, 1.0f}, {u, v} };
            }
        }

        cubeIndices = new UINT[numElementsI];

        int index = 0;
        for (int i = 0; i < numSegments; ++i) {
            for (int j = 0; j < numSegments; ++j) {
                cubeIndices[index++] = i * (numSegments + 1) + j;
                cubeIndices[index++] = (i + 1) * (numSegments + 1) + j;
                cubeIndices[index++] = i * (numSegments + 1) + j + 1;

                cubeIndices[index++] = i * (numSegments + 1) + j + 1;
                cubeIndices[index++] = (i + 1) * (numSegments + 1) + j;
                cubeIndices[index++] = (i + 1) * (numSegments + 1) + j + 1;
            }
        }
    }

    ~Skydome() {
        delete[] cubeVertices;
        delete[] cubeIndices;
    }
};