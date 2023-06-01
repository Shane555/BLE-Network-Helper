#pragma once
#ifndef CUSTOM_MODELS_PRIVATE_DEF
#define CUSTOM_MODELS_PRIVATE_DEF

#define BACKEND_PROV_OP_3(b0, cid)    ((((b0) << 16) | 0xD00000) | (cid))
#define SENSOR_PROV_OP_3(b0, cid)    ((((b0) << 16) | 0xE00000) | (cid))
#define SENSOR_PROV_OP_4(b0, cid)    ((((b0) << 16) | 0xF00000) | (cid))
#define SENSOR_PROV_OP_5(b0, cid)    ((((b0) << 16) | 0xC00000) | (cid))

//these opcodes are hidden to backend, only can be configured through nRF Mesh phone app
#define ESP_BLE_MESH_VND_MODEL_OP_SET_SECONDARY_CHECK          SENSOR_PROV_OP_5(0x00, CID_ESP) //secondary check for PCS presence flag, can be enabled or disabled by setting a '1' or '0' in byte_4 of model_sensor_data_t
#define ESP_BLE_MESH_VND_MODEL_OP_SET_PCS_CONFIG_BLOB_SIZE     SENSOR_PROV_OP_5(0x01, CID_ESP) //set Blob size (see data sheet for PCS, default is 70)
#define ESP_BLE_MESH_VND_MODEL_OP_SET_PCS_CONFIG_IMG_THRESHOLD SENSOR_PROV_OP_5(0x02, CID_ESP) //set image threshold (see data sheet for PCS)
#define BLOB_SIZE_HOLDING_REG 0x0017
#define IMG_THRESHOLD_HOLDING_REG 0x0002
#define PRESENCE_INPUT_REG 0x0008
#define RECALIBRATE_THERMAL_REG 0x000D
#endif //CUSTOM_MODELS_PRIVATE_DEF