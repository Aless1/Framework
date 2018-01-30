#include <iostream>
#include "Logic.h"
#include "yaml-cpp/yaml.h"

ILogic * tcore::GetLogicInstance() {
    static ILogic * s_logic = new Logic();
    return s_logic;
}

bool Logic::Launch() {
    YAML::Node config = YAML::LoadFile("node/master/module.yaml")["module"];
    for (int i = 0; i < config.size(); i++) {
        std::cout << config[0];
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
