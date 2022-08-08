#include "MainHeader.h" //DON'T FORGET TO SET TARGET LIB NAME IN THE FILE

enum Settings {
    fly,
    crouch,
    jump
};

struct {
    Color ZombieColor = Color::red();
} FT;


//declare a variable where the offset we get from bynamemodding sits
uintptr_t Speed = 0x0;
uintptr_t Runner = 0x0;
uintptr_t PlayerUpdate = 0x0;
uintptr_t Visible = 0x0;
uintptr_t Coins = 0x0;
DWORD Example = 0x0; // You can set Dword variable too


bool (*old_get_BoolExample)(void *instance);
bool get_BoolExample(void *instance) {
    if (instance != NULL && Menu::SWITCH.BoolExample) {
        return true;
    }
    return old_get_BoolExample(instance);
}

float (*old_FloatExample)(void *instance); 
float FloatExample(void *instance) { 
      if(instance!=NULL) { 
        if (SWITCH.FloatExample) { 
          return 100.0f; 
         } 
       } return old_FloatExample(instance); 
      } 

int (*old_Level)(void *instance);
int Level(void *instance) {
    if (instance != NULL && SWITCH.IntExample) {
        return 9999;
    }
    return old_Level(instance);
}

void(*_VoidExample)(void *instance);
void VoidExample(void *instance) {
    if (SWITCH.VoidExample) {
        *(bool *) ((uint64_t) instance + Visible) = true;
        *(float *) ((uint64_t) instance + Speed) = 0.01;
    }
    _VoidExample(instance);
}


void (*AddMoney)(void* _this, float coin);
void (*_Coin)(void *instance);
void Coin(void *instance) {
    if (instance != NULL) {
        if(SWITCH.BoolExample) {
            AddMoney(instance, 10000000);
        }
    }
    return _Coin(instance);
}
 

//ImGui Menu, Touch and display
EGLBoolean (*old_eglSwapBuffers)(...);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
    
    if (!setup){
        SetupImGui();
       } setup = true;
        DrawImGuiMenu();
    return old_eglSwapBuffers(dpy, surface);
}


extern "C"
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    
    JNIEnv *globalEnv;
    vm->GetEnv((void **) &globalEnv, JNI_VERSION_1_6);
    UnityPlayer_cls = globalEnv->FindClass(OBFUSCATE("com/unity3d/player/UnityPlayer"));
    UnityPlayer_CurrentActivity_fid = globalEnv->GetStaticFieldID(UnityPlayer_cls, OBFUSCATE("currentActivity"), OBFUSCATE("Landroid/app/Activity;"));
    DobbyHook((void*)globalEnv->functions->RegisterNatives, (void*)hook_RegisterNatives, (void **)&old_RegisterNatives);

    return JNI_VERSION_1_6;
}


void *hack_thread(void *) { 

    do {
        sleep(1);
    } while (!isLibraryLoaded(targetLibName));
    address = findLibrary(targetLibName);
    LOGI(OBFUSCATE("pthread created"));
    
    AttachIl2Cpp();
    Menu::Screen_get_height = (int (*)()) OBFBNM("UnityEngine", "Screen", "get_height", 0);
    Menu::Screen_get_width = (int (*)()) OBFBNM("UnityEngine", "Screen", "get_width", 0);
    // use bynamemodding to get offsets from here.
    
    //get the class
    auto Player = getClass(OBFUSCATE("PlayerData"));
    
    //use the class and method name to get the offset and put it in the variable we declared earlier.
    
    Runner = getOffset(Player, OBFUSCATE("Run"), {"Map"});
    PlayerUpdate = getOffset(Player, OBFUSCATE("Update")); 
    // Field offset
    AddField(Visible, Player, "isVisible");
    AddField(Speed, Player, "Speed");
    
    //Pointer
    Coins = getOffset(Player, OBFUSCATE("Currency"), {"scale"});
    AddPointer(AddMoney, Coins);
    
    // And you can call namespace, class, methods all in once by
    Coins = OBFBNM(""/*NAMESPACE*/, "PlayerData"/*CLASS*/, "Currency"/*METHOD*/, 1/*PARAMETER COUNT*/); 
    
    
    DetachIl2Cpp(); // Important when Using ByNameModding Functions
    
    
    DHK(Runner, Level, old_Level); //DobbyHook
    HK(Runner, FloatExample, old_FloatExample); //MSHookFunction
    
    //patchoffset
    Menu::Patch.map = MemoryPatch::createWithHex(targetLibName, Runner,"0000000000000000");
    Patch.map.Modify();
    
    //patch toggle
    Patch.minimap = MemoryPatch::createWithHex("libil2cpp.so", Runner, "0000000000000000");
        if(SWITCH.Memorypatchtest){
            Patch.minimap.Modify();
            } else {
            Patch.minimap.Restore();
         }
                      
    return NULL;
}


__attribute__((constructor))
void lib_main()
{
    auto eglhandle = dlopen(OBFUSCATE("libEGL.so"), RTLD_LAZY);
    dlerror();
    auto eglSwapBuffers = dlsym(eglhandle, OBFUSCATE("eglSwapBuffers"));
    const char *dlsym_error = dlerror();
    if (dlsym_error)
    {
        LOGE(OBFUSCATE("Cannot load symbol 'eglSwapBuffers': %s"), dlsym_error);
    } else
    {
        DHK(eglSwapBuffers, hook_eglSwapBuffers, old_eglSwapBuffers);
    }
    pthread_t ptid;
    pthread_create(&ptid, NULL, hack_thread, NULL);
}

