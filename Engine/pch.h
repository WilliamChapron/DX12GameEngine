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

#include "src/core/Defines.h"   
#include "src/Utils.h"

//// autres en-têtes à précompiler
//#include "framework.h"

