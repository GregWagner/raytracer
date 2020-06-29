cmake_minimum_required(VERSION 3.10)

option(BUILD_GUI "Build the Qt GUI" OFF)
include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD 14)

if(BUILD_GUI)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
endif()

project(RayTracer LANGUAGES C CXX)

if(BUILD_GUI)
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
endif()
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

option(USE_AVX "Enable the use of AVX Optimisations" ON)

set(RAYTRACER_SRCS
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
        Cameras/ThinLens.cpp
        Cameras/ThinLens.h
        Utilities/RenderTarget.h)

if(BUILD_GUI)
    add_executable(RayTracer
            main.cpp
            ui/MainWindow.cpp
            ui/MainWindow.h
            ui/RenderWindow.cpp
            ui/RenderWindow.h
            ui/RenderThread.cpp
            ui/RenderThread.h
            ${RAYTRACER_SRCS}
    )
    target_link_libraries(RayTracer Qt5::Widgets)
endif()

add_executable(clitracer
        ${RAYTRACER_SRCS}
        cli/main.cpp
	cli/ImageTarget.cpp
	cli/ImageTarget.h
)
target_link_libraries(clitracer PRIVATE Threads::Threads)

# turn on autovectorisation.
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    check_cxx_compiler_flag(-fslp-vectorize FSLP_VECTORIZE)
    check_cxx_compiler_flag(-fvectorize FVECTORIZE)
    if(BUILD_GUI)
        target_compile_options(clitracer PRIVATE $<$<BOOL:FVECTORIZE>:-fvectorize> $<$<BOOL:FSLP_VECTORIZE>:-fslp-vectorize>)
    endif()
    target_compile_options(RayTracer PRIVATE $<$<BOOL:FVECTORIZE>:-fvectorize> $<$<BOOL:FSLP_VECTORIZE>:-fslp-vectorize>)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    check_cxx_compiler_flag(-ftree-vectorize FTREE_VECTORIZE)
    if(BUILD_GUI)
        target_compile_options(RayTracer PRIVATE $<$<BOOL:FTREE_VECTORIZE>:-ftree-vectorize>)
    endif()
    target_compile_options(clitracer PRIVATE $<$<BOOL:FTREE_VECTORISE>:-ftree-vectorize>)
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86|AMD64")
    if(MSVC)
        # bias the optimizer towards Intel CPUs
        #target_compile_options(RayTracer PRIVATE /favor:INTEL64)
        if(USE_AVX)
            if(BUILD_GUI)
                target_compile_options(RayTracer PRIVATE /arch:AVX)
            endif()
            target_compile_options(clitracer PRIVATE /arch:AVX)
        endif()
    else()
        check_cxx_compiler_flag(-msse MSSE)
        check_cxx_compiler_flag(-msse2 MSSE2)
        if(BUILD_GUI)
            target_compile_options(RayTracer PRIVATE $<$<BOOL:MSSE>:-msse> $<$<BOOL:MSSE2>:-msse2>)
        endif()
        target_compile_options(clitracer PRIVATE $<$<BOOL:MSSE>:-msse> $<$<BOOL:MSSE2>:-msse2>)
        if(USE_AVX)
            check_cxx_compiler_flag(-mavx MAVX)
            if(BUILD_GUI)
                target_compile_options(RayTracer PRIVATE $<$<BOOL:MAVX>:-mavx>)
            endif()
            target_compile_options(clitracer PRIVATE $<$<BOOL:MAVX>:-mavx>)
        endif()
    endif()
else()
    message(WARNING "System Processor = ${CMAKE_SYSTEM_PROCESSOR}")
endif()

if(CMAKE_SYSTEM_NAME STREQUAL Windows)
    if(BUILD_GUI)
        add_custom_target(winDeps
            DEPENDS RayTracer
            COMMAND ${Qt5_DIR}../../../../bin/windeployqt.exe RayTracer.exe)
    endif()
endif()
