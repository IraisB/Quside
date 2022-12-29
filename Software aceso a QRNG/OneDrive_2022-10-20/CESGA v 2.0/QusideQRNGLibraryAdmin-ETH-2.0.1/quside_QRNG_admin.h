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

#ifndef QUSIDE_QRNG_ADMIN_H
#define QUSIDE_QRNG_ADMIN_H

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

/* Enum that contains all the monitors in the system. */
typedef enum {
    LASER_STATUS,
    LASER_TEMP,
    OPTICAL_PW,
    BIAS_MON,
    TEMP,
    VCC,
    VCOMP,
    QFACTOR,
    SYSTEM_CALIBRATED
} alarmType;

/* Possible values of the alarms. */
typedef enum {
    OK,
    LOW_VALUE = -1,
    HIGH_VALUE = -2,
    OFF = -3,
    OUT_OF_SECURE_RANGE = -4
} monitorValue;

/* This enumerate defines the codes of the possible status of the QRNG calibration. */
typedef enum {
	 DEFAULT,
	 CALIBRATING,
	 CALIB_SUCCED,
	 CALIB_FAIL,
	 I2C_ERROR
} calibrationStatus;

#define DEBUG				0
#define INVALID_SOCKET		-1

/* TODO: Unify this declarations with the server declarations
 *       to avoid the disconnection between the implementations.
 */
#define ACK						"ACK"
#define ASK_BABYLON				"ASKB"
#define BIAS_MONITOR_READ		"BMR"
#define CALIBRATION 			"CLB"
#define CALIBRATION_FINISH		"CLF"
#define CALIBRATION_STATUS		"CLS"
#define CALIBRATION_VTC			"CLV"
#define CAPTURE_FINISH			"CPF"
#define CAPTURE_RECEIVED		"CPR"
#define CAPTURE 				"CPT"
#define CAPTURE_RAW				"CRA"
#define CHECK_THRESHOLDS		"CTH"
#define DISCONNECT 				"DIS"
#define DEVICE_ERROR			"DRR"
#define DELTA_T_READ			"DTR"
#define ECHO 					"ECH"
#define END 					"END"
#define ERROR					"ERR"
#define FIND_BOARD				"FBO"
#define FIND_DEVICE				"FDV"
#define GET_BOARDS_ID			"GBI"
#define INIT_DEVICE				"IDV"
#define LASER_STATUS_READ		"LAS"
#define LED						"LED"
#define LASER_TEMPERATURES_READ	"LTR"
#define MONITOR_ALARM			"MAL"
#define MINENTROPY				"MET"
#define MONITOR_ENABLE_WRITE	"MEW"
#define MONITOR_OUT_LIMITS		"MOL"
#define MONITOR_VALUE_READ		"MVR"
#define NEW_CONFIG_NETWORK		"NCN"
#define NUM_LASERS				"NML"
#define OPTICAL_POWER_READ		"OPR"
#define QFACTOR					"QFT"
#define RESET					"RST"
#define SERVER_VERSION			"SRV"
#define SYSTEM_INFO				"SYS"
#define TIMEOUT					"TOU"
#define TEMPERATURE_READ		"TPR"
#define UNKNOWN					"UNK"
#define UPDATE_THRESHOLDS		"UTH"
#define VCC_READ				"VCR"
#define VCOMP_READ				"VPR"

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
** Tries to init the communication between the QRNG server and the host.
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
** setTimeout
**
** Set timeout client.
**
** @return void
******************************************************************************/
void setTimeout(int seconds);

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
** monitor_read_temperature
**
** Reads temperature in ºC.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param temp [float*] Variable that will contains the temperature values.
**
** @return [int] If it success returns 0, otherwise -1.
**
******************************************************************************/
int monitor_read_temperature(const uint16_t devInd, float* temp);

/******************************************************************************
** monitor_read_supply_voltage
**
** Reads VCC in V.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param vcc [float**] Variable that will contains the vcc values.
**
** @param nVCCs [int*] Number of VCCs returned.
**
** @return [int] If it success returns 0, otherwise -1.
**
******************************************************************************/
int monitor_read_supply_voltage(const uint16_t devInd, float** vcc, int* nVCCs);

/******************************************************************************
** monitor_read_optical_power
**
** Reads optical power.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param opPwr [float**] Variable that will contains the optical power value.
**
** @param nOpPwrs [int*] Number of optical powers returned.
**
** @return [int] If it success returns 0, otherwise -1.
**
******************************************************************************/
int monitor_read_optical_power(const uint16_t devInd, float** opPwr, int* nOpPwrs);

/******************************************************************************
** monitor_read_bias_monitor
**
** Reads BIAS monitor.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param bias [float**] Variable that will contains the bias values.
**
** @param nBias [int*] Number of bias returned.
**
** @return [int] If it success returns 0, otherwise -1.
**
******************************************************************************/
int monitor_read_bias_monitor(const uint16_t devInd, float** bias, int* nBias);

/******************************************************************************
** quality_Qfactor
**
** Calculates Q Factor. This value is an statistical calcutaion of the quantic
** quality based on the running average of the output and the correlators.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param qFactor [float*] Variable that will contains the qFactor value.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int quality_Qfactor(const uint16_t devInd, float* qFactor);

/******************************************************************************
** get_laser_temperatures
**
** Reads power supply voltage of the resistors that heat the lasers.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param temp [float**] Variable that will contains the temperature values.
**
** @param nTemps [int*] Number of temperatures returned.
**
** @return [int] If it success returns 0, otherwise -1.
**
******************************************************************************/
int get_laser_temperatures(const uint16_t devInd, float **temp, int *nTemps);

/******************************************************************************
** get_laser_status
**
** Gets laser status.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param laserStatus [int**] Variable that will contains the laser status values.
**
** @param nLasers [int*] Number of lasers status returned.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int get_laser_status(const uint16_t devInd, int **laserStatus, int *nLasers);

/******************************************************************************
** get_Vcomp
**
** Gets voltage comparator in volts.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param vComp [float*] Variable that will contains the compare voltage.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int get_Vcomp(const uint16_t devInd, float *vComp);

/******************************************************************************
** get_hmin
**
** Gets the minimum entropy of the system. This value only changes after
** calibration.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param hMin [float*] Variable that will contains the hMin value.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int get_hmin(const uint16_t devInd, float *hMin);

/******************************************************************************
** get_calibration_status
**
** Get QRNG calibration status.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @param status [calibrationStatus*] Contains the status of the calibration
**                                    process.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int get_calibration_status(const uint16_t devInd, calibrationStatus* status);

/******************************************************************************
** check_thresholds
**
** Checks if the monitors of the system are between the correct operational
** limits.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int check_thresholds(const uint16_t devInd);

/******************************************************************************
** update_thresholds.
**
** Updates the thresholds of the monitors. This function must be called after
** the calibration of the system and usually called in a regular period to
** maintain the alarms updated.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int update_thresholds(const uint16_t devInd);

/******************************************************************************
** get_monitor_value
**
** Gets the value of an specific monitor.
**
** @param at [const alarmType] Enum that specifies the monitor to check.
**
** @param num [size_t*] Returns the number of measured values related to
**                      this monitor.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
monitorValue* get_monitor_value(const alarmType at, size_t* num, const uint16_t devInd);

/******************************************************************************
** set_monitor_enable
**
** Sets the monitor status, true means that the check_thresholds function
** will evaluate the value of the monitor, otherwise no.
**
** @param at [const alarmType] Enum that specifies the monitor to set.
**
** @param enable [size_t*] Value to set to the monitor status.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
void set_monitor_enable(const alarmType at, const bool enable, const uint16_t devInd);

/******************************************************************************
** set_calibration
**
** Send an order to the QRNG to calibrate the system. This operation will block
** the QRNG until it finished the calibration.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int set_calibration(const uint16_t devInd);

/******************************************************************************
** set_calibration_with_fixed_VTC
**
** Send an order to the QRNG to calibrate the system without change the pevious
** vtc set values to the lasers. This operation will block the QRNG until it
** finished the calibration.
**
** This operation only will have effect in the FMC ONE.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array.
**
** @return [int] If it success 0, otherwise returns -1.
**
******************************************************************************/
int set_calibration_with_fixed_VTC(const uint16_t devInd);

/******************************************************************************
** config_network
**
** Changes the network configuration.
**
** @param mac [unsigned char*] New MAC address.
**
** @param ip [unsigned char*] New IP address.
**
** @param gateway [unsigned char*] New gateway address.
**
** @param netmask [unsigned char*] New netmask.
**
** @param devInd [const uint16_t] Index of the device to control defined in
**                                devices array
**
** @return [int] If it success 0, otherwise returns -1.
******************************************************************************/
int config_network(char* mac, char* ip, char* gateway, char* netmask,
		const uint16_t devInd);

/******************************************************************************
** get_num_lasers.
**
** Returns the number of lasers.
**
** @return [int] Number of lasers
**
******************************************************************************/
int get_num_lasers(void);

/******************************************************************************
** get_Delta_t
**
** Gets the time that the library caller should wait between to different calls
** of updateThresholds function.
**
** @return [size_t] Time in seconds.
**
******************************************************************************/
size_t get_Delta_t(void);

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

/******************************************************************************
** formNetworkJSON
**
** Parse a JSON message to char array. In this case the data field is a
** char array.
**
** @param ID [const char *] TODO: BERTO!
** @param cmd [const char *] TODO: BERTO!
** @param addr [const char *] TODO: BERTO!
** @param err [const char *] TODO: BERTO!
** @param data [char **] TODO: BERTO!
** @param sizedata [const uint32_t]
** @param ext [const char *] TODO: BERTO!
**
** @return [char*] Returns the message in char array format.s
******************************************************************************/
char* formNetworkJSON(const char *ID, const char *cmd, const uint32_t addr,
		const uint32_t dev, const uint32_t err, const char** data,
		const uint32_t sizeData, const uint32_t ext);

#ifdef __cplusplus
}
#endif

#endif /* QUSIDE_QRNG_ADMIN_H */
