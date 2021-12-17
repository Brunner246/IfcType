#pragma once

// define plugin info. REQUIRED by cadwork plugin
#define CWAPI3D_PLUGIN_NAME L"IfcType"
#define CWAPI3D_AUTHOR_NAME L"Michael Brunner"
#define CWAPI3D_AUTHOR_EMAIL L"brunner@cadwork.swiss"


//#include "CwAPI3D.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include "../CwApi28/includes/CwAPI3D.h" // ../CwApi28/includes/CwAPI3D.h

CWAPI3D_PLUGIN bool plugin_x64_init(CwAPI3D::ControllerFactory* factory);