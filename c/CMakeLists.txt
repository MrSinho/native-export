cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)



project(native-export C)


function(build_native_export)
add_library(native-export native-export/src/native-export.c)
target_include_directories(native-export PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/native-export/include
)
set_target_properties(native-export PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
endfunction()


function(build_native_export_sample)
add_executable(native-export-sample sample/src/native-export-sample.c)
target_link_libraries(native-export-sample PUBLIC native-export)
set_target_properties(native-export-sample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
endfunction()



option(NATIVE_EXPORT_BUILD_SAMPLE CACHE OFF)



function(main)
build_native_export()
if (NATIVE_EXPORT_BUILD_SAMPLE)
build_native_export_sample()
endif(NATIVE_EXPORT_BUILD_SAMPLE)
endfunction()


main()