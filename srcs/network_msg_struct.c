#include "network_msg_struct.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <endian.h>
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
  if ( (opcode != ESP_BLE_MESH_VND_MODEL_OP_GET) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_STATUS) &&
      (opcode != ESP_BLE_MESH_VND_MODEL_OP_SET) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_SET_UNACK) && (opcode != ESP_BLE_MESH_VND_MODEL_OP_INTR_STATUS) )
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

uint8_t* set_sensor_data_msgA(uint32_t opcode, uint16_t addr, model_sensor_data_t *sensor_buf)
{
  static uint8_t buf[MSG_A_BYTES] ={0};
  if (sensor_buf == NULL)
    return NULL;
  //little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf+3, &addr, 2);
  memcpy(buf+5, sensor_buf, sizeof(model_sensor_data_t));
  uint16_t crc = CRCCCITT((uint8_t*)buf, MSG_A_BYTES-2); // generate crc checksum
  crc = htobe16(crc); //needs to be packed in big endian format to ensure checksum works
  memcpy(buf+sizeof(model_sensor_data_t)+5, &crc, 2);
  return buf;
}

uint8_t* set_bt_data_msgA(uint32_t opcode, uint16_t addr, cfg_state_t *state)
{
  static uint8_t buf[MSG_A_CONFIG_BYTES];
  if (state == NULL)
    return NULL;
  //little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf+3, &addr, 2);
  memcpy(buf+5, state, sizeof(cfg_state_t));
  uint16_t crc = CRCCCITT((uint8_t*)buf, MSG_A_CONFIG_BYTES-2); // generate crc checksum
  crc = htobe16(crc); //needs to be packed in big endian format to ensure checksum works
  memcpy(buf+sizeof(cfg_state_t)+5, &crc, 2);
  return buf;
}

int32_t extract_sensor_data_msgC(uint8_t *buf, model_sensor_data_t *sensor_buf)
{
  if (buf == NULL || sensor_buf == NULL)
    return -1;
  memcpy(sensor_buf, buf + 3, sizeof(model_sensor_data_t));
  return 0;
}

uint8_t* set_sensor_data_msgC(uint32_t opcode, model_sensor_data_t *sensor_buf)
{
  static uint8_t buf[MSG_C_BYTES] ={0};
  if (sensor_buf == NULL)
    return NULL;
  //little endian formatting
  memcpy(buf, &opcode, 3);
  memcpy(buf+3, sensor_buf, sizeof(model_sensor_data_t));
  uint16_t crc = CRCCCITT((uint8_t*)buf, MSG_C_BYTES-2); // generate crc checksum
  crc = htobe16(crc); //needs to be packed in big endian format to ensure checksum works
  memcpy(buf+sizeof(model_sensor_data_t)+3, &crc, 2);
  return buf;
}




