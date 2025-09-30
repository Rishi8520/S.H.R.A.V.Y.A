/**
 * @file r_ether_api.h
 * @brief SHRAVYA Ethernet API Header for EK-RA8D1
 * @version 2.0
 * @date 2025-09-19
 *
 * Custom Ethernet API for TRON Programming Contest 2025
 * Compatible with R7FA8D1BH integrated Ethernet PHY
 * Supports TCP/UDP socket operations for N8N communication
 */

#ifndef R_ETHER_API_H
#define R_ETHER_API_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include "hal_data.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/***********************************************************************************************************************
 * FSP Common Error Codes (if not already defined)
 **********************************************************************************************************************/
#ifndef FSP_SUCCESS
#define FSP_SUCCESS                     (0)
#endif

#ifndef FSP_ERR_ASSERTION
#define FSP_ERR_ASSERTION              (-1)
#define FSP_ERR_INVALID_POINTER        (-6)
#define FSP_ERR_INVALID_ARGUMENT       (-7)
#define FSP_ERR_NOT_OPEN               (-8)
#define FSP_ERR_IN_USE                 (-11)
#define FSP_ERR_OUT_OF_MEMORY          (-12)
#define FSP_ERR_INTERNAL               (-20)
#define FSP_ERR_TIMEOUT                (-21)
#define FSP_ERR_ABORTED                (-22)
#endif

/***********************************************************************************************************************
 * Ethernet Configuration Constants
 **********************************************************************************************************************/
#define ETHER_PHY_LINK_SPEED_10H       (0)    /**< 10BASE-T half duplex */
#define ETHER_PHY_LINK_SPEED_10F       (1)    /**< 10BASE-T full duplex */
#define ETHER_PHY_LINK_SPEED_100H      (2)    /**< 100BASE-TX half duplex */
#define ETHER_PHY_LINK_SPEED_100F      (3)    /**< 100BASE-TX full duplex */

#define ETHER_ZEROCOPY_DISABLE         (0)    /**< Zero copy disabled */
#define ETHER_ZEROCOPY_ENABLE          (1)    /**< Zero copy enabled */

#define ETHER_PHY_ADDRESS_DEFAULT      (0)    /**< Default PHY address */

/* Buffer sizes */
#define ETHER_BUFFER_SIZE_MIN          (60U)  /**< Minimum Ethernet frame size */
#define ETHER_BUFFER_SIZE_MAX          (1514U) /**< Maximum Ethernet frame size */
#define ETHER_HEADER_SIZE              (14U)  /**< Ethernet header size */

/* ✅ SHRAVYA-Specific Network Configuration */
#define SHRAVYA_MAC_ADDR_SIZE          (6U)
#define SHRAVYA_IP_ADDR_SIZE           (4U)
#define SHRAVYA_MAX_SOCKETS            (8U)
#define SHRAVYA_SOCKET_TIMEOUT_DEFAULT (5000U) /* 5 seconds */

/***********************************************************************************************************************
 * Socket Type Definitions
 **********************************************************************************************************************/
typedef enum e_ether_socket_type
{
    ETHER_SOCKET_TYPE_TCP = 0,      /**< TCP socket */
    ETHER_SOCKET_TYPE_UDP = 1,      /**< UDP socket */
} ether_socket_type_t;

typedef enum e_ether_socket_state
{
    ETHER_SOCKET_STATE_CLOSED = 0,      /**< Socket is closed */
    ETHER_SOCKET_STATE_LISTENING = 1,   /**< Socket is listening */
    ETHER_SOCKET_STATE_CONNECTED = 2,   /**< Socket is connected */
    ETHER_SOCKET_STATE_CLOSING = 3,     /**< Socket is closing */
} ether_socket_state_t;

/***********************************************************************************************************************
 * Network Address Structures
 **********************************************************************************************************************/
typedef struct st_ether_socket_address
{
    uint8_t  ip_address[SHRAVYA_IP_ADDR_SIZE]; /**< IP address (4 bytes) */
    uint16_t port;                             /**< Port number */
} ether_socket_address_t;

typedef struct st_ether_network_config
{
    uint8_t mac_address[SHRAVYA_MAC_ADDR_SIZE]; /**< MAC address */
    uint8_t ip_address[SHRAVYA_IP_ADDR_SIZE];   /**< IP address */
    uint8_t subnet_mask[SHRAVYA_IP_ADDR_SIZE];  /**< Subnet mask */
    uint8_t gateway[SHRAVYA_IP_ADDR_SIZE];      /**< Gateway address */
    uint8_t dns_server[SHRAVYA_IP_ADDR_SIZE];   /**< DNS server address */
    bool    dhcp_enable;                        /**< DHCP enable flag */
} ether_network_config_t;

/***********************************************************************************************************************
 * PHY and Link Status
 **********************************************************************************************************************/
typedef struct st_ether_link_status
{
    bool    link_up;           /**< Link status (up/down) */
    uint8_t link_speed;        /**< Link speed */
    bool    full_duplex;       /**< Duplex mode */
    bool    auto_negotiation;  /**< Auto-negotiation status */
} ether_link_status_t;

/***********************************************************************************************************************
 * Statistics Structure
 **********************************************************************************************************************/
typedef struct st_ether_statistics
{
    uint32_t tx_packets;       /**< Transmitted packets */
    uint32_t rx_packets;       /**< Received packets */
    uint32_t tx_bytes;         /**< Transmitted bytes */
    uint32_t rx_bytes;         /**< Received bytes */
    uint32_t tx_errors;        /**< Transmission errors */
    uint32_t rx_errors;        /**< Reception errors */
    uint32_t collisions;       /**< Collision count */
    uint32_t dropped_packets;  /**< Dropped packets */
} ether_statistics_t;

/***********************************************************************************************************************
 * Control Block Structure (matches FSP pattern)
 **********************************************************************************************************************/
typedef struct st_ether_instance_ctrl
{
    uint32_t                  open;              /**< Open flag */
    ether_network_config_t    network_config;    /**< Network configuration */
    ether_link_status_t       link_status;       /**< Link status */
    ether_statistics_t        statistics;        /**< Statistics */
    bool                      initialized;       /**< Initialization flag */
    void const              * p_cfg;             /**< Configuration pointer */
    void                    * p_context;         /**< Context pointer */

    /* ✅ SHRAVYA Socket Management */
    struct {
        ether_socket_type_t   type;              /**< Socket type */
        ether_socket_state_t  state;             /**< Socket state */
        ether_socket_address_t local_addr;       /**< Local address */
        ether_socket_address_t remote_addr;      /**< Remote address */
        bool                  in_use;            /**< Socket in use flag */
    } sockets[SHRAVYA_MAX_SOCKETS];

} ether_instance_ctrl_t;

/***********************************************************************************************************************
 * Configuration Structure
 **********************************************************************************************************************/
typedef struct st_ether_cfg
{
    uint8_t                   phy_address;       /**< PHY address */
    uint8_t                   link_speed;        /**< Link speed setting */
    bool                      auto_negotiation;  /**< Auto-negotiation enable */
    bool                      zerocopy;          /**< Zero copy enable */
    uint32_t                  buffer_count_tx;   /**< TX buffer count */
    uint32_t                  buffer_count_rx;   /**< RX buffer count */
    void                    * p_buffers_tx;      /**< TX buffers pointer */
    void                    * p_buffers_rx;      /**< RX buffers pointer */
    void                    * p_context;         /**< User context */
    void const              * p_extend;          /**< Extension pointer */
} ether_cfg_t;

/***********************************************************************************************************************
 * ✅ SHRAVYA Global Instance Declarations (matches your FSP configuration)
 **********************************************************************************************************************/
extern ether_instance_ctrl_t g_ether0_ctrl;
extern const ether_cfg_t     g_ether0_cfg;

/***********************************************************************************************************************
 * Core Ethernet API Functions
 **********************************************************************************************************************/

/**
 * @brief Initialize and open Ethernet interface
 * @param[in] p_ctrl    Pointer to control structure
 * @param[in] p_cfg     Pointer to configuration structure
 * @retval FSP_SUCCESS                  Initialization successful
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_ALREADY_OPEN         Interface already open
 */
fsp_err_t R_ETHER_Open(ether_instance_ctrl_t * const p_ctrl, ether_cfg_t const * const p_cfg);

/**
 * @brief Close Ethernet interface
 * @param[in] p_ctrl    Pointer to control structure
 * @retval FSP_SUCCESS                  Close successful
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_Close(ether_instance_ctrl_t * const p_ctrl);

/**
 * @brief Set IP address configuration
 * @param[in] p_ctrl        Pointer to control structure
 * @param[in] ip_address    IP address (4 bytes)
 * @param[in] subnet_mask   Subnet mask (4 bytes)
 * @param[in] gateway       Gateway address (4 bytes)
 * @retval FSP_SUCCESS                  Configuration successful
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_SetIpAddress(ether_instance_ctrl_t * const p_ctrl,
                               uint8_t const * const ip_address,
                               uint8_t const * const subnet_mask,
                               uint8_t const * const gateway);

/**
 * @brief Get link status
 * @param[in]  p_ctrl       Pointer to control structure
 * @param[out] p_status     Pointer to status structure
 * @retval FSP_SUCCESS                  Status retrieved successfully
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_LinkProcess(ether_instance_ctrl_t * const p_ctrl);

/***********************************************************************************************************************
 * ✅ SHRAVYA Socket API Functions (Custom Implementation)
 **********************************************************************************************************************/

/**
 * @brief Create a new socket
 * @param[in] p_ctrl    Pointer to control structure
 * @param[in] type      Socket type (TCP/UDP)
 * @retval >=0                          Socket descriptor
 * @retval -1                           Error creating socket
 */
int R_ETHER_SocketCreate(ether_instance_ctrl_t * const p_ctrl, ether_socket_type_t type);

/**
 * @brief Connect to remote server (TCP only)
 * @param[in] p_ctrl        Pointer to control structure
 * @param[in] socket_id     Socket descriptor
 * @param[in] p_address     Remote server address
 * @param[in] timeout_ms    Connection timeout in milliseconds
 * @retval FSP_SUCCESS                  Connection successful
 * @retval FSP_ERR_INVALID_ARGUMENT     Invalid socket or address
 * @retval FSP_ERR_TIMEOUT              Connection timeout
 * @retval FSP_ERR_INTERNAL             Connection failed
 */
fsp_err_t R_ETHER_SocketConnect(ether_instance_ctrl_t * const p_ctrl,
                               int socket_id,
                               ether_socket_address_t const * const p_address,
                               uint32_t timeout_ms);

/**
 * @brief Send data through socket
 * @param[in] p_ctrl        Pointer to control structure
 * @param[in] socket_id     Socket descriptor
 * @param[in] p_data        Data to send
 * @param[in] length        Data length
 * @param[in] flags         Send flags (reserved, set to 0)
 * @retval FSP_SUCCESS                  Data sent successfully
 * @retval FSP_ERR_INVALID_ARGUMENT     Invalid parameters
 * @retval FSP_ERR_NOT_OPEN             Socket not connected
 * @retval FSP_ERR_INTERNAL             Send error
 */
fsp_err_t R_ETHER_SocketSend(ether_instance_ctrl_t * const p_ctrl,
                            int socket_id,
                            uint8_t const * const p_data,
                            uint32_t length,
                            uint32_t flags);

/**
 * @brief Receive data from socket
 * @param[in]  p_ctrl       Pointer to control structure
 * @param[in]  socket_id    Socket descriptor
 * @param[out] p_buffer     Buffer to receive data
 * @param[in]  buffer_size  Buffer size
 * @param[in]  timeout_ms   Receive timeout in milliseconds
 * @retval >=0                          Number of bytes received
 * @retval -1                           Error receiving data
 */
int R_ETHER_SocketReceive(ether_instance_ctrl_t * const p_ctrl,
                         int socket_id,
                         uint8_t * const p_buffer,
                         uint32_t buffer_size,
                         uint32_t timeout_ms);

/**
 * @brief Close socket
 * @param[in] p_ctrl        Pointer to control structure
 * @param[in] socket_id     Socket descriptor
 * @retval FSP_SUCCESS                  Socket closed successfully
 * @retval FSP_ERR_INVALID_ARGUMENT     Invalid socket ID
 */
fsp_err_t R_ETHER_SocketClose(ether_instance_ctrl_t * const p_ctrl, int socket_id);

/***********************************************************************************************************************
 * Utility and Status Functions
 **********************************************************************************************************************/

/**
 * @brief Get network statistics
 * @param[in]  p_ctrl       Pointer to control structure
 * @param[out] p_stats      Pointer to statistics structure
 * @retval FSP_SUCCESS                  Statistics retrieved successfully
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_GetStatistics(ether_instance_ctrl_t * const p_ctrl,
                               ether_statistics_t * const p_stats);

/**
 * @brief Reset network statistics
 * @param[in] p_ctrl        Pointer to control structure
 * @retval FSP_SUCCESS                  Statistics reset successfully
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_ResetStatistics(ether_instance_ctrl_t * const p_ctrl);

/**
 * @brief Get current network configuration
 * @param[in]  p_ctrl       Pointer to control structure
 * @param[out] p_config     Pointer to configuration structure
 * @retval FSP_SUCCESS                  Configuration retrieved successfully
 * @retval FSP_ERR_INVALID_POINTER      Null pointer passed
 * @retval FSP_ERR_NOT_OPEN             Interface not open
 */
fsp_err_t R_ETHER_GetNetworkConfig(ether_instance_ctrl_t * const p_ctrl,
                                  ether_network_config_t * const p_config);

/***********************************************************************************************************************
 * ✅ SHRAVYA Helper Macros for Easy Integration
 **********************************************************************************************************************/

/** Convert IP address from separate bytes to array */
#define SHRAVYA_IP_ADDR(a,b,c,d)  {(a), (b), (c), (d)}

/** Convert MAC address from separate bytes to array */
#define SHRAVYA_MAC_ADDR(a,b,c,d,e,f)  {(a), (b), (c), (d), (e), (f)}

/** Check if IP addresses are equal */
#define SHRAVYA_IP_EQUAL(ip1, ip2) \
    (memcmp((ip1), (ip2), SHRAVYA_IP_ADDR_SIZE) == 0)

/** Print IP address (for debugging) */
#define SHRAVYA_IP_PRINTF(ip) \
    printf("%d.%d.%d.%d", (ip)[0], (ip)[1], (ip)[2], (ip)[3])

/***********************************************************************************************************************
 * Version Information
 **********************************************************************************************************************/
#define ETHER_API_VERSION_MAJOR    (2)
#define ETHER_API_VERSION_MINOR    (0)
#define ETHER_API_VERSION_PATCH    (0)

#define ETHER_API_VERSION_BUILD    (20250919)

/***********************************************************************************************************************
 * Common Return Values for Documentation
 **********************************************************************************************************************/
/** @} (end addtogroup ETHER_API) */

#endif /* R_ETHER_API_H */

/***********************************************************************************************************************
 * END OF FILE
 **********************************************************************************************************************/
