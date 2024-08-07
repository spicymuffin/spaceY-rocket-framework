if (DEFINED PICO_BOARD)
    file(GLOB DIRECTORY_CONTENTS LIST_DIRECTORIES true rp2040/*)
    foreach(DIR ${DIRECTORY_CONTENTS})
        if(IS_DIRECTORY ${DIR})
            add_subdirectory(${DIR})
            message(STATUS "Adding subdirectory ${DIR}")
        else()
            continue()
        endif()
    endforeach()
else()
    file(GLOB DIRECTORY_CONTENTS LIST_DIRECTORIES true host/*)
    foreach(DIR ${DIRECTORY_CONTENTS})
        if(IS_DIRECTORY ${DIR})
            add_subdirectory(${DIR})
            message(STATUS "Adding subdirectory ${DIR}")
        else()
            continue()
        endif()
    endforeach()
endif()


add_custom_command(OUTPUT ${PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_ROOT_LIST_DIR}/dist/util
)