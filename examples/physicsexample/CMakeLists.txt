add_executable( physicsexample physicsexample.cpp VPEConstraintDemos.cpp VPEConstraintDemos.hpp ${CMAKE_SOURCE_DIR}/include/VPE.hpp)

set_target_properties(physicsexample PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Release
    VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/Debug
)

# Link the VVE
set( VulkanEngine ${CMAKE_SOURCE_DIR}/../ViennaVulkanEngine )
include_directories(${VulkanEngine}/VulkanEngine)

target_include_directories(physicsexample PUBLIC
          ${CMAKE_SOURCE_DIR}/include
          ${VulkanEngine}/VulkanEngine
          ${VulkanEngine}/external/threadpool
          ${VulkanEngine}/external/stb
          ${VulkanEngine}/external/nuklear
          )

set(IRRKLANG_ROOT ${VulkanEngine}/external/irrKlang)
find_package(IrrKlang REQUIRED)
target_include_directories(physicsexample PUBLIC ${IRRKLANG_INCLUDE_DIR})
target_link_libraries(physicsexample ${IRRKLANG_LIBRARY})

find_package(ZLIB REQUIRED)
target_link_libraries(physicsexample ZLIB::ZLIB)

find_package(assimp REQUIRED)
target_include_directories(physicsexample PUBLIC ${assimp_INCLUDE_DIRS})
target_link_libraries(physicsexample assimp::assimp)

find_package(glm CONFIG REQUIRED)
target_include_directories(physicsexample PUBLIC ${glm_INCLUDE_DIRS})
target_link_libraries(physicsexample glm)

find_package(glfw3 CONFIG REQUIRED)
target_include_directories(physicsexample PUBLIC ${glfw_INCLUDE_DIRS})
target_link_libraries(physicsexample glfw)

add_library(VulkanEngineLib STATIC IMPORTED)
set_target_properties(VulkanEngineLib PROPERTIES
             IMPORTED_CONFIGURATIONS "Debug;Release"
             IMPORTED_LOCATION ${VulkanEngine}/lib/libvulkanengine.a
             IMPORTED_LOCATION_DEBUG ${VulkanEngine}/lib/libvulkanengine.a
             )

target_link_libraries(physicsexample VulkanEngineLib)
