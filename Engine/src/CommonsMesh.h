#pragma once

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

        // Générer les vertices
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
                cubeVertices[index].Color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f); // Blanc par défaut
                cubeVertices[index].Uv = XMFLOAT2(static_cast<float>(lon) / longitudeCount, static_cast<float>(lat) / latitudeCount);

                ++index;
            }
        }

        // Générer les indices
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

class Skybox {
public:
    Vertex* cubeVertices;
    UINT* cubeIndices;
    int numElementsV;
    int numElementsI;

    Skybox(float size = 1.0f) {
        numElementsV = 24;
        numElementsI = 36;

        cubeVertices = new Vertex[numElementsV]{
            // Face avant (+Z)
            { {-size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 1 / 3.0f} },
            { {size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 1 / 3.0f} },
            { {size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 2 / 3.0f}},
            { {-size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 2 / 3.0f} },

            // Face arrière (-Z)
            { {-size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.75f, 1 / 3.0f} },
            { {size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{1.0f, 1 / 3.0f} },
            { {size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{1.0f, 2 / 3.0f} },
            { {-size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.75f, 2 / 3.0f} },

            // Face gauche (-X)
            { {-size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.0f, 1 / 3.0f} },
            { {-size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 1 / 3.0f} },
            { {-size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 2 / 3.0f} },
            { {-size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.0f, 2 / 3.0f} },

            // Face droite (+X)
            { {size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 1 / 3.0f} },
            { {size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.75f, 1 / 3.0f} },
            { {size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.75f, 2 / 3.0f} },
            { {size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 2 / 3.0f} },

            // Face supérieure (+Y)
            { {-size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 0.0f} },
            { {size, size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 0.0f} },
            { {size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 1 / 3.0f} },
            { {-size, size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 1 / 3.0f} },

            // Face inférieure (-Y)
            { {-size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 2 / 3.0f} },
            { {size, -size, size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 2 / 3.0f} },
            { {size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.5f, 1.0f} },
            { {-size, -size, -size}, {1.0f, 0.0f, 0.0f, 1.0f} ,{0.25f, 1.0f} }
        };

        cubeIndices = new UINT[numElementsI]{
            0, 1, 2, 2, 3, 0, // Face avant
            4, 5, 6, 6, 7, 4, // Face arrière
            8, 9, 10, 10, 11, 8, // Face gauche
            12, 13, 14, 14, 15, 12, // Face droite
            16, 17, 18, 18, 19, 16, // Face supérieure
            23, 22, 21, 21, 20, 23  // Face inférieure (inversion des indices)
        };
    }

    ~Skybox() {
        delete[] cubeVertices;
        delete[] cubeIndices;
    }
};
