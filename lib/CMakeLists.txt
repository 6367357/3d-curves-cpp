cmake_minimum_required(VERSION 3.16)
project(curves LANGUAGES CXX)

add_library(curves SHARED
    src/curves/intersection3d/ModelIntersection.cpp
    src/curves/model3d/Circle.cpp
    src/curves/model3d/CurveFactory.cpp
    src/curves/model3d/Ellipse.cpp
    src/curves/model3d/Helix.cpp
)

target_include_directories(curves
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_precompile_headers(curves
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/curves/pch.h
)

target_compile_features(curves
    PUBLIC cxx_std_20
)