#pragma once
#ifndef CUSTOM_MODELS_PRIVATE_DEF
#define CUSTOM_MODELS_PRIVATE_DEF

#define BACKEND_PROV_OP_3(b0, cid)    ((((b0) << 16) | 0xD00000) | (cid))
#define SENSOR_PROV_OP_3(b0, cid)    ((((b0) << 16) | 0xE00000) | (cid))
#define SENSOR_PROV_OP_4(b0, cid)    ((((b0) << 16) | 0xF00000) | (cid))
#define SENSOR_PROV_OP_5(b0, cid)    ((((b0) << 16) | 0xC00000) | (cid))

//FOR PCS ONLY:these opcodes are hidden to backend, only can be configured through nRF Mesh phone app
#define ESP_BLE_MESH_VND_MODEL_OP_SET_SECONDARY_CHECK          SENSOR_PROV_OP_5(0x00, CID_ESP) //secondary check for PCS presence flag, can be enabled or disabled by setting a '1' or '0' in byte_4 of model_sensor_data_t
#define ESP_BLE_MESH_VND_MODEL_OP_SET_PCS_CONFIG_BLOB_SIZE     SENSOR_PROV_OP_5(0x01, CID_ESP) //set Blob size (see data sheet for PCS, default is 70)
#define ESP_BLE_MESH_VND_MODEL_OP_SET_PCS_CONFIG_IMG_THRESHOLD SENSOR_PROV_OP_5(0x02, CID_ESP) //set image threshold (see data sheet for PCS)
#define BLOB_SIZE_HOLDING_REG 0x0017
#define IMG_THRESHOLD_HOLDING_REG 0x0002
#define PRESENCE_INPUT_REG 0x0008
#define RECALIBRATE_THERMAL_REG 0x000D

//FOR MP555 ONLY:
#define MP555_DATA_OUTPUT 0x03001C
#define MP555_CLEAR_SUPPRESSION 0x060030
#define CLEAR 0x0000
#define CALIBRATE 0x0001
#define MP555_XMIN_CONFIG 0x060021
#define MP555_XMAX_CONFIG 0x060022
#define MP555_ZMIN_CONFIG 0x060023
#define MP555_ZMAX_CONFIG 0x060024
#define MP555_DEPLOYMENT_HEIGHT 0x060025
#define MP555_MOTION_THRESHOLD_DIST 0x060026
#define MP555_CLUSTER_SIZE 0x060028
#endif //CUSTOM_MODELS_PRIVATE_DEF