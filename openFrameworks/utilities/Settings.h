//
//  Settings.h
//  Settings
//
//  Created by Matt Felsen on 12/7/15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxJSON.h"

class Settings {
public:
    Settings();

    // Singleton..
    static Settings& get() {
        static Settings instance;
        return instance;
    }

    void setDelimiter(string delim);
    void load(string file = "settings.json");
    void save(string file = "settings.json", bool prettyPrint = true);

    // Use this to get values
    // These return references, so you can bind directly to a GUI library that
    // supports variable binding
    static string& getString(string key);
    static bool& getBool(string key);
    static int& getInt(string key);
    static float& getFloat(string key);
    static double& getDouble(string key);

    ofEvent<void> settingsLoaded;
    ofEvent<void> settingsSaved;

    // Super shorthand?
    // static bool getB("setting");
    // static bool bool_("setting");
    // static bool _bool("setting");

protected:
    string& _stringVal(string& key);
    bool& _boolVal(string& key);
    int& _intVal(string& key);
    float& _floatVal(string& key);
    double& _doubleVal(string& key);

    string _stringValFromJson(ofxJSON& data, string& key);
    bool _boolValFromJson(ofxJSON& data, string& key);
    int _intValFromJson(ofxJSON& data, string& key);
    float _floatValFromJson(ofxJSON& data, string& key);
    double _doubleValFromJson(ofxJSON& data, string& key);

    ofxJSON getNestedChild(ofxJSON data, string key);
    ofxJSON getNestedChild(ofxJSON data, vector<string> keys);

    template<typename T>
    void setNestedChild(ofxJSON& data, string key, T val);

    template<typename T>
    void setNestedChild(ofxJSON& data, vector<string> keys, T val);

    template<typename T>
    void cacheToJson(T& container, ofxJSON& data);

    template<typename T>
    bool exists(T& container, const string &key);

    template<typename T>
    void printMap(T& container, const string& text = "");

    ofxJSON jsonStore;
    unordered_map<string,string> stringMap;
    unordered_map<string,int> intMap;
    unordered_map<string,bool> boolMap;
    unordered_map<string,float> floatMap;
    unordered_map<string,double> doubleMap;

    string delimiter;

};
