configure_file (
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h
)

include_directories (
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
)

set (SOURCES 
    Cvcore.cpp
    Utility.cpp
    Absdiff.cpp
    Add.cpp
    AddWeighted.cpp
    Bitwise_and.cpp
    Bitwise_not.cpp
    Bitwise_or.cpp
    Bitwise_xor.cpp
    Mean.cpp
    Merge.cpp
    Sum.cpp
)

add_library (stromx_cvcore SHARED ${SOURCES})

set(VERSION_STRING "${STROMX_OPENCV_VERSION_MAJOR}.${STROMX_OPENCV_VERSION_MINOR}.${STROMX_OPENCV_VERSION_PATCH}")

set_target_properties (stromx_cvcore PROPERTIES
    VERSION ${VERSION_STRING}
    SOVERSION ${VERSION_STRING}
    FOLDER "library"
)

target_link_libraries (stromx_cvcore
    ${OpenCV_LIBS}
    ${stromx_RUNTIME_LIB}
    ${stromx_CVSUPPORT_LIB}
)

if(WIN32)
    install (TARGETS stromx_cvcore
        RUNTIME DESTINATION .
        LIBRARY DESTINATION ${LIB_DIR}
        ARCHIVE DESTINATION ${LIB_DIR}
    )
else(WIN32)
    install (TARGETS stromx_cvcore
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION ${LIB_DIR}
        ARCHIVE DESTINATION ${LIB_DIR}
    )
endif(WIN32)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/stromx/cvcore
    DESTINATION include/stromx
    FILES_MATCHING PATTERN "*.h"
    PATTERN "test" EXCLUDE
)

install(FILES ${CMAKE_BINARY_DIR}/stromx/cvcore/Config.h
    DESTINATION include/stromx/cvcore
)

if(BUILD_TESTS)
    add_subdirectory(test)
endif(BUILD_TESTS)
