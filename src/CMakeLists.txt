
#add src files
set(${PROJECT_NAME}_Client_SRCS
    client/main.cpp
    client/testclient.cpp
    client/clientworker.cpp
)

set(${PROJECT_NAME}_Server_SRCS
    server/main.cpp
    server/testserver.cpp
)



#add static resources
qt5_add_resources(QML_SRCS qml.qrc)

# Build resources into object libraries to have target level dependencies

add_library(qml_resources OBJECT
    ${QML_SRCS}
)

# Build target executable

add_executable(${PROJECT_NAME}_Client
    ${${PROJECT_NAME}_Client_SRCS}
    $<TARGET_OBJECTS:qml_resources>
)

add_executable(${PROJECT_NAME}_Server
    ${${PROJECT_NAME}_Server_SRCS}
    $<TARGET_OBJECTS:qml_resources>
)

message(includedir ${CMAKE_CURRENT_BINARY_DIR}/../proto)
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../proto)


target_link_libraries(${PROJECT_NAME}_Client PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    gRPC::grpc++
    grpc_proto
    ${_REFLECTION}
)

target_link_libraries(${PROJECT_NAME}_Server PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    gRPC::grpc++
    grpc_proto
    ${_REFLECTION}
)

target_compile_definitions(${PROJECT_NAME}_Client PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_compile_definitions(${PROJECT_NAME}_Server PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
