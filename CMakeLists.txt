CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(rtracer)
SET(CMAKE_BUILD_TYPE "Debug")
SET(rtracer_SOURCES
        main.cpp
        RayTracer.cpp
        Scene.cpp
        ImageIO.cpp
        ImageWriter.cpp
        ImageReader.cpp
        Drawable.cpp
        Material.cpp
        Pixel.cpp
        Ray.cpp
        Texture.cpp
        Light.cpp
        Box.cpp
        Sphere.cpp
        Plane.cpp
        math/Vec3.cpp
        math/Matrix4d.cpp
        math/Matrix4f.cpp
        math/Quat.cpp
        )
ADD_EXECUTABLE(rtracer ${rtracer_SOURCES})
#SET(CMAKE_CXX_FLAGS_DEBUG "-Wextra -Wall -g -O2 -fno-inline")
#SET(CMAKE_CXX_FLAGS_DEBUG "-Wextra -Wall -O2 -fno-inline -pg")
