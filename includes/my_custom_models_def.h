#pragma once
#ifndef CUSTOM_MODELS_DEF
#define CUSTOM_MODELS_DEF

#include <stdint.h>
#include "esp_ble_mesh_defs.h"

#define CID_ESP 0x02E5 //esp's company id for BLE
#define ESP_BLE_MESH_VND_MODEL_ID_CLIENT 0x0002
#define ESP_BLE_MESH_VND_MODEL_ID_SERVER 0x0003

#define ESP_BLE_MESH_VND_MODEL_OP_GET ESP_BLE_MESH_MODEL_OP_3(0x0A, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_STATUS ESP_BLE_MESH_MODEL_OP_3(0x0B, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_SET ESP_BLE_MESH_MODEL_OP_3(0x0C, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_SET_UNACK ESP_BLE_MESH_MODEL_OP_3(0x0D, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_INTR_STATUS ESP_BLE_MESH_MODEL_OP_3(0x0E, CID_ESP)

#define SENSOR_PAYLOAD_BYTES 5
#define MSG_C_BYTES (SENSOR_PAYLOAD_BYTES+5)

#define MSG_A_BYTES (MSG_C_BYTES +2) //Msg A sensor format bytes
#define BLE_NET_CONFIG_PAYLOAD_BYTES 28 //bluetooth network config payload for message A(config message)
#define MSG_A_NON_NET_PAYLOAD 7  //non bluetooth config payload portions of MsgA config format
#define MSG_A_CONFIG_BYTES (BLE_NET_CONFIG_PAYLOAD_BYTES+MSG_A_NON_NET_PAYLOAD) //MsgA config format bytes

//for client model usage
#define MSG_SEND_TTL 7
#define MSG_SEND_REL false
#define MSG_TIMEOUT 0
#define MSG_ROLE ROLE_NODE

typedef struct __attribute__((packed))
{
  uint8_t byte0;
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;
} model_sensor_data_t;


#endif //CUSTOM_MODELS_DEF