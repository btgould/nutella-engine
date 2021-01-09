# Nutella Engine

Game engine based on TheCherno's Hazel engine using his YouTube series. 

To build, run `premake5 gmake`. Although premake is capable of generating files for other build systems, such as visual studio, my source code only supports compiling with g++ (and therefore GNU `make`). This will generate makefiles that will handle actually building the project. Run `make` to generate the executable, and `make help` for a more detailed list of targets. The executable will be placed (along with a copy of the shared object library) in a subdirectory of "bin" corresponding to the build configuration and platform.
