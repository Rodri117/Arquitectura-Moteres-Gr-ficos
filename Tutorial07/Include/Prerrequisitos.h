#pragma once

// std Lib
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

//Ecternal Lib
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <xnamath.h>

//Windows
#include <windows.h>

//Internal Includ
#include "Resource.h"

//Definir
#define WINDOWS
#define WARNING( s )						 \
{											 \
   std::wostringstream os_;					 \
   os_ << s;								 \
   OutputDebugStringW( os_.str().c_str() );  \
}

//Macro for safe release of resources
#define SAFE_RELEASE(x) if(x != nullptr) x->Release(); x = nullptr;

// * To check monster
#define OutputLOG(_ClassName, _FunctionName, _OutputMessage)           \
OutputDebugStringA(_ClassName);                                        \
OutputDebugStringA(" : In Function : ");                               \
OutputDebugStringA(_FunctionName);                                     \
OutputDebugStringA(" : ");                                             \
OutputDebugStringA(_OutputMessage);                                    \
OutputDebugStringA("\n");
