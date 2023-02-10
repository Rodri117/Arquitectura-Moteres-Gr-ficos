#pragma once

// std Lib
#include <iostream>
#include <sstream>
#include <vector>

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
