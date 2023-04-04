/*
 * SPDX-FileCopyrightText: 2017-2021 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ESP_BLE_MESH_DEFS_H_
#define _ESP_BLE_MESH_DEFS_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*!< The maximum length of a BLE Mesh message, including Opcode, Payload and TransMIC */
#define ESP_BLE_MESH_SDU_MAX_LEN            384

/*!< Length of a short Mesh MIC. */
#define ESP_BLE_MESH_MIC_SHORT              4

/*!< Length of a long Mesh MIC. */
#define ESP_BLE_MESH_MIC_LONG               8

/*!< The maximum length of a BLE Mesh provisioned node name */
#define ESP_BLE_MESH_NODE_NAME_MAX_LEN      31

/*!< The maximum length of a BLE Mesh unprovisioned device name */
#define ESP_BLE_MESH_DEVICE_NAME_MAX_LEN    DEVICE_NAME_SIZE

/*!< The maximum length of settings user id */
#define ESP_BLE_MESH_SETTINGS_UID_SIZE      20

/*!< Invalid settings index */
#define ESP_BLE_MESH_INVALID_SETTINGS_IDX   0xFF

/*!< Define the BLE Mesh octet 16 bytes size */
#define ESP_BLE_MESH_OCTET16_LEN    16
typedef uint8_t esp_ble_mesh_octet16_t[ESP_BLE_MESH_OCTET16_LEN];

/*!< Define the BLE Mesh octet 8 bytes size */
#define ESP_BLE_MESH_OCTET8_LEN     8
typedef uint8_t esp_ble_mesh_octet8_t[ESP_BLE_MESH_OCTET8_LEN];

/*!< Invalid Company ID */
#define ESP_BLE_MESH_CID_NVAL                     0xFFFF

/*!< Special TTL value to request using configured default TTL */
#define ESP_BLE_MESH_TTL_DEFAULT                  0xFF

/*!< Maximum allowed TTL value */
#define ESP_BLE_MESH_TTL_MAX                      0x7F

#define ESP_BLE_MESH_ADDR_UNASSIGNED              0x0000
#define ESP_BLE_MESH_ADDR_ALL_NODES               0xFFFF
#define ESP_BLE_MESH_ADDR_PROXIES                 0xFFFC
#define ESP_BLE_MESH_ADDR_FRIENDS                 0xFFFD
#define ESP_BLE_MESH_ADDR_RELAYS                  0xFFFE

#define ESP_BLE_MESH_KEY_UNUSED                   0xFFFF
#define ESP_BLE_MESH_KEY_DEV                      0xFFFE

#define ESP_BLE_MESH_KEY_PRIMARY                  0x0000
#define ESP_BLE_MESH_KEY_ANY                      0xFFFF

/*!< Primary Network Key index */
#define ESP_BLE_MESH_NET_PRIMARY                  0x000

/*!< Relay state value */
#define ESP_BLE_MESH_RELAY_DISABLED               0x00
#define ESP_BLE_MESH_RELAY_ENABLED                0x01
#define ESP_BLE_MESH_RELAY_NOT_SUPPORTED          0x02

/*!< Beacon state value */
#define ESP_BLE_MESH_BEACON_DISABLED              0x00
#define ESP_BLE_MESH_BEACON_ENABLED               0x01

/*!< GATT Proxy state value */
#define ESP_BLE_MESH_GATT_PROXY_DISABLED          0x00
#define ESP_BLE_MESH_GATT_PROXY_ENABLED           0x01
#define ESP_BLE_MESH_GATT_PROXY_NOT_SUPPORTED     0x02

/*!< Friend state value */
#define ESP_BLE_MESH_FRIEND_DISABLED              0x00
#define ESP_BLE_MESH_FRIEND_ENABLED               0x01
#define ESP_BLE_MESH_FRIEND_NOT_SUPPORTED         0x02

/*!< Node identity state value */
#define ESP_BLE_MESH_NODE_IDENTITY_STOPPED        0x00
#define ESP_BLE_MESH_NODE_IDENTITY_RUNNING        0x01
#define ESP_BLE_MESH_NODE_IDENTITY_NOT_SUPPORTED  0x02

/*!< Supported features */
#define ESP_BLE_MESH_FEATURE_RELAY                BIT(0)
#define ESP_BLE_MESH_FEATURE_PROXY                BIT(1)
#define ESP_BLE_MESH_FEATURE_FRIEND               BIT(2)
#define ESP_BLE_MESH_FEATURE_LOW_POWER            BIT(3)
#define ESP_BLE_MESH_FEATURE_ALL_SUPPORTED        (ESP_BLE_MESH_FEATURE_RELAY |     \
                                                   ESP_BLE_MESH_FEATURE_PROXY |     \
                                                   ESP_BLE_MESH_FEATURE_FRIEND |    \
                                                   ESP_BLE_MESH_FEATURE_LOW_POWER)

#define ESP_BLE_MESH_ADDR_IS_UNICAST(addr)        ((addr) && (addr) < 0x8000)
#define ESP_BLE_MESH_ADDR_IS_GROUP(addr)          ((addr) >= 0xC000 && (addr) <= 0xFF00)
#define ESP_BLE_MESH_ADDR_IS_VIRTUAL(addr)        ((addr) >= 0x8000 && (addr) < 0xC000)
#define ESP_BLE_MESH_ADDR_IS_RFU(addr)            ((addr) >= 0xFF00 && (addr) <= 0xFFFB)


/*!< Macros used to define message opcode */
#define ESP_BLE_MESH_MODEL_OP_1(b0)         (b0)
#define ESP_BLE_MESH_MODEL_OP_2(b0, b1)     (((b0) << 8) | (b1))
#define ESP_BLE_MESH_MODEL_OP_3(b0, cid)    ((((b0) << 16) | 0xC00000) | (cid))
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT
     */
    extern struct ble_mesh_provisioner_prov_comp_param {
        uint16_t node_idx;                      /*!< Index of the provisioned device */
        esp_ble_mesh_octet16_t device_uuid;     /*!< Device UUID of the provisioned device */
        uint16_t unicast_addr;                  /*!< Primary address of the provisioned device */
        uint8_t element_num;                    /*!< Element count of the provisioned device */
        uint16_t netkey_idx;                    /*!< NetKey Index of the provisioned device */
    } provisioner_prov_complete;                /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_PROV_COMPLETE_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT
     */
    extern struct ble_mesh_provisioner_add_unprov_dev_comp_param {
        int err_code;                           /*!< Indicate the result of adding device into queue by the Provisioner */
    } provisioner_add_unprov_dev_comp;          /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_ADD_UNPROV_DEV_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_DEV_WITH_ADDR_COMP_EVT
     */
    extern struct ble_mesh_provisioner_prov_dev_with_addr_comp_param {
        int err_code;                           /*!< Indicate the result of Provisioner starting to provision a device */
    } provisioner_prov_dev_with_addr_comp;      /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_PROV_DEV_WITH_ADDR_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT
     */
    extern struct ble_mesh_provisioner_delete_dev_comp_param {
        int err_code;                           /*!< Indicate the result of deleting device by the Provisioner */
    } provisioner_delete_dev_comp;              /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_DELETE_DEV_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT
     */
    extern struct ble_mesh_provisioner_set_dev_uuid_match_comp_param {
        int err_code;                           /*!< Indicate the result of setting Device UUID match value by the Provisioner */
    } provisioner_set_dev_uuid_match_comp;      /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_SET_DEV_UUID_MATCH_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT
     */
    extern struct ble_mesh_provisioner_set_prov_data_info_comp_param {
        int err_code;                           /*!< Indicate the result of setting provisioning info by the Provisioner */
    } provisioner_set_prov_data_info_comp;      /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_SET_PROV_DATA_INFO_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_STATIC_OOB_VALUE_COMP_EVT
     */
    extern struct ble_mesh_provisioner_set_static_oob_val_comp_param {
        int err_code;                           /*!< Indicate the result of setting static oob value by the Provisioner */
    } provisioner_set_static_oob_val_comp;      /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_SET_STATIC_OOB_VALUE_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_PRIMARY_ELEM_ADDR_COMP_EVT
     */
    extern struct ble_mesh_provisioner_set_primary_elem_addr_comp_param {
        int err_code;                           /*!< Indicate the result of setting unicast address of primary element by the Provisioner */
    } provisioner_set_primary_elem_addr_comp;   /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_SET_PRIMARY_ELEM_ADDR_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_COMP_EVT
     */
    extern struct ble_mesh_provisioner_prov_read_oob_pub_key_comp_param {
        int err_code;                           /*!< Indicate the result of setting OOB Public Key by the Provisioner */
    } provisioner_prov_read_oob_pub_key_comp;   /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_PROV_READ_OOB_PUB_KEY_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_INPUT_NUMBER_COMP_EVT
     */
    extern struct ble_mesh_provisioner_prov_input_num_comp_param {
        int err_code;                           /*!< Indicate the result of inputting number by the Provisioner */
    } provisioner_prov_input_num_comp;          /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_PROV_INPUT_NUMBER_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_PROV_INPUT_STRING_COMP_EVT
     */
    extern struct ble_mesh_provisioner_prov_input_str_comp_param {
        int err_code;                           /*!< Indicate the result of inputting string by the Provisioner */
    } provisioner_prov_input_str_comp;          /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_PROV_INPUT_STRING_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT
     */
    extern struct ble_mesh_provisioner_set_node_name_comp_param {
        int err_code;                           /*!< Indicate the result of setting provisioned device name by the Provisioner */
        uint16_t node_index;                    /*!< Index of the provisioned device */
    } provisioner_set_node_name_comp;           /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_SET_NODE_NAME_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT
     */
    extern struct ble_mesh_provisioner_add_local_app_key_comp_param {
        int err_code;                           /*!< Indicate the result of adding local AppKey by the Provisioner */
        uint16_t net_idx;                       /*!< NetKey Index */
        uint16_t app_idx;                       /*!< AppKey Index */
    } provisioner_add_app_key_comp;             /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_APP_KEY_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_APP_KEY_COMP_EVT
     */
    extern struct ble_mesh_provisioner_update_local_app_key_comp_param {
        int err_code;                           /*!< Indicate the result of updating local AppKey by the Provisioner */
        uint16_t net_idx;                       /*!< NetKey Index */
        uint16_t app_idx;                       /*!< AppKey Index */
    } provisioner_update_app_key_comp;          /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_APP_KEY_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT
     */
    extern struct ble_mesh_provisioner_bind_local_mod_app_comp_param {
        int err_code;                           /*!< Indicate the result of binding AppKey with model by the Provisioner */
        uint16_t element_addr;                  /*!< Element address */
        uint16_t app_idx;                       /*!< AppKey Index */
        uint16_t company_id;                    /*!< Company ID */
        uint16_t model_id;                      /*!< Model ID */
    } provisioner_bind_app_key_to_model_comp;   /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_BIND_APP_KEY_TO_MODEL_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT
     */
    extern struct ble_mesh_provisioner_add_local_net_key_comp_param {
        int err_code;                           /*!< Indicate the result of adding local NetKey by the Provisioner */
        uint16_t net_idx;                       /*!< NetKey Index */
    } provisioner_add_net_key_comp;             /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_ADD_LOCAL_NET_KEY_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_NET_KEY_COMP_EVT
     */
    extern struct ble_mesh_provisioner_update_local_net_key_comp_param {
        int err_code;                           /*!< Indicate the result of updating local NetKey by the Provisioner */
        uint16_t net_idx;                       /*!< NetKey Index */
    } provisioner_update_net_key_comp;          /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_UPDATE_LOCAL_NET_KEY_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_STORE_NODE_COMP_DATA_COMP_EVT
     */
    extern struct ble_mesh_provisioner_store_node_comp_data_comp_param {
        int err_code;                           /*!< Indicate the result of storing node composition data by the Provisioner */
        uint16_t addr;                          /*!< Node element address */
    } provisioner_store_node_comp_data_comp;    /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_STORE_NODE_COMP_DATA_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_UUID_COMP_EVT
     */
    extern struct ble_mesh_provisioner_delete_node_with_uuid_comp_param {
        int err_code;                           /*!< Indicate the result of deleting node with uuid by the Provisioner */
        uint8_t uuid[16];                       /*!< Node device uuid */
    } provisioner_delete_node_with_uuid_comp;   /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_UUID_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_ADDR_COMP_EVT
     */
    extern struct ble_mesh_provisioner_delete_node_with_addr_comp_param {
        int err_code;                           /*!< Indicate the result of deleting node with unicast address by the Provisioner */
        uint16_t unicast_addr;                  /*!< Node unicast address */
    } provisioner_delete_node_with_addr_comp;   /*!< Event parameter of ESP_BLE_MESH_PROVISIONER_DELETE_NODE_WITH_ADDR_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_ENABLE_HEARTBEAT_RECV_COMP_EVT
     */
    extern struct {
        int err_code;                           /*!< Indicate the result of enabling/disabling to receive heartbeat messages by the Provisioner */
        bool enable;                            /*!< Indicate enabling or disabling receiving heartbeat messages */
    } provisioner_enable_heartbeat_recv_comp;   /*!< Event parameters of ESP_BLE_MESH_PROVISIONER_ENABLE_HEARTBEAT_RECV_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_TYPE_COMP_EVT
     */
    extern struct {
        int err_code;                               /*!< Indicate the result of setting the heartbeat filter type by the Provisioner */
        uint8_t type;                               /*!< Type of the filter used for receiving heartbeat messages */
    } provisioner_set_heartbeat_filter_type_comp;   /*!< Event parameters of ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_TYPE_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_INFO_COMP_EVT
     */
    extern struct {
        int err_code;                               /*!< Indicate the result of setting the heartbeat filter address by the Provisioner */
        uint8_t  op;                                /*!< Operation (add, remove, clean) */
        uint16_t hb_src;                            /*!< Heartbeat source address */
        uint16_t hb_dst;                            /*!< Heartbeat destination address */
    } provisioner_set_heartbeat_filter_info_comp;   /*!< Event parameters of ESP_BLE_MESH_PROVISIONER_SET_HEARTBEAT_FILTER_INFO_COMP_EVT */
    /**
     * @brief ESP_BLE_MESH_PROVISIONER_RECV_HEARTBEAT_MESSAGE_EVT
     */
    extern struct {
        uint16_t hb_src;            /*!< Heartbeat source address */
        uint16_t hb_dst;            /*!< Heartbeat destination address */
        uint8_t  init_ttl;          /*!< Heartbeat InitTTL */
        uint8_t  rx_ttl;            /*!< Heartbeat RxTTL */
        uint8_t  hops;              /*!< Heartbeat hops (InitTTL - RxTTL + 1) */
        uint16_t feature;           /*!< Bit field of currently active features of the node */
        int8_t   rssi;              /*!< RSSI of the heartbeat message */
    } provisioner_recv_heartbeat;   /*!< Event parameters of ESP_BLE_MESH_PROVISIONER_RECV_HEARTBEAT_MESSAGE_EVT */


/**
 * @brief BLE Mesh models related Model ID and Opcode definitions
 */

/*!< Foundation Models */
#define ESP_BLE_MESH_MODEL_ID_CONFIG_SRV                            0x0000
#define ESP_BLE_MESH_MODEL_ID_CONFIG_CLI                            0x0001
#define ESP_BLE_MESH_MODEL_ID_HEALTH_SRV                            0x0002
#define ESP_BLE_MESH_MODEL_ID_HEALTH_CLI                            0x0003

/*!< Models from the Mesh Model Specification */
#define ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_SRV                         0x1000
#define ESP_BLE_MESH_MODEL_ID_GEN_ONOFF_CLI                         0x1001
#define ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_SRV                         0x1002
#define ESP_BLE_MESH_MODEL_ID_GEN_LEVEL_CLI                         0x1003
#define ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_SRV                0x1004
#define ESP_BLE_MESH_MODEL_ID_GEN_DEF_TRANS_TIME_CLI                0x1005
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SRV                   0x1006
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_SETUP_SRV             0x1007
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_ONOFF_CLI                   0x1008
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SRV                   0x1009
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_SETUP_SRV             0x100a
#define ESP_BLE_MESH_MODEL_ID_GEN_POWER_LEVEL_CLI                   0x100b
#define ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_SRV                       0x100c
#define ESP_BLE_MESH_MODEL_ID_GEN_BATTERY_CLI                       0x100d
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SRV                      0x100e
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_SETUP_SRV                0x100f
#define ESP_BLE_MESH_MODEL_ID_GEN_LOCATION_CLI                      0x1010
#define ESP_BLE_MESH_MODEL_ID_GEN_ADMIN_PROP_SRV                    0x1011
#define ESP_BLE_MESH_MODEL_ID_GEN_MANUFACTURER_PROP_SRV             0x1012
#define ESP_BLE_MESH_MODEL_ID_GEN_USER_PROP_SRV                     0x1013
#define ESP_BLE_MESH_MODEL_ID_GEN_CLIENT_PROP_SRV                   0x1014
#define ESP_BLE_MESH_MODEL_ID_GEN_PROP_CLI                          0x1015
#define ESP_BLE_MESH_MODEL_ID_SENSOR_SRV                            0x1100
#define ESP_BLE_MESH_MODEL_ID_SENSOR_SETUP_SRV                      0x1101
#define ESP_BLE_MESH_MODEL_ID_SENSOR_CLI                            0x1102
#define ESP_BLE_MESH_MODEL_ID_TIME_SRV                              0x1200
#define ESP_BLE_MESH_MODEL_ID_TIME_SETUP_SRV                        0x1201
#define ESP_BLE_MESH_MODEL_ID_TIME_CLI                              0x1202
#define ESP_BLE_MESH_MODEL_ID_SCENE_SRV                             0x1203
#define ESP_BLE_MESH_MODEL_ID_SCENE_SETUP_SRV                       0x1204
#define ESP_BLE_MESH_MODEL_ID_SCENE_CLI                             0x1205
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_SRV                         0x1206
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_SETUP_SRV                   0x1207
#define ESP_BLE_MESH_MODEL_ID_SCHEDULER_CLI                         0x1208
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SRV                   0x1300
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_SETUP_SRV             0x1301
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LIGHTNESS_CLI                   0x1302
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SRV                         0x1303
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_SETUP_SRV                   0x1304
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_CLI                         0x1305
#define ESP_BLE_MESH_MODEL_ID_LIGHT_CTL_TEMP_SRV                    0x1306
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SRV                         0x1307
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SETUP_SRV                   0x1308
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_CLI                         0x1309
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_HUE_SRV                     0x130a
#define ESP_BLE_MESH_MODEL_ID_LIGHT_HSL_SAT_SRV                     0x130b
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SRV                         0x130c
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_SETUP_SRV                   0x130d
#define ESP_BLE_MESH_MODEL_ID_LIGHT_XYL_CLI                         0x130e
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SRV                          0x130f
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_SETUP_SRV                    0x1310
#define ESP_BLE_MESH_MODEL_ID_LIGHT_LC_CLI                          0x1311

/**
 * esp_ble_mesh_opcode_config_client_get_t belongs to esp_ble_mesh_opcode_t, this typedef is only
 * used to locate the opcodes used by esp_ble_mesh_config_client_get_state.
 * The following opcodes will only be used in the esp_ble_mesh_config_client_get_state function.
 */
typedef uint32_t esp_ble_mesh_opcode_config_client_get_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_GET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x09) /*!< Config Beacon Get */
#define ESP_BLE_MESH_MODEL_OP_COMPOSITION_DATA_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x08) /*!< Config Composition Data Get */
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_GET                       ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0C) /*!< Config Default TTL Get */
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_GET                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x12) /*!< Config GATT Proxy Get */
#define ESP_BLE_MESH_MODEL_OP_RELAY_GET                             ESP_BLE_MESH_MODEL_OP_2(0x80, 0x26) /*!< Config Relay Get */
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_GET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x18) /*!< Config Model Publication Get */
#define ESP_BLE_MESH_MODEL_OP_FRIEND_GET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0F) /*!< Config Friend Get */
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x38) /*!< Config Heartbeat Publication Get */
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3a) /*!< Config Heartbeat Subscription Get */
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_GET                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x42) /*!< Config NetKey Get */
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_GET                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x01) /*!< Config AppKey Get */
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x46) /*!< Config Node Identity Get */
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_SUB_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x29) /*!< Config SIG Model Subscription Get */
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_SUB_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2B) /*!< Config Vendor Model Subscription Get */
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_APP_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4B) /*!< Config SIG Model App Get */
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_APP_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4D) /*!< Config Vendor Model App Get */
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_GET                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x15) /*!< Config Key Refresh Phase Get */
#define ESP_BLE_MESH_MODEL_OP_LPN_POLLTIMEOUT_GET                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2D) /*!< Config Low Power Node PollTimeout Get */
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_GET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x23) /*!< Config Network Transmit Get */

/**
 * esp_ble_mesh_opcode_config_client_set_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by esp_ble_mesh_config_client_set_state.
 * The following opcodes will only be used in the esp_ble_mesh_config_client_set_state function.
 */
typedef uint32_t esp_ble_mesh_opcode_config_client_set_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_SET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0A) /*!< Config Beacon Set */
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_SET                       ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0D) /*!< Config Default TTL Set */
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_SET                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x13) /*!< Config GATT Proxy Set */
#define ESP_BLE_MESH_MODEL_OP_RELAY_SET                             ESP_BLE_MESH_MODEL_OP_2(0x80, 0x27) /*!< Config Relay Set */
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_SET                         ESP_BLE_MESH_MODEL_OP_1(0x03)       /*!< Config Model Publication Set */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_ADD                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1B) /*!< Config Model Subscription Add */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_ADD            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x20) /*!< Config Model Subscription Virtual Address Add */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1C) /*!< Config Model Subscription Delete */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_DELETE         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x21) /*!< Config Model Subscription Virtual Address Delete */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_OVERWRITE                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1E) /*!< Config Model Subscription Overwrite */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_VIRTUAL_ADDR_OVERWRITE      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x22) /*!< Config Model Subscription Virtual Address Overwrite */
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_ADD                           ESP_BLE_MESH_MODEL_OP_2(0x80, 0x40) /*!< Config NetKey Add */
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_ADD                           ESP_BLE_MESH_MODEL_OP_1(0x00)       /*!< Config AppKey Add */
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_BIND                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3D) /*!< Config Model App Bind */
#define ESP_BLE_MESH_MODEL_OP_NODE_RESET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x49) /*!< Config Node Reset */
#define ESP_BLE_MESH_MODEL_OP_FRIEND_SET                            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x10) /*!< Config Friend Set */
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x39) /*!< Config Heartbeat Publication Set */
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3B) /*!< Config Heartbeat Subscription Set */
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_UPDATE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x45) /*!< Config NetKey Update */
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_DELETE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x41) /*!< Config NetKey Delete */
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_UPDATE                        ESP_BLE_MESH_MODEL_OP_1(0x01)       /*!< Config AppKey Update */
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_DELETE                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x00) /*!< Config AppKey Delete */
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x47) /*!< Config Node Identity Set */
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_SET                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x16) /*!< Config Key Refresh Phase Set */
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_VIRTUAL_ADDR_SET            ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1A) /*!< Config Model Publication Virtual Address Set */
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_DELETE_ALL                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1D) /*!< Config Model Subscription Delete All */
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_UNBIND                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3F) /*!< Config Model App Unbind */
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_SET                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x24) /*!< Config Network Transmit Set */

/**
 * esp_ble_mesh_opcode_config_status_t belongs to esp_ble_mesh_opcode_t, this typedef is only
 * used to locate the opcodes used by the Config Model messages
 * The following opcodes are used by the BLE Mesh Config Server Model internally to respond
 * to the Config Client Model's request messages.
 */
typedef uint32_t esp_ble_mesh_opcode_config_status_t;

#define ESP_BLE_MESH_MODEL_OP_BEACON_STATUS                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0B)
#define ESP_BLE_MESH_MODEL_OP_COMPOSITION_DATA_STATUS               ESP_BLE_MESH_MODEL_OP_1(0x02)
#define ESP_BLE_MESH_MODEL_OP_DEFAULT_TTL_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x0E)
#define ESP_BLE_MESH_MODEL_OP_GATT_PROXY_STATUS                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x14)
#define ESP_BLE_MESH_MODEL_OP_RELAY_STATUS                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x28)
#define ESP_BLE_MESH_MODEL_OP_MODEL_PUB_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x19)
#define ESP_BLE_MESH_MODEL_OP_MODEL_SUB_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x1F)
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_SUB_LIST                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2A)
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_SUB_LIST                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2C)
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_STATUS                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x44)
#define ESP_BLE_MESH_MODEL_OP_NET_KEY_LIST                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x43)
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_STATUS                        ESP_BLE_MESH_MODEL_OP_2(0x80, 0x03)
#define ESP_BLE_MESH_MODEL_OP_APP_KEY_LIST                          ESP_BLE_MESH_MODEL_OP_2(0x80, 0x02)
#define ESP_BLE_MESH_MODEL_OP_NODE_IDENTITY_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x48)
#define ESP_BLE_MESH_MODEL_OP_MODEL_APP_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3E)
#define ESP_BLE_MESH_MODEL_OP_SIG_MODEL_APP_LIST                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4C)
#define ESP_BLE_MESH_MODEL_OP_VENDOR_MODEL_APP_LIST                 ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4E)
#define ESP_BLE_MESH_MODEL_OP_NODE_RESET_STATUS                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x4A)
#define ESP_BLE_MESH_MODEL_OP_FRIEND_STATUS                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x11)
#define ESP_BLE_MESH_MODEL_OP_KEY_REFRESH_PHASE_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x80, 0x17)
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_PUB_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x06)
#define ESP_BLE_MESH_MODEL_OP_HEARTBEAT_SUB_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x3C)
#define ESP_BLE_MESH_MODEL_OP_LPN_POLLTIMEOUT_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2E)
#define ESP_BLE_MESH_MODEL_OP_NETWORK_TRANSMIT_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x25)

/**
 * This typedef is only used to indicate the status code contained in some of
 * the Configuration Server Model status message.
 */
typedef uint8_t esp_ble_mesh_cfg_status_t;

#define ESP_BLE_MESH_CFG_STATUS_SUCCESS                             0x00
#define ESP_BLE_MESH_CFG_STATUS_INVALID_ADDRESS                     0x01
#define ESP_BLE_MESH_CFG_STATUS_INVALID_MODEL                       0x02
#define ESP_BLE_MESH_CFG_STATUS_INVALID_APPKEY                      0x03
#define ESP_BLE_MESH_CFG_STATUS_INVALID_NETKEY                      0x04
#define ESP_BLE_MESH_CFG_STATUS_INSUFFICIENT_RESOURCES              0x05
#define ESP_BLE_MESH_CFG_STATUS_KEY_INDEX_ALREADY_STORED            0x06
#define ESP_BLE_MESH_CFG_STATUS_INVALID_PUBLISH_PARAMETERS          0x07
#define ESP_BLE_MESH_CFG_STATUS_NOT_A_SUBSCRIBE_MODEL               0x08
#define ESP_BLE_MESH_CFG_STATUS_STORAGE_FAILURE                     0x09
#define ESP_BLE_MESH_CFG_STATUS_FEATURE_NOT_SUPPORTED               0x0A
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_UPDATE                       0x0B
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_REMOVE                       0x0C
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_BIND                         0x0D
#define ESP_BLE_MESH_CFG_STATUS_TEMP_UNABLE_TO_CHANGE_STATE         0x0E
#define ESP_BLE_MESH_CFG_STATUS_CANNOT_SET                          0x0F
#define ESP_BLE_MESH_CFG_STATUS_UNSPECIFIED_ERROR                   0x10
#define ESP_BLE_MESH_CFG_STATUS_INVALID_BINDING                     0x11

/**
 * esp_ble_mesh_opcode_health_client_get_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by esp_ble_mesh_health_client_get_state.
 * The following opcodes will only be used in the esp_ble_mesh_health_client_get_state function.
 */
typedef uint32_t esp_ble_mesh_opcode_health_client_get_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_GET                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x31) /*!< Health Fault Get */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_GET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x34) /*!< Health Period Get */
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_GET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x04) /*!< Health Attention Get */

/**
 * esp_ble_mesh_opcode_health_client_set_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by esp_ble_mesh_health_client_set_state.
 * The following opcodes will only be used in the esp_ble_mesh_health_client_set_state function.
 */
typedef uint32_t esp_ble_mesh_opcode_health_client_set_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR                    ESP_BLE_MESH_MODEL_OP_2(0x80, 0x2F) /*!< Health Fault Clear */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_CLEAR_UNACK              ESP_BLE_MESH_MODEL_OP_2(0x80, 0x30) /*!< Health Fault Clear Unacknowledged */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_TEST                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x32) /*!< Health Fault Test */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_TEST_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x33) /*!< Health Fault Test Unacknowledged */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_SET                     ESP_BLE_MESH_MODEL_OP_2(0x80, 0x35) /*!< Health Period Set */
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x80, 0x36) /*!< Health Period Set Unacknowledged */
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_SET                         ESP_BLE_MESH_MODEL_OP_2(0x80, 0x05) /*!< Health Attention Set */
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x80, 0x06) /*!< Health Attention Set Unacknowledged */

/**
 * esp_ble_mesh_health_model_status_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by the Health Model messages.
 * The following opcodes are used by the BLE Mesh Health Server Model internally to
 * respond to the Health Client Model's request messages.
 */
typedef uint32_t esp_ble_mesh_health_model_status_t;

#define ESP_BLE_MESH_MODEL_OP_HEALTH_CURRENT_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x04)
#define ESP_BLE_MESH_MODEL_OP_HEALTH_FAULT_STATUS                   ESP_BLE_MESH_MODEL_OP_1(0x05)
#define ESP_BLE_MESH_MODEL_OP_HEALTH_PERIOD_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x80, 0x37)
#define ESP_BLE_MESH_MODEL_OP_ATTENTION_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x80, 0x07)

/**
 * esp_ble_mesh_generic_message_opcode_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by functions esp_ble_mesh_generic_client_get_state
 * & esp_ble_mesh_generic_client_set_state.
 */
typedef uint32_t esp_ble_mesh_generic_message_opcode_t;

/*!< Generic OnOff Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x01)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x02)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x03)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONOFF_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x04)

/*!< Generic Level Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x05)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x06)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x07)
#define ESP_BLE_MESH_MODEL_OP_GEN_LEVEL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x08)
#define ESP_BLE_MESH_MODEL_OP_GEN_DELTA_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x09)
#define ESP_BLE_MESH_MODEL_OP_GEN_DELTA_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0A)
#define ESP_BLE_MESH_MODEL_OP_GEN_MOVE_SET                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0B)
#define ESP_BLE_MESH_MODEL_OP_GEN_MOVE_SET_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0C)

/*!< Generic Default Transition Time Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_GET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0D)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_SET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0E)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_SET_UNACK          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x0F)
#define ESP_BLE_MESH_MODEL_OP_GEN_DEF_TRANS_TIME_STATUS             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x10)

/*!< Generic Power OnOff Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x11)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x12)

/*!< Generic Power OnOff Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x13)
#define ESP_BLE_MESH_MODEL_OP_GEN_ONPOWERUP_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x14)

/*!< Generic Power Level Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x15)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x16)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x17)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LEVEL_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x18)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LAST_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x19)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_LAST_STATUS                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1A)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1B)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1C)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1D)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1E)

/*!< Generic Power Level Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x1F)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x20)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x21)
#define ESP_BLE_MESH_MODEL_OP_GEN_POWER_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x22)

/*!< Generic Battery Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_BATTERY_GET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x23)
#define ESP_BLE_MESH_MODEL_OP_GEN_BATTERY_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x24)

/*!< Generic Location Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x25)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x40)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x26)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x27)

/*!< Generic Location Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_SET                    ESP_BLE_MESH_MODEL_OP_1(0x41)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_GLOBAL_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x42)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x28)
#define ESP_BLE_MESH_MODEL_OP_GEN_LOC_LOCAL_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x29)

/*!< Generic Manufacturer Property Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTIES_GET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2A)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTIES_STATUS    ESP_BLE_MESH_MODEL_OP_1(0x43)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_GET         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2B)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET         ESP_BLE_MESH_MODEL_OP_1(0x44)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_SET_UNACK   ESP_BLE_MESH_MODEL_OP_1(0x45)
#define ESP_BLE_MESH_MODEL_OP_GEN_MANUFACTURER_PROPERTY_STATUS      ESP_BLE_MESH_MODEL_OP_1(0x46)

/*!< Generic Admin Property Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTIES_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2C)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTIES_STATUS           ESP_BLE_MESH_MODEL_OP_1(0x47)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_GET                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2D)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_SET                ESP_BLE_MESH_MODEL_OP_1(0x48)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_SET_UNACK          ESP_BLE_MESH_MODEL_OP_1(0x49)
#define ESP_BLE_MESH_MODEL_OP_GEN_ADMIN_PROPERTY_STATUS             ESP_BLE_MESH_MODEL_OP_1(0x4A)

/*!< Generic User Property Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTIES_GET               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2E)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTIES_STATUS            ESP_BLE_MESH_MODEL_OP_1(0x4B)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x2F)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_SET                 ESP_BLE_MESH_MODEL_OP_1(0x4C)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_SET_UNACK           ESP_BLE_MESH_MODEL_OP_1(0x4D)
#define ESP_BLE_MESH_MODEL_OP_GEN_USER_PROPERTY_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x4E)

/*!< Generic Client Property Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_GET             ESP_BLE_MESH_MODEL_OP_1(0x4F)
#define ESP_BLE_MESH_MODEL_OP_GEN_CLIENT_PROPERTIES_STATUS          ESP_BLE_MESH_MODEL_OP_1(0x50)

/**
 * esp_ble_mesh_sensor_message_opcode_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by functions esp_ble_mesh_sensor_client_get_state
 * & esp_ble_mesh_sensor_client_set_state.
 */
typedef uint32_t esp_ble_mesh_sensor_message_opcode_t;

/*!< Sensor Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x30)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_DESCRIPTOR_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x51)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_GET                            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x31)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_STATUS                         ESP_BLE_MESH_MODEL_OP_1(0x52)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x32)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_COLUMN_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x53)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x33)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SERIES_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x54)

/*!< Sensor Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x34)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_SET                    ESP_BLE_MESH_MODEL_OP_1(0x55)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x56)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_CADENCE_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x57)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x35)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTINGS_STATUS                ESP_BLE_MESH_MODEL_OP_1(0x58)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x36)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_SET                    ESP_BLE_MESH_MODEL_OP_1(0x59)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_SET_UNACK              ESP_BLE_MESH_MODEL_OP_1(0x5A)
#define ESP_BLE_MESH_MODEL_OP_SENSOR_SETTING_STATUS                 ESP_BLE_MESH_MODEL_OP_1(0x5B)

/**
 * esp_ble_mesh_time_scene_message_opcode_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by functions esp_ble_mesh_time_scene_client_get_state
 * & esp_ble_mesh_time_scene_client_set_state.
 */
typedef uint32_t esp_ble_mesh_time_scene_message_opcode_t;

/*!< Time Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_TIME_GET                              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x37)
#define ESP_BLE_MESH_MODEL_OP_TIME_SET                              ESP_BLE_MESH_MODEL_OP_1(0x5C)
#define ESP_BLE_MESH_MODEL_OP_TIME_STATUS                           ESP_BLE_MESH_MODEL_OP_1(0x5D)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x38)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x39)
#define ESP_BLE_MESH_MODEL_OP_TIME_ROLE_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3A)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3B)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3C)
#define ESP_BLE_MESH_MODEL_OP_TIME_ZONE_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3D)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3E)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x3F)
#define ESP_BLE_MESH_MODEL_OP_TAI_UTC_DELTA_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x40)

/*!< Scene Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SCENE_GET                             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x41)
#define ESP_BLE_MESH_MODEL_OP_SCENE_RECALL                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x42)
#define ESP_BLE_MESH_MODEL_OP_SCENE_RECALL_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x43)
#define ESP_BLE_MESH_MODEL_OP_SCENE_STATUS                          ESP_BLE_MESH_MODEL_OP_1(0x5E)
#define ESP_BLE_MESH_MODEL_OP_SCENE_REGISTER_GET                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x44)
#define ESP_BLE_MESH_MODEL_OP_SCENE_REGISTER_STATUS                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x45)

/*!< Scene Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SCENE_STORE                           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x46)
#define ESP_BLE_MESH_MODEL_OP_SCENE_STORE_UNACK                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x47)
#define ESP_BLE_MESH_MODEL_OP_SCENE_DELETE                          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9E)
#define ESP_BLE_MESH_MODEL_OP_SCENE_DELETE_UNACK                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9F)

/*!< Scheduler Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x48)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_STATUS                  ESP_BLE_MESH_MODEL_OP_1(0x5F)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x49)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4A)

/*!< Scheduler Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_SET                     ESP_BLE_MESH_MODEL_OP_1(0x60)
#define ESP_BLE_MESH_MODEL_OP_SCHEDULER_ACT_SET_UNACK               ESP_BLE_MESH_MODEL_OP_1(0x61)

/**
 * esp_ble_mesh_light_message_opcode_t belongs to esp_ble_mesh_opcode_t, this typedef is
 * only used to locate the opcodes used by functions esp_ble_mesh_light_client_get_state
 * & esp_ble_mesh_light_client_set_state.
 */
typedef uint32_t esp_ble_mesh_light_message_opcode_t;

/*!< Light Lightness Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_GET            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x4F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_SET            ESP_BLE_MESH_MODEL_OP_2(0x82, 0x50)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_SET_UNACK      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x51)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LINEAR_STATUS         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x52)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LAST_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x53)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_LAST_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x54)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_GET           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x55)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_STATUS        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x56)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_GET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x57)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_STATUS          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x58)

/*!< Light Lightness Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_SET           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x59)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_DEFAULT_SET_UNACK     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_SET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LIGHTNESS_RANGE_SET_UNACK       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5C)

/*!< Light CTL Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x5F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x60)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_GET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x61)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_GET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x62)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_STATUS    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x63)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_SET             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x64)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_SET_UNACK       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x65)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_STATUS          ESP_BLE_MESH_MODEL_OP_2(0x82, 0x66)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x67)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x68)

/*!< Light CTL Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x69)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_SET       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_CTL_TEMPERATURE_RANGE_SET_UNACK ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6C)

/*!< Light HSL Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x6F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x70)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_HUE_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x71)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x72)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_SET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x73)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_SET_UNACK        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x74)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SATURATION_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x75)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x76)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x77)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x78)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_TARGET_GET                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x79)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_TARGET_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7E)

/*!< Light HSL Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x7F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x80)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x81)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_HSL_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x82)

/*!< Light xyL Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_GET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x83)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_SET                         ESP_BLE_MESH_MODEL_OP_2(0x82, 0x84)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_SET_UNACK                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x85)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_STATUS                      ESP_BLE_MESH_MODEL_OP_2(0x82, 0x86)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_TARGET_GET                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x87)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_TARGET_STATUS               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x88)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x89)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_STATUS              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_GET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_STATUS                ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8C)

/*!< Light xyL Setup Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_SET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_DEFAULT_SET_UNACK           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8E)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_SET                   ESP_BLE_MESH_MODEL_OP_2(0x82, 0x8F)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_XYL_RANGE_SET_UNACK             ESP_BLE_MESH_MODEL_OP_2(0x82, 0x90)

/*!< Light Control Message Opcode */
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_GET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x91)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_SET                     ESP_BLE_MESH_MODEL_OP_2(0x82, 0x92)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_SET_UNACK               ESP_BLE_MESH_MODEL_OP_2(0x82, 0x93)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_MODE_STATUS                  ESP_BLE_MESH_MODEL_OP_2(0x82, 0x94)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_GET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x95)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_SET                       ESP_BLE_MESH_MODEL_OP_2(0x82, 0x96)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_SET_UNACK                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x97)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_OM_STATUS                    ESP_BLE_MESH_MODEL_OP_2(0x82, 0x98)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_GET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x99)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_SET              ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9A)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_SET_UNACK        ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9B)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_LIGHT_ONOFF_STATUS           ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9C)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_GET                 ESP_BLE_MESH_MODEL_OP_2(0x82, 0x9D)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_SET                 ESP_BLE_MESH_MODEL_OP_1(0x62)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_SET_UNACK           ESP_BLE_MESH_MODEL_OP_1(0x63)
#define ESP_BLE_MESH_MODEL_OP_LIGHT_LC_PROPERTY_STATUS              ESP_BLE_MESH_MODEL_OP_1(0x64)

typedef uint32_t esp_ble_mesh_opcode_t;
/*!< End of defines of esp_ble_mesh_opcode_t */

/**
 * This typedef is only used to indicate the status code contained in some of the
 * server models (e.g. Generic Server Model) status message.
 */
typedef uint8_t esp_ble_mesh_model_status_t;

#define ESP_BLE_MESH_MODEL_STATUS_SUCCESS                           0x00
#define ESP_BLE_MESH_MODEL_STATUS_CANNOT_SET_RANGE_MIN              0x01
#define ESP_BLE_MESH_MODEL_STATUS_CANNOT_SET_RANGE_MAX              0x02


#ifndef BD_ADDR_LEN
#define BD_ADDR_LEN     6
typedef uint8_t BD_ADDR[BD_ADDR_LEN];
#endif

typedef uint8_t esp_ble_mesh_bd_addr_t[BD_ADDR_LEN];
/// BLE device address type
typedef uint8_t esp_ble_mesh_addr_type_t;

/** Information of the provisioned node */
typedef struct {
    /* Device information */
    esp_ble_mesh_bd_addr_t   addr;      /*!< Node device address */
    esp_ble_mesh_addr_type_t addr_type; /*!< Node device address type */
    uint8_t  dev_uuid[16];  /*!< Device UUID */
    uint16_t oob_info;      /*!< Node OOB information */

    /* Provisioning information */
    uint16_t unicast_addr;  /*!< Node unicast address */
    uint8_t  element_num;   /*!< Node element number */
    uint16_t net_idx;       /*!< Node NetKey Index */
    uint8_t  flags;         /*!< Node key refresh flag and iv update flag */
    uint32_t iv_index;      /*!< Node IV Index */
    uint8_t  dev_key[16];   /*!< Node device key */

    /* Additional information */
    char name[ESP_BLE_MESH_NODE_NAME_MAX_LEN + 1]; /*!< Node name */
    uint16_t comp_length;  /*!< Length of Composition Data */
    uint8_t *comp_data;    /*!< Value of Composition Data */
} __attribute__((packed)) esp_ble_mesh_node_t;

/** @def    ESP_BLE_MESH_TRANSMIT
 *
 *  @brief  Encode transmission count & interval steps.
 *
 *  @note   For example, ESP_BLE_MESH_TRANSMIT(2, 20) means that the message
 *          will be sent about 90ms(count is 3, step is 1, interval is 30 ms
 *          which includes 10ms of advertising interval random delay).
 *
 *  @param  count   Number of retransmissions (first transmission is excluded).
 *  @param  int_ms  Interval steps in milliseconds. Must be greater than 0
 *                  and a multiple of 10.
 *
 *  @return BLE Mesh transmit value that can be used e.g. for the default
 *          values of the Configuration Model data.
 */
#define ESP_BLE_MESH_TRANSMIT(count, int_ms) ((count) | (((int_ms / 10) - 1) << 3))

/** @def ESP_BLE_MESH_GET_TRANSMIT_COUNT
 *
 *  @brief Decode transmit count from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission count (actual transmissions equal to N + 1).
 */
#define ESP_BLE_MESH_GET_TRANSMIT_COUNT(transmit) (((transmit) & (uint8_t)BIT_MASK(3)))

/** @def ESP_BLE_MESH_GET_TRANSMIT_INTERVAL
 *
 *  @brief Decode transmit interval from a transmit value.
 *
 *  @param transmit Encoded transmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define ESP_BLE_MESH_GET_TRANSMIT_INTERVAL(transmit) ((((transmit) >> 3) + 1) * 10)

/** @def ESP_BLE_MESH_PUBLISH_TRANSMIT
 *
 *  @brief Encode Publish Retransmit count & interval steps.
 *
 *  @param count   Number of retransmissions (first transmission is excluded).
 *  @param int_ms  Interval steps in milliseconds. Must be greater than 0
 *                 and a multiple of 50.
 *
 *  @return BLE Mesh transmit value that can be used e.g. for the default
 *          values of the Configuration Model data.
 */
#define ESP_BLE_MESH_PUBLISH_TRANSMIT(count, int_ms) ESP_BLE_MESH_TRANSMIT(count, (int_ms) / 5)

/** @def ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_COUNT
 *
 *  @brief Decode Publish Retransmit count from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Retransmission count (actual transmissions equal to N + 1).
 */
#define ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_COUNT(transmit) ESP_BLE_MESH_GET_TRANSMIT_COUNT(transmit)

/** @def ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_INTERVAL
 *
 *  @brief Decode Publish Retransmit interval from a given value.
 *
 *  @param transmit Encoded Publish Retransmit count & interval value.
 *
 *  @return Transmission interval in milliseconds.
 */
#define ESP_BLE_MESH_GET_PUBLISH_TRANSMIT_INTERVAL(transmit) ((((transmit) >> 3) + 1) * 50)


#ifdef __cplusplus
}
#endif

#endif /* _ESP_BLE_MESH_DEFS_H_ */
