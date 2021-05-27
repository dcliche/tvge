# tvge
Tiny Vulkan Game Engine

## Getting Started

- Install Vulkan SDK (https://www.lunarg.com/vulkan-sdk/)
- Clone the repository with the `recurse-submodules` flag:
```bash
git clone --recurse-submodules https://github.com/dcliche/xeni.git
cd xeni
```

Note: if the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

- Build the project with your IDE or manually:
```bash
cmake -B build -S .
cmake --build build
```

