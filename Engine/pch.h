#include <windows.h>

#include <string>
#include <string_view>
#include <array>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>

#include <random>
#include <iostream>
#include <sstream>
#include <format> 
#include <system_error>

//DirectX
#include <directxtk/SimpleMath.h>

//Direct3D
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

// GameInput
#include "Include/GameInput/GameInput.h"

//Custom
#include "Helper/CommonEnum.h"
#include "Helper/CommonDef.h"
#include "Helper/ReferenceCounter.h"

#include "Helper/DataType/Vector.h"
#include "Helper/DataType/Matrix.h"
#include "Helper/DataType/ColorF.h"
#include "Helper/DataType/Radian.h"
#include "Helper/DataType/Degree.h"

#include "Helper/Time/Time.h"
#include "Helper/Input/Input.h"
#include "Helper/Utillity/Utillity.h"

#include "Interface/ILifeCycle.h"
#include "Interface/Entity.h"
#include "Interface/Factory.h"

#include "Manager/GameManager.h"
#include "Manager/WorldManager.h"