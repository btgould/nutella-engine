## Nutella Engine

Game engine based on TheCherno's Hazel engine using his YouTube series. 

To build, run `premake5 gmake`. Although premake is capable of generating files for other build systems, such as visual studio, my source code only supports compiling with g++ (and therefore GNU `make`). This will generate makefiles that will handle actually building the project. Run `make` to generate the executable, and `make help` for a more detailed list of targets. The executable will be placed (along with a copy of the shared object library) in a subdirectory of "bin" corresponding to the build configuration and platform.

# Using with Client Application
To have a client application link with nutella, simply use the `client-premake.lua` file in the nutella repo. Create a parent premake script for your project, have it include the `client-premake.lua` file, and make your parent project `links "Nutella"`. 

If you have placed nutella in a subdirectory of your main project (i.e. as a git submodule or something similar), you will have to pass the relative path of this subdirectory to nutella so that it can load its default resources properly. To do this, in your parent premake script, simply declare a global string variable called `nutellaPath` with the relative path before including the `client-premake.lua` file. 
