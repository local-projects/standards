//
//  Assets.h
//  Assets
//
//  Created by Matt Felsen on 12/7/15.
//
//

#pragma once

#include "ofMain.h"

class Assets {
public:
    Assets() {}

    // Singleton..
    static Assets& get() {
        static Assets instance;
        return instance;
    }

    void setup();

    // Use these to access shared assets after they've been added
    shared_ptr<ofImage> image(const string& name);
    shared_ptr<ofTexture> texture(const string& name);

    // Use this for somewhat nicer access to the raw pointer
    // ie this:      image->setImagePointer(Assets::get().image("name").get())
    // becomes this: image->setImagePointer(Assets::get().imagePointer("name"))
    ofImage* imagePointer(const string& name);
    ofTexture* texturePointer(const string& name);

    // Use these to load new assets. If already loaded, asset will be skipped
    bool addImage(const string& name, const string& filename, bool doMipmaps = false);
    bool addTexture(const string& name, const string& filename, bool doMipmaps = false);

protected:
    template<typename T>
    bool exists(T& container, const string &name);

    void loadImages();
    void loadTextures();

    map<string, shared_ptr<ofImage>> images;
    map<string, shared_ptr<ofTexture>> textures;

    // empty content to return instead of null pointers
    shared_ptr<ofImage> emptyImage;
    shared_ptr<ofTexture> emptyTexture;

private:
    // make sure there are no copies
    Assets(Assets const&);
    void operator=(Assets const&);
};