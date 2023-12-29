cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)



project(native-export C)



option(NATIVE_EXPORT_BINARIES_DIR CACHE OFF)

if (NOT NATIVE_EXPORT_BINARIES_DIR)
set(NATIVE_EXPORT_BINARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
endif()

function(build_native_export)
add_library(native-export native-export/src/native-export.c)
target_include_directories(native-export PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/native-export/include
)
if (WIN32)
set_target_properties(native-export PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${NATIVE_EXPORT_BINARIES_DIR}/windows
)
else()
set_target_properties(native-export PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${NATIVE_EXPORT_BINARIES_DIR}/linux
)
endif(WIN32)
endfunction()


function(build_native_export_sample)
add_executable(native-export-sample sample/src/native-export-sample.c)
target_link_libraries(native-export-sample PUBLIC native-export)
if (WIN32)
set_target_properties(native-export-sample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY      ${NATIVE_EXPORT_BINARIES_DIR}/windows
    VS_DEBUGGER_WORKING_DIRECTORY ${NATIVE_EXPORT_BINARIES_DIR}/windows
)
else()
set_target_properties(native-export-sample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY      ${NATIVE_EXPORT_BINARIES_DIR}/linux
    VS_DEBUGGER_WORKING_DIRECTORY ${NATIVE_EXPORT_BINARIES_DIR}/linux
)
endif(WIN32)
endfunction()



option(NATIVE_EXPORT_BUILD_SAMPLE CACHE OFF)



function(main)
build_native_export()
if (NATIVE_EXPORT_BUILD_SAMPLE)
build_native_export_sample()
endif(NATIVE_EXPORT_BUILD_SAMPLE)
endfunction()


main()
