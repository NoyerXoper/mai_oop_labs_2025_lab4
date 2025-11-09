add_library(arrayLib INTERFACE)
target_include_directories(arrayLib INTERFACE array exceptions)

add_library(compareLib INTERFACE)
target_include_directories(compareLib INTERFACE compare concepts)

add_library(figuresLib INTERFACE)
target_include_directories(figuresLib INTERFACE compare concepts exceptions point figure polygon rhombus pentagon trapezoid)
