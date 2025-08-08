# OpenGL-Forum

This is a forum app where you can chat, create your own account, it works like a normal forum.

- Written in C.
- Simple and easy to use UI made with OpenGL + FreeGLUT.
- Only dependency: FreeGLUT 3.0+.
- Built on Linux. Also compiles on Windows with MinGW (use the right FreeGLUT library and version).
- You can use any Linux distro you like, I use RHEL.
- Also you can use any compiler you like, I used clang.
- If you want to use any other compiler you can change it inside the Makefile.

## RHEL setup (FreeGLUT)
```bash
sudo dnf install freeglut freeglut-devel
```

## Build
```bash
make all
```

## Clean
```bash
make clean
```
