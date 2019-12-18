cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

project(RayTracer LANGUAGES C CXX)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(RayTracer
        main.cpp
        BRDFs/BRDF.cpp
        BRDFs/BRDF.h
        BRDFs/Lambertian.cpp
        BRDFs/Lambertian.h
        Cameras/Camera.cpp
        Cameras/Camera.h
        Cameras/Pinhole.cpp
        Cameras/Pinhole.h
        GeometricObjects/GeometricObject.cpp
        GeometricObjects/GeometricObject.h
        GeometricObjects/Plane.cpp
        GeometricObjects/Plane.h
        GeometricObjects/Sphere.cpp
        GeometricObjects/Sphere.h
        Lights/Ambient.cpp
        Lights/Ambient.h
        Lights/Directional.cpp
        Lights/Directional.h
        Lights/Light.cpp
        Lights/Light.h
        Materials/Material.cpp
        Materials/Material.h
        Materials/Matte.cpp
        Materials/Matte.h
        Tracers/MultipleObjects.cpp
        Tracers/MultipleObjects.h
        Tracers/RayCast.cpp
        Tracers/RayCast.h
        Tracers/SingleSphere.cpp
        Tracers/SingleSphere.h
        Tracers/Tracer.cpp
        Tracers/Tracer.h
        ui/MainWindow.cpp
        ui/MainWindow.h
        ui/RenderWindow.cpp
        ui/RenderWindow.h
        World/ViewPlane.cpp
        World/ViewPlane.h
        World/World.cpp
        World/World.h)
target_link_libraries(RayTracer Qt5::Widgets)