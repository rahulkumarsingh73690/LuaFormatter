#pragma once

#include <yaml-cpp/yaml.h>
#include "ConfigCheck.h"
#ifdef HAVE_FILESYSTEM_H
#include <filesystem>
#else
#include <experimental/filesystem>
#endif

#include <any>
#include <functional>

using namespace std;

typedef std::function<std::any(std::string, std::any)> Validator;

#ifdef HAVE_FILESYSTEM_H
namespace fs = filesystem;
#else
namespace fs = experimental::filesystem;
#endif

class Config {
   public:
    Config();
    void readFromFile(const string &file);
    void dumpCurrent(ofstream &fout);
    void dumpCurrent(ostream &out);
    map<string, any> argmap;
    map<string, char> datatype;
    void readFromMap(map<string, any> &mp);
    YAML::Node node_;
    template <typename T>
    T get(const char *key) const {
        return node_[key].as<T>();
    }
    template <typename T>
    T get(const char *key) {
        return node_[key].as<T>();
    }
    template <typename T>
    void set(const char *key, T value) {
        node_[key] = value;
    }
    template <typename T>
    void set(const char *key, T value) const {
        node_[key] = value;
    }
    std::map<std::string, Validator> validators;
};
