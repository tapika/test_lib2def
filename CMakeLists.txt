cmake_minimum_required(VERSION 3.17)

# Inspired by llvm\lib\cmake\llvm\AddLLVM.cmake / export_executable_symbols
function(export_executable_symbols target def_file)
    get_target_property(new_libs ${target} LINK_LIBRARIES)
    
    foreach(lib ${new_libs})
    if(TARGET ${lib})
        get_target_property(lib_type ${lib} TYPE)
        if("${lib_type}" STREQUAL "STATIC_LIBRARY")
        list(APPEND static_libs ${lib})
        endif()
    endif()
    endforeach(lib)

    set(lib2def ${CMAKE_CURRENT_SOURCE_DIR}/lib2def.py)
    add_custom_command(OUTPUT ${def_file}
                       COMMAND python ${lib2def} ${static_libs} -o ${def_file}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                       DEPENDS ${lib2def} ${static_libs}
                       VERBATIM
                       COMMENT "Generating ${def_file}...")
endfunction()


project(test_lib2def)

add_library(test1 
    test1.cpp 
    test1.h
    lib2def.py
)

target_compile_definitions(test1 PUBLIC TEST1)

set(def_file ${CMAKE_CURRENT_BINARY_DIR}/test1_dll.def)

add_library(test1_dll SHARED 
    test1_dll.cpp
    ${def_file}
)

set_source_files_properties(${def_file} PROPERTIES GENERATED 1)

target_link_libraries(test1_dll PRIVATE test1)

export_executable_symbols(test1_dll ${def_file})


add_executable(test2 test2.cpp)

target_link_libraries(test2 PRIVATE test1_dll)

