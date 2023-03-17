set(NOESIS_ROOT_DIR ${PROJECT_SOURCE_DIR}/libs/NoesisGUI CACHE PATH "" FORCE)
set(NOESIS_PKG_DIR ${NOESIS_ROOT_DIR}/Src/Packages)

if ((NOT EXISTS ${NOESIS_ROOT_DIR}))
    message(ERROR "Failed to build panda3d-noesis; NoesisGUI lib not found: ${NOESIS_ROOT_DIR}")
endif()

message(STATUS "Found NoesisGUI lib: ${NOESIS_ROOT_DIR}")

# Link libs.
if (WIN32)
    if (CMAKE_CL_64 STREQUAL "1")
        link_libraries(${NOESIS_ROOT_DIR}/Lib/windows_x86_64/Noesis.lib)
        link_libraries(${NOESIS_ROOT_DIR}/Lib/windows_x86_64/NoesisApp.lib)
    else()
        link_libraries(${NOESIS_ROOT_DIR}/Lib/windows_x86/Noesis.lib)
        link_libraries(${NOESIS_ROOT_DIR}/Lib/windows_x86/NoesisApp.lib)
    endif()
endif()

# Include header files.
include_directories(${NOESIS_ROOT_DIR}/Include)
include_directories(${NOESIS_PKG_DIR}/Render/RenderContext/Include)
include_directories(${NOESIS_PKG_DIR}/Render/GLRenderDevice/Include)
include_directories(${NOESIS_PKG_DIR}/App/Providers/Include)

# Copy binary dependencies.
if (WIN32)
    if (CMAKE_CL_64 STREQUAL "1")
        file(COPY "${NOESIS_ROOT_DIR}/Bin/windows_x86_64/Noesis.dll" DESTINATION ${PROJECT_SOURCE_DIR})
        file(COPY "${NOESIS_ROOT_DIR}/Bin/windows_x86_64/NoesisApp.dll" DESTINATION ${PROJECT_SOURCE_DIR})
    else()
        file(COPY "${NOESIS_ROOT_DIR}/Bin/windows_x86/Noesis.dll" DESTINATION ${PROJECT_SOURCE_DIR})
        file(COPY "${NOESIS_ROOT_DIR}/Bin/windows_x86/NoesisApp.dll" DESTINATION ${PROJECT_SOURCE_DIR})
    endif()
endif()

# Noesis licence information.
# This must be set at compile time.
set(NS_LICENSE_NAME "" CACHE STRING "Noesis License Name" FORCE)
set(NS_LICENSE_KEY "" CACHE STRING "Noesis License Key" FORCE)

add_definitions(-DNS_LICENSE_NAME="${NS_LICENSE_NAME}")
add_definitions(-DNS_LICENSE_KEY="${NS_LICENSE_KEY}")
