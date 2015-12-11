//
//  Settings.cpp
//  Settings
//
//  Created by Matt Felsen on 12/10/15.
//
//

#include "Settings.h"

Settings::Settings() {
    delimiter = "/";
    // TODO conversion/recursion of json["parent"]["child"] to "parent/child"
}

void Settings::load(string file) {
    ofxJSON loadData;

    if (loadData.open(file)) {
        data = loadData;

        // Any values bound to gui are bound to memory address of value
        // inside various cached map objects, so we can't clear() the maps
        // Instead, load new values from new json object to cached maps

        // TODO any keys that were in the old json that have been removed from
        // the new file won't be deleted from the cached maps. Need to compare
        // data vs loadData objects and remove missing keys?
        for (auto& it : stringMap) stringMap[it.first] = data[it.first].asString();
        for (auto& it : intMap) intMap[it.first] = data[it.first].asInt();
        for (auto& it : boolMap) boolMap[it.first] = data[it.first].asBool();
        for (auto& it : floatMap) floatMap[it.first] = data[it.first].asFloat();
        for (auto& it : doubleMap) doubleMap[it.first] = data[it.first].asDouble();

        ofNotifyEvent(settingsLoaded);
    } else {
        ofLogError("Settings") << "could not load file! " << file;
    }
}

void Settings::save(string file) {
    // Write cached values back to JSON object
    for (auto& it : stringMap) data[it.first] = it.second;
    for (auto& it : intMap) data[it.first] = it.second;
    for (auto& it : boolMap) data[it.first] = it.second;
    for (auto& it : floatMap) data[it.first] = it.second;
    for (auto& it : doubleMap) data[it.first] = it.second;

    // second arg is for pretty-print
    if (data.save(file, true)) {
        ofNotifyEvent(settingsSaved);
    } else {
        ofLogError("Settings") << "could not save file! " << file;
    }
}

string& Settings::getString(string key) {
    return get()._stringVal(key);
}
bool& Settings::getBool(string key) {
    return get()._boolVal(key);
}
int& Settings::getInt(string key) {
    return get()._intVal(key);
}
float& Settings::getFloat(string key) {
    return get()._floatVal(key);
}
double& Settings::getDouble(string key) {
    return get()._doubleVal(key);
}

string& Settings::_stringVal(string& key) {
//    if (ofStringTimesInString(key, delimiter)) {
//        auto keys = ofSplitString(key, delimiter);
//    }

    if (!exists(stringMap, key)) {
        if (data.isMember(key)) {
            stringMap[key] = data[key].asString();
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            stringMap[key] = "";
        }
    }

//    printMap(stringMap, "strings");
    return stringMap[key];
}

bool& Settings::_boolVal(string& key) {
    if (!exists(boolMap, key)) {
        if (data.isMember(key)) {
            boolMap[key] = data[key].asBool();
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            boolMap[key] = false;
        }
    }

//    printMap(boolMap, "bools");
    return boolMap[key];
}

int& Settings::_intVal(string& key) {
    if (!exists(intMap, key)) {
        if (data.isMember(key)) {
            intMap[key] = data[key].asInt();
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            intMap[key] = 0;
        }
    }

//    printMap(intMap, "ints");
    return intMap[key];
}

float& Settings::_floatVal(string& key) {
    if (!exists(floatMap, key)) {
        if (data.isMember(key)) {
            floatMap[key] = data[key].asFloat();
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            floatMap[key] = 0;
        }
    }

//    printMap(floatMap, "floats");
    return floatMap[key];
}

double& Settings::_doubleVal(string& key) {
    if (!exists(doubleMap, key)) {
        if (data.isMember(key)) {
            doubleMap[key] = data[key].asDouble();
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            doubleMap[key] = 0;
        }
    }

//    printMap(doubleMap, "doubles");
    return doubleMap[key];
}

template<typename T>
bool Settings::exists(T& container, const string &key) {
    return container.find(key) != container.end();
}

template<typename T>
void Settings::printMap(T& container, const string& text) {
    for (auto& it : container) {
        ofLogNotice() << text << ": " << it.first << ": " << it.second;
    }
}
