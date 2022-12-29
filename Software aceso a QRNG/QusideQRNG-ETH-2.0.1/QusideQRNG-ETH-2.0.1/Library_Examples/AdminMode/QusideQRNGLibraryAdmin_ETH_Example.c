/*
 ============================================================================
 Name        : QusideQRNGLibraryAdmin_ETH_Example.c
 Author      : Alvaro Velasco Garcia, Heriberto J. Díaz Luis-Ravelo
 Created on  : 01 jul. 2022
 Version     : 0.1
 Copyright   : Copyright (C) 2022 QUSIDE TECHNOLOGIES - All Rights Reserved.
 	 	 	   Unauthorized copying of this file, via any medium is
 	 	 	   strictly prohibited.
 Description : This is an example to use the QusideQRNGLibrary for ETH in
 	 	 	   Admin mode.
 ============================================================================
 */

#include <quside_QRNG_admin.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	/* In this example it is implemented the minimum source code to
	 * capture random data from a QRNG.
	 */

	/* connectToServer connect with the QRNG, and it need the QRNG IP address as
	 * parameter.
	 */
	if(connectToServer("xxx.xxx.xxx.xxx") != 0) {
		puts("Error connect.");
		return -1;

	} else {
		puts("Connected");
	}

	/* Lets try to capture random data. */

	/* This variable has to be set to 0. */
	const int devIndex = 0;

	if(devIndex != -1) {

		/* Number of random numbers in bytes. */
		const size_t numberOfRandomNumbers = 1024;
		uint32_t* randomNumbers = (uint32_t*)malloc(sizeof(uint32_t) * numberOfRandomNumbers);
		float temp;

		/* With this function read the QRNG temperature. */
		monitor_read_temperature(devInd, &temp);

		/* Now we will print the QRNG temperature. */
		printf("Temperature: %f\n", temp);

		/* With this function captures numberOfRandomNumbers bytes of extracted
		 * random numbers.
		 */
		if(get_random(randomNumbers, numberOfRandomNumbers, devIndex) == -1) {
			puts("Some error occurs");
		}

		/* Now we will print the extracted random numbers. */
		for(int i = 0; i < (int)(numberOfRandomNumbers >> 2); ++i) {
			printf("Random number %d: %u\n", i, randomNumbers[i]);
		}

		/* And we will release the memory of our program. */
		free(randomNumbers);

	} else {
		puts("Some error occurs");
	}

	/* disconnectServer disconnect the QRNG.
	 * NOTE: IT IS MANDATORY TO EXECUTE THIS FUNCTION BEFORE CLOSING THE APPLICATION.
	 */
	disconnectServer();

	/* To compile the code:
	 * 		gcc QusideQRNGLibraryAdmin_ETH_Example.c -lqusideQRNGadmin -o QusideQRNGLibraryAdmin_ETH_Example
	 */

	return 0;
}
