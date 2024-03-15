#pragma once

#include "./include.h"
#include <iostream>
#include <iomanip>

//using namespace DirectX;

void PrintMatrix(const DirectX::XMFLOAT4X4& matrix);

void printFloatWithPrecision(float value, int precision);

std::wstring stringToWString(const std::string& narrowString);

HRESULT CompileShaderFromFile(const wchar_t* filePath, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);

XMFLOAT2 NormalizeVector(XMFLOAT2 vect);

float Clamp(float v, float a = 0.0f, float b = 1.0f);

int GetRandomNum(int min, int max);