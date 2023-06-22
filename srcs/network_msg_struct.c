#include "network_msg_struct.h"
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>
#include "my_endian.h"
#include "my_crc.h"

uint32_t extract_opcode(uint8_t *buf)
{
  if (buf == NULL)
    return 0;
  uint32_t opcode = 0;
  opcode = ((*(buf + 2)) << 16) + ((*(buf + 1)) << 8) + ((*(buf)) << 0);
  return opcode;
}

uint16_t extract_addr(uint8_t *buf)
{
  if (buf == NULL)
    return 0;
  uint16_t unicast = 0;
  unicast = ((*(buf + 4)) << 8) + ((*(buf + 3)) << 0);
  return unicast;
}

int32_t extract_sensor_data_msgA(uint8_t *buf, model_sensor_data_t *sensor_buf)
{
  if (buf == NULL || sensor_buf == NULL)
  {
    return -1;
  }
  uint32_t opcode = extract_opcode(buf);
  if ((opcode != ESP_BLE_MESH_VND_MODEL_OP_GET) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_STATUS) &&
      (opcode != ESP_BLE_MESH_VND_MODEL_OP_SET) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_SET_UNACK) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_INTR_STATUS) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_HEALTH_STATUS) )
  {
    return -1;
  }
  memcpy(sensor_buf, buf + 5, sizeof(model_sensor_data_t));
  return 0;
}

int32_t extract_bt_data_msgA(uint8_t *buf, cfg_state_t *state)
{
  if (buf == NULL || state == NULL)
    return -1;
  memcpy(state, buf + 5, sizeof(*state));
  return 0;
}

int32_t extract_backend_prov_data_msgA(uint8_t *buf, backend_prov_data_t *prov_data)
{
  if (buf == NULL || prov_data == NULL)
    return -1;
  memcpy(prov_data, buf + 3, sizeof(*prov_data));
  return 0;
}

int32_t extract_all_node_data_msgA(uint8_t *buf, esp_ble_mesh_node_t **node_info)
{
  _Static_assert(sizeof(esp_ble_mesh_node_t) == 89,"platform must treat esp_ble_mesh_node_t as 89 bytes");  //sanity check for portability issues
  if (buf == NULL)
    return -1;
  int32_t node_num = 0;
  node_num = ((*(buf + 4)) << 8) + ((*(buf + 3)) << 0); //buffer's 4th and 5th byte is for node_num
  *node_info = NULL;
  *node_info = malloc(sizeof(esp_ble_mesh_node_t) * node_num);
  if (( *node_info) == NULL)
    return -1;
  memcpy( (*node_info), buf + 5, sizeof(esp_ble_mesh_node_t) * node_num); 
  return node_num;
}

void free_node_data(esp_ble_mesh_node_t** node_info)
{
  free(*node_info);
}

uint8_t *set_sensor_data_msgA(uint32_t opcode, uint16_t addr, model_sensor_data_t *sensor_buf)
{
  static uint8_t buf[MSG_A_BYTES] = {0};
  memset(buf, 0, MSG_A_BYTES);
  if (sensor_buf == NULL)
    return NULL;
  // little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf + 3, &addr, 2);
  memcpy(buf + 5, sensor_buf, sizeof(model_sensor_data_t));
  uint16_t crc = CRCCCITT((uint8_t *)buf, MSG_A_BYTES - 2); // generate crc checksum
  crc = htobe16(crc);                                       // needs to be packed in big endian format to ensure checksum works
  memcpy(buf + sizeof(model_sensor_data_t) + 5, &crc, 2);
  return buf;
}

uint8_t *set_bt_data_msgA(uint32_t opcode, uint16_t addr, cfg_state_t *state)
{
  _Static_assert(sizeof(cfg_state_t) == BLE_NET_CONFIG_PAYLOAD_BYTES,"platform must treat cfg_state_t as 28 bytes");  //sanity check for portability issues
  static uint8_t buf[MSG_A_CONFIG_BYTES] = {0};
  memset(buf, 0, MSG_A_CONFIG_BYTES);
  if (state == NULL)
    return NULL;
  // little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf + 3, &addr, 2);
  memcpy(buf + 5, state, sizeof(cfg_state_t));
  uint16_t crc = CRCCCITT((uint8_t *)buf, MSG_A_CONFIG_BYTES - 2); // generate crc checksum
  crc = htobe16(crc);                                              // needs to be packed in big endian format to ensure checksum works
  memcpy(buf + sizeof(cfg_state_t) + 5, &crc, 2);
  return buf;
}

uint8_t *set_backend_prov_data_msgA(uint32_t opcode, backend_prov_data_t *prov_data)
{
  static uint8_t buf[MSG_A_BACKEND_PROV_BYTES];
  memset(buf, 0, MSG_A_BACKEND_PROV_BYTES);
  if (prov_data == NULL)
    return NULL;
  // little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf + 3, prov_data, sizeof(backend_prov_data_t));
  uint16_t crc = CRCCCITT((uint8_t *)buf, MSG_A_BACKEND_PROV_BYTES - 2); // generate crc checksum
  crc = htobe16(crc);                                              // needs to be packed in big endian format to ensure checksum works
  memcpy(buf + sizeof(backend_prov_data_t) + 3, &crc, 2);
  return buf;
}

int32_t extract_sensor_data_msgC(uint8_t *buf, model_sensor_data_t *sensor_buf)
{
  if (buf == NULL || sensor_buf == NULL)
    return -1;
  memcpy(sensor_buf, buf + 3, sizeof(model_sensor_data_t));
  return 0;
}

uint8_t *set_sensor_data_msgC(uint32_t opcode, model_sensor_data_t *sensor_buf)
{
  static uint8_t buf[MSG_C_BYTES] = {0};
  memset(buf, 0, MSG_C_BYTES);
  if (sensor_buf == NULL)
    return NULL;
  // little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf + 3, sensor_buf, sizeof(model_sensor_data_t));
  uint16_t crc = CRCCCITT((uint8_t *)buf, MSG_C_BYTES - 2); // generate crc checksum
  crc = htobe16(crc);                                       // needs to be packed in big endian format to ensure checksum works
  memcpy(buf + sizeof(model_sensor_data_t) + 3, &crc, 2);
  return buf;
}
