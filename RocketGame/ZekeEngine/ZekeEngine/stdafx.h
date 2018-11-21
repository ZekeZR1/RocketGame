// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。

#include <WinSock2.h>
#include <windows.h>
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <map>
#include <wincodec.h>
#include <memory>
#include <wincodecsdk.h>
#include <Xinput.h>
#include <xaudio2.h>
#include <x3daudio.h>
#include <xaudio2fx.h>
#include <functional>
#include <cstring>
#include <string>

const float FRAME_BUFFER_W = 1280.0f;
const float FRAME_BUFFER_H = 720.0f;
static const int MAX_BONE = 512;

#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"	
#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/Audio.h"

#include "policy\Noncopyable.h"
#include "util\Util.h"
#include "math\kMath.h"
#include "math/Matrix.h"
#include "math\Vector.h"
#include "graphics\Camera.h"
#include "graphics\CGraphicsEngine.h"
#include "EngineStruct.h"
#include "CEngine.h"
#include "gameObject\CTransform.h"
#include "gameObject\GameObject.h"
#include "gameObject\GameObjectManager.h"

#include "graphics\SkinModel.h"
#include "graphics/SkinModelDataManager.h"

using namespace ZekeEngine;
