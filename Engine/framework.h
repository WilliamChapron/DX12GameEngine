// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

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
#include <algorithm>
#include <functional>

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





// Core
#include "src/core/Defines.h"  
#include "src/core/Engine.h"  
#include "src/core/Window.h"  

// Component
#include "src/ecs/components/Camera.h"
#include "src/ecs/components/Collider.h"
#include "src/ecs/components/Component.h"
#include "src/ecs/components/Mesh.h"
#include "src/ecs/components/MeshRenderer.h"
#include "src/ecs/components/Shader.h"
#include "src/ecs/components/Texture.h"
#include "src/ecs/components/Transform.h"
#include "src/ecs/components/ScriptComponent.h"
#include "src/ecs/components/Particle.h"



// Ent
#include "src/ecs/entities/GameObject.hpp"          



// System
#include "src/ecs/systems/ComponentManager.h"  
#include "src/ecs/systems/GameObjectManager.h"  
#include "src/ecs/systems/Input.h"
#include "src/ecs/systems/ResourceManager.h"
#include "src/ecs/systems/StateMachine.h"
#include "src/ecs/systems/Time.h"




// Renderer 
#include "src/renderer/Graphics.h"   
#include "src/renderer/Resources.h"   



// Miscellaneous
#include "src/CommonsMesh.h"
#include "src/Utils.h"
#include "src/DDSTextureLoader.h"

// Other

#include "src/Atom.h"

using namespace DirectX;

//// autres en-têtes à précompiler
//#include "framework.h"

