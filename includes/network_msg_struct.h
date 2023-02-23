/**
 * @file network_msg_struct.h
 * @author Shane
 * @brief helper functions to pack/unpack BLE Mesh messages(format A, format C)
 * @version 0.1
 * @date 2023-02-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#ifndef NET_MSG_STRUCT
#define NET_MSG_STRUCT

#if defined (__GLIBC__)
# include <endian.h>
# if (__BYTE_ORDER == __LITTLE_ENDIAN)
#else
#error "invalid endianness"
#endif
#endif

#include "esp_ble_mesh_defs.h"
#include "esp_ble_mesh_config_model_api.h"
#include "my_custom_models_def.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef union 
{
  esp_ble_mesh_cfg_client_get_state_t get_state;
  esp_ble_mesh_cfg_client_set_state_t set_state;
}cfg_state_t;

/**
 * @brief extract opcode segment from any message. 
 * 
 * @param buf pointer to message
 * @return uint32_t opcode, 0 if fail
 */
uint32_t extract_opcode(uint8_t *buf);

/**
 * @brief extract address segment from message A.
 * 
 * @param buf pointer to message A
 * @return uint16_t unicast addr or group addr, 0 if fail
 */
uint16_t extract_addr(uint8_t *buf);

/**
 * @brief extract sensor data payload from buf to store in sensor_buf
 * 
 * @param buf buf should have enough data allocated and user should ensure it contains message A sensor msg format
 * @param sensor_buf empty buffer to store sensor data, must be initialised first
 * @return returns 0 if successful, -1 if fail. Note: returning 0 does not guarantee succcess unless buf contains correct data
 */
int32_t extract_sensor_data_msgA(uint8_t *buf, model_sensor_data_t *sensor_buf);

/**
 * @brief extract bluetooth config data payload from buf to store in cfg_state_t state
 * 
 * @param buf buf should have enough data allocated and user should ensure it contains message A bluetooth config msg format
 * @param state empty buffer to store bt config data, must be initialised first
 * @return returns 0 if successful, -1 if fail. Note: returning 0 does not guarantee succcess unless buf contains correct data
 */
int32_t extract_bt_data_msgA(uint8_t* buf, cfg_state_t* state);

/**
 * @brief Set the buffer containing sensor message A , which includes generating and setting the crc in message A
 * 
 * @param opcode opcode of command 
 * @param addr destination address
 * @param sensor_buf valid sensor data pointer
 * @return returns pointer to buffer(static define, not thread-safe) containing message A if successful, NULL if fail. Note: returning valid pointer does not guarantee succcess unless sensor_buf contains correct data
 */
uint8_t* set_sensor_data_msgA(uint32_t opcode, uint16_t addr, model_sensor_data_t *sensor_buf);

/**
 * @brief Set the buffer containing bt message A , which includes generating and setting the crc in message A
 * 
 * @param opcode opcode of command
 * @param addr destination address
 * @param state valid bt config data pointer
 * @return returns pointer to buffer(static define, not thread-safe) containing message A if successful, NULL if fail. Note: returning valid pointer does not guarantee succcess unless state contains correct data
 */
uint8_t* set_bt_data_msgA(uint32_t opcode, uint16_t addr, cfg_state_t *state);

/**
 * @brief extract sensor data payload from buf to store in sensor_buf
 * 
 * @param buf buf should have enough data allocated and user should ensure it contains message C msg format
 * @param sensor_buf empty buffer to store sensor data, must be initialised first
 * @return returns 0 if successful, -1 if fail. Note: returning 0 does not guarantee succcess unless buf contains correct data
 */
int32_t extract_sensor_data_msgC(uint8_t *buf, model_sensor_data_t* sensor_buf);

/**
 * @brief Set the buffer containing message C , which includes generating and setting the crc in message C
 * 
 * @param opcode opcode of command 
 * @param addr destination address
 * @param sensor_buf valid sensor data pointer
 * @return returns pointer to buffer(static define, not thread-safe) containing message C if successful, NULL if fail. Note: returning valid pointer does not guarantee succcess unless sensor_buf contains correct data
 */
uint8_t* set_sensor_data_msgC(uint32_t opcode, model_sensor_data_t *sensor_buf);


#ifdef __cplusplus
}
#endif

#endif /* NET_MSG_STRUCT */
