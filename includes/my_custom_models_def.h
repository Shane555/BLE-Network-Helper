#pragma once
#ifndef CUSTOM_MODELS_DEF
#define CUSTOM_MODELS_DEF

#include <stdint.h>
#include "esp_ble_mesh_defs.h"

#define BACKEND_PROV_OP_3(b0, cid)    ((((b0) << 16) | 0xD00000) | (cid))
#define CID_ESP 0x02E5 //esp's company id for BLE
#define ESP_BLE_MESH_VND_MODEL_ID_CLIENT 0x0002
#define ESP_BLE_MESH_VND_MODEL_ID_SERVER 0x0003

#define ESP_BLE_MESH_VND_MODEL_OP_GET ESP_BLE_MESH_MODEL_OP_3(0x0A, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_STATUS ESP_BLE_MESH_MODEL_OP_3(0x0B, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_SET ESP_BLE_MESH_MODEL_OP_3(0x0C, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_SET_UNACK ESP_BLE_MESH_MODEL_OP_3(0x0D, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_INTR_STATUS ESP_BLE_MESH_MODEL_OP_3(0x0E, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_DUMMY_SET ESP_BLE_MESH_MODEL_OP_3(0x0F, CID_ESP)
#define ESP_BLE_MESH_VND_MODEL_OP_HEALTH_STATUS SENSOR_PROV_OP_3(0x0C, CID_ESP) //health status of sensors

#define PROV_MODE_SET BACKEND_PROV_OP_3(0x00, CID_ESP)
#define PROV_MODE_GET BACKEND_PROV_OP_3(0x01, CID_ESP)
#define PROV_MODE_STATUS BACKEND_PROV_OP_3(0x02, CID_ESP)
#define PROV_MODE_NODE_RESET BACKEND_PROV_OP_3(0x03, CID_ESP)
#define PROV_ADD_NETKEY BACKEND_PROV_OP_3(0x04, CID_ESP)
#define PROV_ADD_APPKEY BACKEND_PROV_OP_3(0x05, CID_ESP)
#define PROV_KEY_SUCCESS BACKEND_PROV_OP_3(0x06, CID_ESP)
#define PROV_KEY_FAIL BACKEND_PROV_OP_3(0x07, CID_ESP)
#define MESH_CLIENT_TIMEOUT BACKEND_PROV_OP_3(0x08, CID_ESP)
#define PROV_NODE_INFO BACKEND_PROV_OP_3(0x0F, CID_ESP)

#define SENSOR_PAYLOAD_BYTES 8
#define MSG_C_BYTES (SENSOR_PAYLOAD_BYTES+5)

#define MSG_A_BYTES (MSG_C_BYTES +2) //Msg A sensor format bytes
#define BLE_NET_CONFIG_PAYLOAD_BYTES 28 //bluetooth network config payload for message A(config message)
#define MSG_A_NON_NET_PAYLOAD 7  //non bluetooth config payload portions of MsgA config format
#define MSG_A_CONFIG_BYTES (BLE_NET_CONFIG_PAYLOAD_BYTES+MSG_A_NON_NET_PAYLOAD) //MsgA config format bytes
#define BACKEND_PROV_DATA_PAYLOAD_BYTES 8 //backend provisioning data payload, does not include PROV_NODE_INFO command 
#define MSG_A_BACKEND_PROV_BYTES (BACKEND_PROV_DATA_PAYLOAD_BYTES+5) //MsgA backend provision format bytes

//for client model usage
#define MSG_SEND_TTL 7
#define MSG_SEND_REL false
#define MSG_TIMEOUT 0
#define MSG_ROLE ROLE_NODE

typedef struct __attribute__((packed))
{
  uint8_t sensor_header;
  uint8_t byte1;
  uint8_t byte2;
  uint8_t byte3;
  uint8_t byte4;
  uint8_t byte5;
  uint8_t byte6;
  uint8_t byte7;
} model_sensor_data_t;


typedef struct {
  uint32_t prov_payload;
}prov_mode_get_t;

typedef struct {
  uint32_t prov_payload;
}prov_mode_set_t;

typedef struct {
  uint8_t prov_is_true;
}prov_mode_status_t;

typedef struct {
  uint32_t prov_payload;
}prov_mode_node_reset_t;

typedef struct {
  uint16_t net_idx;
}prov_add_netkey_t;

typedef struct {
  uint16_t net_idx;
  uint16_t app_idx;
}prov_add_appkey_t;

typedef struct {
  uint32_t opcode;
  uint16_t net_idx;
  uint16_t app_idx;
}prov_key_success_t;

typedef struct {
  uint32_t opcode;
}prov_key_fail_t;

typedef union {
  prov_mode_get_t prov_mode_get;
  prov_mode_set_t prov_mode_set;
  prov_mode_status_t prov_mode_status;
  prov_mode_node_reset_t prov_mode_node_reset;
  prov_add_netkey_t prov_add_net_key;
  prov_add_appkey_t prov_add_app_key;
  prov_key_success_t prov_key_success;
  prov_key_fail_t prov_key_fail;
} backend_prov_data_t;

#endif //CUSTOM_MODELS_DEF
