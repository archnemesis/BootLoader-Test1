/*
 * @file	iap.c
 * @date	May 20, 2018
 * @author	robin
 * @brief   Description of file here...
 */

#include "iap.h"
#include "usart.h"
#include "firmware_metadata.h"
#include "diag/Trace.h"

static FirmwareMetadata_t *fw_meta;
static uint8_t serialBuffer[2048];
static uint8_t packetCount = 0;
static uint32_t bytesExpected = 0;
static uint32_t bytesReceived = 0;

void abortTransfer()
{
	bytesExpected = 0;
	bytesReceived = 0;
	packetCount = 0;
	BSP_USART_PutChar(&huart1, IAP_NAK);
}

void IAP_Init(void)
{
	IAP_DeviceInfo_t pkt;
	IAP_FirmwareHeader_t *hdr;
	IAP_FirmwarePacket_t *chk;
	HAL_StatusTypeDef result;
	uint16_t bytes;

	while (1)
	{
		if (HAL_UART_Receive(&huart1, &serialBuffer[0], 1, HAL_MAX_DELAY)
				== HAL_OK)
		{
			switch (serialBuffer[0])
			{
			case IAP_QRY:
				pkt.major = 0;
				pkt.minor = 0;
				pkt.rev = 0;

				if (((*(volatile uint32_t*) APPLICATION_ADDRESS) & 0x2FF00000)
						== 0x20000000)
				{
					fw_meta = (FirmwareMetadata_t *) (APPLICATION_ADDRESS
							+ APPLICATION_FW_META_OFFSET);
					pkt.major = fw_meta->major;
					pkt.minor = fw_meta->minor;
					pkt.rev = fw_meta.rev;
				}

				BSP_USART_PutChar(&huart1, IAP_INF);
				HAL_UART_Transmit(&huart1, (uint8_t*) &pkt,
						sizeof(IAP_DeviceInfo_t),
						HAL_MAX_DELAY);

				break;
			case IAP_SOH:
				/* First packet should contain the header information */
				if (packetCount == 0)
				{
					result = HAL_UART_Receive(&huart1, &serialBuffer[0],
							sizeof(IAP_FirmwareHeader_t), IAP_SOP_TIMEOUT);

					if (result == HAL_OK)
					{
						hdr = (IAP_FirmwareHeader_t *) &serialBuffer[0];
						bytesExpected = hdr->size;
						bytesReceived = 0;
						packetCount++;

						/* TODO: Erase flash and prepare for incoming data... */

						BSP_USART_PutChar(&huart1, IAP_ACK);
					}
					else if (result == HAL_TIMEOUT || result == HAL_ERROR)
					{
						abortTransfer();
					}
				}
				else
				{
					if ((bytesExpected - bytesReceived) >= IAP_MAX_PACKET_SIZE) {
						bytes = IAP_MAX_PACKET_SIZE;
					}
					else {
						bytes = bytesExpected - bytesReceived;
					}

					result = HAL_UART_Receive(&huart1, &serialBuffer[0],
							bytes + 2, IAP_TRANSFER_TIMEOUT);

					if (result == HAL_OK)
					{
						chk = (IAP_FirmwarePacket_t *)&serialBuffer[0];

						if (chk->sequence != packetCount) {
							/* TODO: Clean up flash operation and abort... */

							abortTransfer();
							break;
						}

						/* TODO: Copy received data into flash memory... */

						bytesReceived += bytes;
						packetCount++;
						BSP_USART_PutChar(&huart1, IAP_ACK);
					}
					else if (result == HAL_TIMEOUT || result == HAL_ERROR)
					{
						/* TODO: Clean up flash operation and abort... */

						abortTransfer();
					}
				}
			}
		}
	}

	while (1)
	{
		// waiting temporarily...
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

}
