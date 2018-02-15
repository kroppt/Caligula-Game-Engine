#include "config.hpp"
#include <libconfig.h++>
#include <iostream>

using namespace libconfig;

int res_x = 1280;
int res_y = 720;
int vsync = 1;

void parse_res_x(const Setting& root){
    try{
        res_x = root["window"]["width"];
    }
    catch(const SettingNotFoundException &nfex){
        // Ignore.
    }
    catch(const std::exception &ex){
        // Throw any other exception.
        throw ex;
    }
}

void parse_res_y(const Setting& root){
    try{
        res_y = root["window"]["height"];
    }
    catch(const SettingNotFoundException &nfex){
        // Ignore.
    }
    catch(const std::exception &ex){
        // Throw any other exception.
        throw ex;
    }
}

void parse_vsync(const Setting& root){
    try{
        vsync = (root["window"]["vsync"]) ? 1 : 0;
    }
    catch(const SettingNotFoundException &nfex){
        // Ignore.
    }
    catch(const std::exception &ex){
        // Throw any other exception.
        throw ex;
    }
}

void readConfig(const char *filename){
    Config cfg;
    try{
        cfg.readFile(filename);
    }
    catch(const FileIOException &fioex){
        throw fioex;
    }
    catch(const ParseException &pex){
        throw pex;
    }
    const Setting& root = cfg.getRoot();
    try{
        parse_res_x(root);
        parse_res_y(root);
        parse_vsync(root);
    }
    catch(const SettingException &sex){
        throw sex;
        return;
    }
}

void createConfig(const char *filename){
    Config cfg;
    Setting &root = cfg.getRoot();

    Setting &window = root.add("window", Setting::TypeGroup);
    window.add("width", Setting::TypeInt) = res_x;
    window.add("height", Setting::TypeInt) = res_y;
    window.add("vsync", Setting::TypeBoolean) = (bool) vsync;

    try{
        cfg.writeFile(filename);
    }
    catch(const FileIOException &fioex){
        throw fioex;
    }
}
