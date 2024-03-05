#pragma once

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")

// en-têtes standard C++
#include <iostream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <list>
#include <stdexcept>
#include <math.h>

// Windows
#include <Windows.h>

// DirectX
#include <d3d12.h>
#include <dxgi1_4.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "./extern/d3dx12.h"
#include <wrl/client.h>

#include <DirectXColors.h>

#include "src/core/Engine.h"
#include "src/core/Defines.h"
#include "src/ecs/entities/GameObject.h"
#include "src/ecs/entities/CubeMesh.h"
#include "src/ecs/components/Camera.h"
#include "src/ecs/systems/GameObjectManager.h"
#include "src/ecs/systems/ComponentManager.h"
#include "src/ecs/systems/Input.h"



