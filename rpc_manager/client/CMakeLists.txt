set(SOURCES
    rpc_client.cpp
)

add_library(client  ${SOURCES})

target_link_libraries(client
    PUBLIC
    monitor_proto

)