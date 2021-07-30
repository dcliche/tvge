# tvge
Tiny Vulkan Game Engine

Based on the Vulkan Game Engine Tutorial available here: https://www.youtube.com/c/BrendanGalea/featured

## Getting Started

- Install Vulkan SDK (https://www.lunarg.com/vulkan-sdk/)
- Clone the repository with the `recurse-submodules` flag:
```bash
git clone --recurse-submodules https://github.com/dcliche/tvge.git
cd tvge
```

Note: if the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

- Build the project with your IDE or manually:
```bash
cmake -B build -S .
cmake --build build
```

