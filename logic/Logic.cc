#include <iostream>
#include <dlfcn.h>

#include "Logic.h"
#include "yaml-cpp/yaml.h"
#include "ICore.h"

using namespace tcore;

ICore * g_core = NULL; 

template<typename T>  
void operator >> (const YAML::Node& node, T& i)  
{  
    i = node.as<T>();  
}

ILogic * tcore::GetLogicInstance() {
    static ILogic * s_logic = new Logic();
    return s_logic;
}

bool Logic::Launch() {
    g_core = GetCoreInstance();
    const char * node = g_core->GetParam("node");
    if(!node) {
        return false;
    }
    char path[128];
    sprintf(path, "node/%s/module.yaml", node);
    YAML::Node config = YAML::LoadFile(path)["module"];

    MODULE_MAP::iterator iter;
    for (int i = 0; i < config.size(); i++) {
        std::string name;
        config[0] >> name;

        char file[32];
        sprintf(file, "lib%s.dylib", name.c_str());

        void * handle = dlopen(file, RTLD_LAZY); 
        if(handle == NULL){  
            std::cerr << dlerror() << std::endl;
        }

        GetModule * getModule = (GetModule *)dlsym(handle, "GetModule");
        if(getModule == NULL){  
            std::cerr << dlerror() << std::endl;  
        }

        IModule * module = getModule(g_core);
        while(module) {
            iter = _module_map.find(module->name);
            if(iter != _module_map.end()) {
                continue;
            }
            _module_map[module->name] = module;
            module->Init();
            module = module->next;
        }
    }
    
    iter = _module_map.begin();
    while(iter != _module_map.end()) {
        iter->second->Launch();
        iter++;
    }
    return true;
}

bool Logic::Shutdown() {
    return true;
}

IModule * Logic::FindModule(const char * name) {
    MODULE_MAP::iterator iter = _module_map.find(name);
    if(iter == _module_map.end()) {
        return NULL;
    }
    return iter->second;
}