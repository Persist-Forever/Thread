aux_source_directory(. SRC_LIST)
include_directories(${PROJECT_SOURCE_DIR}/src/thread_proc/include)
add_library(thread_proc-src-object OBJECT ${SRC_LIST})

set(thread_proc-src
    $<TARGET_OBJECTS:thread_proc-src-object>
    PARENT_SCOPE)
set(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib/)
