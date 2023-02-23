#ifndef MY_CRC_H
#define MY_CRC_H

#include <stddef.h>
#include <stdint.h>
/**
 * Name   : "CRC-16/CITT"
   Width  : 16
   Poly   : 1021
   Init   : FFFF
   RefIn  : False
   RefOut : False
   XorOut : 0000
 * 
 **/

/**
 * @brief Runs a CRC-16-CCITT checksum algorithm. It will return and generate 2 bytes of checksum if you are sender.
 * If you are receiver, run the function with the length_of_interest accounting for the last 2 bytes of crc. It should
 * return 0 to indicate no data loss for 99.9984% of the time
 * 
 * @param data buffer with a size of the message contents + 2 bytes for CRC portion. This buffer's data must be in little endian format regardless of checking or receiving
 * @param length_of_interest number of bytes of interest in message content(exclude CRC part) if generating CRC. If checking CRC, must account for the number of bytes for CRC in length
 * @return uint16_t FOR SENDER: returns crc checksum value. FOR RECEIVER: returns 0 if no data loss
 */
uint16_t CRCCCITT(uint8_t *data, size_t length_of_interest);
#endif