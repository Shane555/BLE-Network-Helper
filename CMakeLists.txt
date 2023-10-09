cmake_minimum_required(VERSION 3.1.6)

project(network_msg_struct VERSION 0.1 DESCRIPTION "helper functions to pack/unpack BLE mesh messages")

#create install rule 
include(GNUInstallDirs)

add_library(network_msg_struct
    srcs/network_msg_struct.c
    srcs/my_crc.c
)
set_target_properties(network_msg_struct PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")

set_target_properties(network_msg_struct PROPERTIES VERSION ${PROJECT_VERSION})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/includes)
set_target_properties(network_msg_struct PROPERTIES PUBLIC_HEADER includes/network_msg_struct.h
                                                                  includes/my_custom_models_def.h
								                                  includes/my_custom_models_def_private.h
                                                                  includes/my_crc.h
                                                                  includes/esp_ble_mesh_defs.h
                                                                  includes/my_endian.h
                                                                  includes/esp_ble_mesh_config_model_api.h
                                                                  )


install(TARGETS network_msg_struct
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

