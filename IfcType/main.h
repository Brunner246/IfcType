#pragma once

// define plugin info. REQUIRED by cadwork plugin
#define CWAPI3D_PLUGIN_NAME L"Test"
#define CWAPI3D_AUTHOR_NAME L"MB"
#define CWAPI3D_AUTHOR_EMAIL L"brunner@cadwork.swiss"


//#include "CwAPI3D.h"
#include <string>
#include <exception>
#include <locale>
#include <codecvt>
#include <chrono>
#include <thread>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include "../CwApi28/includes/CwAPI3D.h"

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory* factory);