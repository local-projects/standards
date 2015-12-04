## Root Folder Structure

- README.md
- Apps
	- OF App 1
	- OF App 2
	- OF App 3
- Sketches
	- OF Sketch 1
	- OF Sketch 2
	- OF Sketch 3
- openFrameworks (git submodule)
- ExternalAddons
	- addon1 (git submodule)
	- addon2 (git submodule)
	- addon3 (git submodule)
- build.command*
- Configs*
- Documentation
- Deployment*
	- Scripts
	- start.command
	- stop.command
- Scripts*


## openFrameworks and addons

### openFrameworks
openFrameworks should be added as a submodule, pointing at the Local Projects fork. Feel free to create a project-specific branch that points to a different version of OF (`master`, `stable`, `0.8.1`, etc.). For example:

	git submodule add https://github.com/local-projects/openFrameworks.git
	cd openFrameworks
	git checkout stable
	git checkout -b project/YourProject

### addons
openFrameworks addons should be added as submodules in the ExternalAddons addons folder. These addons should be forked into the Local Projects account in the event that the original author removes their repository, and so that we can maintain project-specific code. For example:

	cd ExternalAddons
	git submodule add https://github.com/local-projects/ofxAddonName.git

When adding an addon to a project, make sure a relative path is used. Tools such as Adam Carlucci's [OF Plugin for Xcode](https://github.com/admsyn/OFPlugin) should take care of this automatically, setting the paths to something like `../../ExternalAddons/ofxAddonName...` instead of the normal `../../../addons/ofxAddonName...`. You want to make sure it's not an absolute path such as `/Users/youraccount/Code/Project/ExternalAddons/ofxAddonName...` because everyone will hate you.

## Other Folders

### build.command
This script should build a Release from scratch. The script will create a Release folder, to be copied integrally into the final computer. That folder should include binary + needed configuration files, required assets, and deployment scripts. The deployment scripts are the way to start, stop and report crashes for the installation.
The release binary should include versioning information. Look into CWRU project for an example on how to do this on OSX.

### Configs
Includes configuration files to be used onsite. These will be copied over the Release folder by the build.command when building a release.

### Deployment
includes all scripts needed to start / stop / report crash etc for the installtaion. It should at least include two clear scripts called "start" and "stop", wich might call subscripts.

### Scripts
Random scripts that might help for development / testing (i.e. pull json files and clean, update submodules, etc)

### Shared
Project-specific code that is shared among Sketches and/or Apps.

## Set up a new project
See [this non-official, non-complete, work in progress script](https://gist.github.com/mattfelsen/b50762ed68a9e43f7388) for helping to automate getting a new project set up with the above structure: