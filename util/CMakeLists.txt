file(GLOB DIRECTORY_CONTENTS LIST_DIRECTORIES true *)
foreach(DIR ${DIRECTORY_CONTENTS})
    if(IS_DIRECTORY ${DIR})
        add_subdirectory(${DIR})
        message(STATUS "Adding subdirectory ${DIR}")
    else()
        continue()
    endif()
endforeach()

add_custom_command(OUTPUT ${PROJECT} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
    ${CMAKE_ROOT_LIST_DIR}/dist/util
)