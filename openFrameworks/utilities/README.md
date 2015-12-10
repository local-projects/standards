Some thoughts/goals for putting this stuff together...

## Assets

- load stuff when the app starts
- load stuff on the fly // content obtained from CMS that we get during app initialization
- built around `shared_ptr` instead of raw pointers
- nice syntax
	- `Assets::get().addTexture("ui/next-button", "images/ui/next-button.png");`
	- `Assets::get().texture("ui/next-button");`
	- `Assets::get().texture("ui/next-button").get();` gets the pointer. posible but kind of dumb looking
	- `Assets::get().texturePointer("ui/next-button");` so use this instead

## Settings

- load/save to json instead of xml
	- pattern of having cms store settings is used frequently
	- easily consume settings from cms
	- json is easier to read/edit (highly subjective!)
- build settings dynamically instead of explicit declaration/initialization
	- don't need to build settings line by line
	- ie didn't want to have to do this..
	
	```
	namespace Settings {
		namespace Fonts {
			static float size = 34;
			static float lineHeight = 1.2;
			static string face = "Palatino"
		}
	}
	```
	- above also is not only not directly loadable, it isn't directly saveable either
	- makes adding new settings as easy as adding to json file and that's it
		- add to file: `"{ ..., newKey: "new Value" }`
		- `Settings::getValue("newKey")` should work automatically
- namespacing/nesting/hierarchical structure instead of just flat

	```
	{
		"cms:" {
			"hostname": "192.168.0.10",
			"port": 8000,
			"endpoint": "/settings"
			"use": true
		},
		"fonts:" {
			"size": 34,
			"line-height": 1.2,
			"face": "Palatino"
		}
	}
	```
- type agnostic
	- should support strings, bools, ints, floats, doubles nicely
- fast!
	- leaving values in an ofxJSONElement calling .asFloat() for something every frame seems excessive and might be 	slow
- directly bindable to gui
	- didn't want to have to create/track/update primitives that are bound to gui that then have to be synced with 	values in the Settings object somehow
	- can't do this if you were using an ofxJSONElement as your storage
- separation between app settings and gui settings
	- settings should be bindable to gui, but not every settings needs to be controlled by your gui!
	- also allows easy changing of guis since you're not tied to that gui's settings file format
- nice syntax
	- `Settings::getString("font-name");`
	- `Settings::getString("fonts/face");`
	- `guiSlider->bind(&Settings::getFloat("font-size"));`
	- somewhat cleaner than `Settings::get().getString("font-name")`
	
