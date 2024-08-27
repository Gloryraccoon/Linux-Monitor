set(SOURCES
    main.cpp
    rpc_manager.cpp
)

add_executable(server ${SOURCES})
target_link_libraries(server
    PUBLIC
    monitor_proto
)