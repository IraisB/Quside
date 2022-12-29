/*
 ============================================================================
 Name        : quside_qrng_user.c
 Author      : Alvaro Velasco Garcia, Heriberto J. Diaz
 Created on  : 14 April. 2022
 Version     : 0.1
 Copyright   : Copyright (C) 2022 QUSIDE TECHNOLOGIES - All Rights Reserved.
               Unauthorized copying of this file, via any medium is
               strictly prohibited.
 Description : This header defines the functions to establish a connection
               with a QRNG and manage it.
 ============================================================================
 */

#ifndef QUSIDE_QRNG_USER_H
#define QUSIDE_QRNG_USER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <time.h>
#include "cJSON.h"

#define DEBUG				0
#define INVALID_SOCKET		-1

/* TODO: Unify this declarations with the server declarations
 *       to avoid the disconnection between the implementations.
 */
#define ACK						"ACK"
#define ASK_BABYLON				"ASKB"
#define CAPTURE_FINISH			"CPF"
#define CAPTURE_RECEIVED		"CPR"
#define CAPTURE 				"CPT"
#define CAPTURE_RAW				"CRA"
#define DISCONNECT 				"DIS"
#define DEVICE_ERROR			"DRR"
#define ECHO 					"ECH"
#define END 					"END"
#define ERROR					"ERR"
#define FIND_BOARD				"FBO"
#define FIND_DEVICE				"FDV"
#define GET_BOARDS_ID			"GBI"
#define INIT_DEVICE				"IDV"
#define RESET					"RST"
#define SERVER_VERSION			"SRV"
#define SYSTEM_INFO				"SYS"
#define UNKNOWN					"UNK"

/******************************************************************************
** connectToServer
**
** Tries to init the communication between the QRNG server and the host.
**
** @param serverIP [char *] IP of the server.
**
** @return [int] If it success returns 0, otherwise -1.
******************************************************************************/
int connectToServer(char *serverIP);

/******************************************************************************
** disconnectServer
**
** Tries to disconnect the communication between the QRNG server and the host.
**
** @return void.
******************************************************************************/
void disconnectServer(void);

/******************************************************************************
** reset
**
** Reset system.
**
** @return void
******************************************************************************/
void reset(void);

/******************************************************************************
** get_random
**
** This function captures N uint32 bytes of extracted random numbers.
**
** @param mem_slot [uint32_t *] pointer to region where save the numbers.
** @param Nuint32 [const size_t] count of random numbers in bytes.
** @param devInd [uint16_t] Index of the device to use from the list.
**
** @return [int] If it success returns 0, otherwise -1.
******************************************************************************/
int get_random(uint32_t* mem_slot, const size_t Nuint32, const uint16_t devInd);

/******************************************************************************
** get_raw
**
** This function capture Nuint32 bytes of raw random numbers.
**
** @param mem_slot [uint32_t *] pointer to region where save the numbers.
** @param Nuint32 [const size_t] count of random numbers in bytes.
** @param devInd [uint16_t] Index of the device to use from the list.
**
** @return [int] If it success returns 0, otherwise -1.
******************************************************************************/
int get_raw(uint32_t* mem_slot, const size_t Nuint32, const uint16_t devInd);

/******************************************************************************
** find_boards
**
** Search Babylon devices connected through PCI in the system and initialize
** the lists with the descriptors.
**
** @return [uint16_t] number of Babylons connected.
******************************************************************************/
uint16_t find_boards(void);

/******************************************************************************
** get_boards
**
** Returns a list of the devices IDs connected to the system.
**
** @param devIDs  [uint16_t**] List that will contain the devices IDs.
** @param numDevs [uint16_t*] Number of elements that the list will contain.
**
** @return void.
**
******************************************************************************/
void get_boards(uint16_t** devIDs, uint16_t* numDevs);

/******************************************************************************
** find_device
**
** Returns the index of a device contained in the devices list.
**
** @param devID [uint16_t] Device id to search in the list.
**
** @return [int] The index of the devID in the devices list. If the provided devID
**               does not exist, this function will return a -1.
******************************************************************************/
int find_device(const uint16_t devID);

/******************************************************************************
** formJSON
**
** Parse a JSON message to char array.
**
** @param ID [const char *] TODO: BERTO!
** @param cmd [const char *] TODO: BERTO!
** @param addr [const char *] TODO: BERTO!
** @param err [const char *] TODO: BERTO!
** @param data [float *] TODO: BERTO!
** @param sizedata [const uint32_t]
** @param ext [const char *] TODO: BERTO!
**
** @return [char*] Returns the message in char array format.s
******************************************************************************/
char* formJSON(const char *ID, const char *cmd, const uint32_t addr,
		const uint32_t dev, const uint32_t err, const float* data,
		const uint32_t sizeData, const uint32_t ext);

#ifdef __cplusplus
}
#endif

#endif /* QUSIDE_QRNG_USER_H */
