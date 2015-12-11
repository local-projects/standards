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

    void load(string file = "settings.json");
    void save(string file = "settings.json");

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

    ofxJSON getChild(ofxJSON parent, vector<string> keys);

    template<typename T>
    bool exists(T& container, const string &key);

    template<typename T>
    void printMap(T& container, const string& text = "");

    template<typename T>
    void cacheToJson(T& container, ofxJSON& data);

    ofxJSON data;
    unordered_map<string,string> stringMap;
    unordered_map<string,int> intMap;
    unordered_map<string,bool> boolMap;
    unordered_map<string,float> floatMap;
    unordered_map<string,double> doubleMap;

    string delimiter;

};
