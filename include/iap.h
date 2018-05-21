/*
 * @file	iap.h
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#ifndef INCLUDE_IAP_H_
#define INCLUDE_IAP_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define IAP_MAX_PACKET_SIZE	1024

#define IAP_ACK 0xAB
#define IAP_NAK 0xAC
#define IAP_QRY 0xAD
#define IAP_INF 0xAE
#define IAP_SOH 0xAF

#define IAP_NAK_TIMEOUT 1000
#define IAP_SOP_TIMEOUT 1000
#define IAP_TRANSFER_TIMEOUT 1000

typedef struct IAP_DeviceInfo {
	uint8_t major;
	uint8_t minor;
	uint8_t rev;
	uint8_t reserved0;
} __attribute__((packed)) IAP_DeviceInfo_t;

typedef struct IAP_FirmwarePacket {
	uint32_t sequence;
	uint32_t checksum;
	uint32_t data[IAP_MAX_PACKET_SIZE / 4];
} __attribute__((packed)) IAP_FirmwarePacket_t;

typedef struct IAP_FirmwareHeader {
	uint32_t size;
	uint16_t chunks;
} __attribute__((packed)) IAP_FirmwareHeader_t;

void IAP_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDE_IAP_H_ */
