cmake_minimum_required(VERSION 3.13.4)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

set(LIB_SRCS
    src/library/lib.c
)
set(CLI_SRCS
    src/client/main.c
)
set(TEST_SRCS
    src/test/add1.c
    src/test/add2.c
)

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
math(EXPR VERSION_NUM
    "${VERSION_MAJOR} * 1000000 + ${VERSION_MINOR} * 1000 + ${VERSION_PATCH}"
)

project(chattor VERSION ${VERSION})

include(CTest)

add_library(chattor SHARED ${LIB_SRCS})
set_target_properties(chattor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
target_include_directories(chattor PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

add_library(chattors STATIC ${LIB_SRCS})
set_target_properties(chattor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
target_include_directories(chattors PUBLIC ${PROJECT_SOURCE_DIR}/src/include)

add_executable(chattor-cli ${CLI_SRCS})
set_target_properties(chattor-cli PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output)
target_link_libraries(chattor-cli PRIVATE chattors)

foreach(test_filename ${TEST_SRCS})
    get_filename_component(test_name ${test_filename} NAME_WE)
    add_executable(chattor-test-${test_name} ${test_filename})
    set_target_properties(chattor-test-${test_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output/unit-tests)
    target_link_libraries(chattor-test-${test_name} PRIVATE chattors cunit)
    add_test(NAME unit/${test_name}
        COMMAND valgrind --leak-check=full --quiet --error-exitcode=2
                $<TARGET_FILE:chattor-test-${test_name}>)
endforeach()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

configure_file(src/include/chattor.h output/include/chattor.h)
