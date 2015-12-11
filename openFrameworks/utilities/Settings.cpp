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
        for (auto& it : boolMap) boolMap[it.first] = data[it.first].asBool();
        for (auto& it : intMap) intMap[it.first] = data[it.first].asInt();
        for (auto& it : floatMap) floatMap[it.first] = data[it.first].asFloat();
        for (auto& it : doubleMap) doubleMap[it.first] = data[it.first].asDouble();

        ofNotifyEvent(settingsLoaded);
    } else {
        ofLogError("Settings") << "could not load file! " << file;
    }
}

void Settings::save(string file) {
    // Write cached values back to JSON object
    cacheToJson(stringMap, data);
    cacheToJson(boolMap, data);
    cacheToJson(intMap, data);
    cacheToJson(floatMap, data);
    cacheToJson(doubleMap, data);

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
    if (!exists(stringMap, key)) {
        try {
            if (ofStringTimesInString(key, delimiter)) {
                auto keys = ofSplitString(key, delimiter);
                stringMap[key] = getChild(data, keys).asString();
            } else if (data.isMember(key)) {
                stringMap[key] = data[key].asString();
            } else {
                ofLogWarning("Settings") << "no setting found for: " << key;
                stringMap[key] = "";
            }
        } catch (const runtime_error& e) {
            ofLogError("Settings") << "error for key: " << key << ": " << e.what();
        }
    }

//    printMap(stringMap, "strings");
    return stringMap[key];
}

bool& Settings::_boolVal(string& key) {
    if (!exists(boolMap, key)) {
        try {
            if (ofStringTimesInString(key, delimiter)) {
                auto keys = ofSplitString(key, delimiter);
                boolMap[key] = getChild(data, keys).asBool();
            } else if (data.isMember(key)) {
                boolMap[key] = data[key].asBool();
            } else {
                ofLogWarning("Settings") << "no setting found for: " << key;
                boolMap[key] = false;
            }
        } catch (const runtime_error& e) {
            ofLogError("Settings") << "error for key: " << key << ": " << e.what();
        }
    }

//    printMap(boolMap, "bools");
    return boolMap[key];
}

int& Settings::_intVal(string& key) {
    if (!exists(intMap, key)) {
        try {
            if (ofStringTimesInString(key, delimiter)) {
                auto keys = ofSplitString(key, delimiter);
                intMap[key] = getChild(data, keys).asInt();
            } else if (data.isMember(key)) {
                intMap[key] = data[key].asInt();
            } else {
                ofLogWarning("Settings") << "no setting found for: " << key;
                intMap[key] = 0;
            }
        } catch (const runtime_error& e) {
            ofLogError("Settings") << "error for key: " << key << ": " << e.what();
        }
    }

//    printMap(intMap, "ints");
    return intMap[key];
}

float& Settings::_floatVal(string& key) {
    if (!exists(floatMap, key)) {
        try {
            if (ofStringTimesInString(key, delimiter)) {
                auto keys = ofSplitString(key, delimiter);
                floatMap[key] = getChild(data, keys).asFloat();
            } else if (data.isMember(key)) {
                floatMap[key] = data[key].asFloat();
            } else {
                ofLogWarning("Settings") << "no setting found for: " << key;
                floatMap[key] = 0;
            }
        } catch (const runtime_error& e) {
            ofLogError("Settings") << "error for key: " << key << ": " << e.what();
        }
    }

//    printMap(floatMap, "floats");
    return floatMap[key];
}

double& Settings::_doubleVal(string& key) {
    if (!exists(doubleMap, key)) {
        try {
            if (ofStringTimesInString(key, delimiter)) {
                auto keys = ofSplitString(key, delimiter);
                doubleMap[key] = getChild(data, keys).asDouble();
            } else if (data.isMember(key)) {
                doubleMap[key] = data[key].asDouble();
            } else {
                ofLogWarning("Settings") << "no setting found for: " << key;
                doubleMap[key] = 0;
            }
        } catch (const runtime_error& e) {
            ofLogError("Settings") << "error for key: " << key << ": " << e.what();
        }
    }

//    printMap(doubleMap, "doubles");
    return doubleMap[key];
}

ofxJSON Settings::getChild(ofxJSON data, vector<string> keys) {
    if (keys.size()) {
        string key = keys.front();
        keys.erase(keys.begin());

        if (data.isMember(key)) {
            return getChild(data[key], keys);
        } else {
            ofLogWarning("Settings") << "no setting found for: " << key;
            return ofxJSON();
        }
    }

    return data;
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

template<typename T>
void Settings::cacheToJson(T& container, ofxJSON& data) {
    for (auto& it : container) {
        auto& key = it.first;
        if (ofStringTimesInString(key, delimiter)) {
            auto keys = ofSplitString(key, delimiter);
            getChild(data, keys) = (ofxJSON) it.second;
        }
    }
}
