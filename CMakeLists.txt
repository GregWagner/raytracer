cmake_minimum_required(VERSION 3.13)

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
        Samplers/Hammersley.cpp
        Samplers/Hammersley.h
        Samplers/Jittered.cpp
        Samplers/Jittered.h
        Samplers/MultiJittered.cpp
        Samplers/MultiJittered.h
        Samplers/NRooks.cpp
        Samplers/NRooks.h
        Samplers/PureRandom.cpp
        Samplers/PureRandom.h
        Samplers/Regular.cpp
        Samplers/Regular.h
        Samplers/Sampler.cpp
        Samplers/Sampler.h
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
        ui/RenderThread.cpp
        ui/RenderThread.h
        Utilities/Constants.h
        Utilities/Maths.h
        Utilities/Matrix.cpp
        Utilities/Matrix.h
        Utilities/Normal.cpp
        Utilities/Normal.h
        Utilities/Point2D.cpp
        Utilities/Point2D.h
        Utilities/Point3D.cpp
        Utilities/Point3D.h
        Utilities/Ray.cpp
        Utilities/Ray.h
        Utilities/RGBColor.cpp
        Utilities/RGBColor.h
        Utilities/ShadeRec.cpp
        Utilities/ShadeRec.h
        Utilities/Vector3D.cpp
        Utilities/Vector3D.h
        World/ViewPlane.cpp
        World/ViewPlane.h
        World/World.cpp
        World/World.h
        )
target_link_libraries(RayTracer Qt5::Widgets)