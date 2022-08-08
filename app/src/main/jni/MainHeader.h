#include <EGL/egl.h> // need to make a common.h that contains all these headers cuz this is nasty
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#include <fstream>
#include <sstream>
#include "ImGui/imgui.h"
#include "ImGui/backends/imgui_impl_android.h"
#include "ImGui/backends/imgui_impl_opengl3.h"
#include <stdio.h>
#include <android/native_window_jni.h>
#include <list>
#include <vector>
#include <string.h>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "ByNameModding/BNM.hpp"
#include "Includes/Custom_Obfuscate.h"
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"
#include "Includes/Utils.h"
#include "KittyMemory/MemoryPatch.h"
#include "includes/Dobby/dobby.h"
#define targetLibName OBFUSCATE("libil2cpp.so")
#include "Includes/Macros.h"
#include "Includes/Loader.h"
#include "Includes/JNIStuff.h"
#include "Includes/FileWrapper.h"
#include "Menu/Menu.h"
#include "Color.h"


using namespace BNM;
using namespace Menu;

