cmake_minimum_required(VERSION 3.17)

# Switch ON/OFF to test different types of linkage
#set(use_def_file ON)
set(use_def_file OFF)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY DISABLE_DEPRECATION_WARNING ON)
cmake_policy(SET CMP0026 OLD)


# Inspired by llvm\lib\cmake\llvm\AddLLVM.cmake / export_executable_symbols
function(export_executable_symbols target def_file)
    get_target_property(new_libs ${target} LINK_LIBRARIES)
    
    foreach(lib ${new_libs})
    if(TARGET ${lib})
        get_target_property(lib_type ${lib} TYPE)
        if("${lib_type}" STREQUAL "STATIC_LIBRARY")
        # Works only with CMP0026, see https://stackoverflow.com/questions/32197663/how-can-i-remove-the-the-location-property-may-not-be-read-from-target-error-i
        get_property(libpath TARGET ${lib} PROPERTY LOCATION)
        #list(APPEND static_libs $<${lib}>)
        list(APPEND static_libs ${libpath})
        endif()
    endif()
    endforeach(lib)

    message(${static_libs})

    set(lib2def ${CMAKE_CURRENT_SOURCE_DIR}/lib2def.py)
    add_custom_command(OUTPUT ${def_file}
                       COMMAND python ${lib2def} ${static_libs} -o ${def_file}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                       DEPENDS ${lib2def} ${static_libs}
                       VERBATIM
                       COMMENT "Generating ${def_file}...")
endfunction()


project(test_lib2def)


if(NOT ${use_def_file})
    add_definitions(-DEXPORT_VIA_DECLSPEC)
endif()

set(staticLibSrcs
    test1.cpp 
    test1.h
)


if(${use_def_file})
    set(def_file ${CMAKE_CURRENT_BINARY_DIR}/test1_dll.def)

    add_library(test1 
        ${staticLibSrcs}
        lib2def.py
    )
    target_compile_definitions(test1 PRIVATE TEST1_EXPORTS)
    add_library(test1_dll SHARED 
        test1_dll.cpp
        ${def_file}
    )
    set_source_files_properties(${def_file} PROPERTIES GENERATED 1)
    target_link_libraries(test1_dll PRIVATE test1)
    export_executable_symbols(test1_dll ${def_file})

else()

    add_library(test1_dll SHARED
        ${staticLibSrcs}
    )

    target_compile_definitions(test1_dll PRIVATE TEST1_EXPORTS)

endif()

add_executable(test2 test2.cpp)

target_link_libraries(test2 PRIVATE test1_dll)

