//
//  Assets.cpp
//  Assets
//
//  Created by Matt Felsen on 12/7/15.
//
//

#include "Assets.h"

void Assets::setup() {
    loadImages();
    loadTextures();

    emptyImage = make_shared<ofImage>();
    emptyImage->allocate(1, 1, OF_IMAGE_COLOR_ALPHA);

    emptyTexture = make_shared<ofTexture>();
    emptyTexture->allocate(1, 1, GL_RGBA);
}

shared_ptr<ofImage> Assets::image(const string &name) {
    // TODO Cache empty image so you only get a warning the first time
    // you try to access it and not every frame trying to draw it?
    if (!exists(images, name)) {
        ofLogError("Assets") << "no such image: " << name;
        return emptyImage;
    }

    return images[name];
}
ofImage* Assets::imagePointer(const string& name) {
    return image(name).get();
}

shared_ptr<ofTexture> Assets::texture(const string &name) {
    // TODO Cache empty texture so you only get a warning the first time
    // you try to access it and not every frame trying to draw it?
    if (!exists(textures, name)) {
        ofLogError("Assets") << "no such texture: " << name;
        return emptyTexture;
    }

    return textures[name];
}
ofTexture* Assets::texturePointer(const string& name) {
    return texture(name).get();
}

bool Assets::addImage(const string &name, const string &filename, bool doMipmaps) {
    if (exists(images, name)) {
        ofLogVerbose("Assets") << "addImage: already exists, skipping: " << name;
        return true;
    }

    auto image = make_shared<ofImage>();

    if (doMipmaps)
        image->getTexture().enableMipmap();

    if (!image->load(filename)) {
        ofLogError("Assets") << "addImage: failed to load: " << filename;
        return false;
    }

    ofLogVerbose("Assets") << "loaded " << filename;
    images[name] = image;

    return true;
}

bool Assets::addTexture(const string &name, const string &filename, bool doMipmaps) {
    if (exists(textures, name)) {
        ofLogVerbose("Assets") << "addTexture: already exists, skipping: " << name;
        return true;
    }

    auto texture = make_shared<ofTexture>();

    if (doMipmaps)
        texture->enableMipmap();

    if (!ofLoadImage(*texture, filename)) {
        ofLogError("Assets") << "addTexture: failed to load: " << filename;
        return false;
    }

    ofLogVerbose("Assets") << "loaded " << filename;
    textures[name] = texture;

    return true;
}

template<typename T>
bool Assets::exists(T& container, const string &name) {
    return container.find(name) != container.end();
}

void Assets::loadImages() {
    addImage("ui/next", "images/ui/next.png");
    addImage("ui/previous", "images/ui/previous.png");

    addImage("ui/zoom-in", "images/ui/zoom-in.png");
    addImage("ui/zoom-out", "images/ui/zoom-out.png");
    image("ui/zoom-in")->resize(100, 100);
    image("ui/zoom-out")->resize(100, 100);
}

void Assets::loadTextures() {

}
