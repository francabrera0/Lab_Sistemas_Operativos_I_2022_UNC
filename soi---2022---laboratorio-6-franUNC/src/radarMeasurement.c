/**************************************************************************
 * @file         radarMeasurement.c
 * @brief        Contains all functions support for process a file.
 * @version      1.0
 * @date         8. November. 2022
 * @author       Fran Cabrera
 **************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "../include/radarMeasurement.h"

/***********************************************************************
 * @brief        Return the instances (and their number) of measurements
 * 					presents in the file.
 * @param[in]    pathToFile             Path of the file to process  
 * @param[in]    numberOfInstances      Pointer to store the value of 
 *                                       the number of instances
 * @return       measurement            Pointer to radarMeasurement
 **********************************************************************/
radarMeasurement* getInstances(char* pathToFile, int* numberOfInstances){
	
	int fd = open(pathToFile, O_RDONLY);
	if(fd == -1)
		fd = open("./rawdata/datos", O_RDONLY);

	if(fd == -1){
		perror("Could not open the file");
		exit(EXIT_FAILURE);
	}

	struct stat sb;
	if(fstat(fd, &sb) == -1){
		perror("Could not calculate stats of the file");
		exit(EXIT_FAILURE);
	}


	*numberOfInstances = (sb.st_size/sizeof(radarMeasurement));

	radarMeasurement* measurement = mmap(NULL, sizeof(radarMeasurement)*(*numberOfInstances), PROT_READ, MAP_PRIVATE, fd, 0);
	if(measurement == MAP_FAILED){
		perror("Could not mapped file into memory");
		exit(EXIT_FAILURE);
	}

	return measurement;
	close(fd);
}

/***********************************************************************
 * @brief        Return the average of the field valid samples of 
 *                n instances.
 * @param[in]    measurement        Pointer to the first instance  
 * @param[in]    instances          Number of instances
 * @return       average            Average of valid samples
 **********************************************************************/
unsigned int getAverage(radarMeasurement* measurement, int instances){
	unsigned int average = 0;

	for(int i=0; i<instances; i++)
		average += measurement[i].validSamples;

	return average/instances;
}

/***********************************************************************
 * @brief        Print the value of each field of an instance 
 * @param[in]    measurement        radarMeasurement instance  
 * @return       nothing
 **********************************************************************/
void printMeasurement(radarMeasurement measurement){
	printf("Data version: %d\n",measurement.version);
	printf("Drx version: %d\n",measurement.drxVersion);
	printf("reserved1: %s\n",measurement.reserved1);
	printf("initCW: %lf\n",measurement.initCW);
	printf("azimuth: %f\n",measurement.azimuth);
	printf("elevation: %f\n",measurement.elevation);
	printf("idVolume: %d\n",measurement.idVolume);
	printf("idScanning: %d\n",measurement.idScanning);
	printf("idSet: %d\n",measurement.idSet);
	printf("idGroup: %d\n",measurement.idGroup);
	printf("idPulse: %d\n",measurement.idPulse);
	printf("initScanning: %d\n",measurement.initScanning);
	printf("endScanning: %d\n",measurement.endScanning);
	printf("endGroup: %d\n",measurement.endGroup);
	printf("inhibited: %d\n",measurement.inhibited);
	printf("validSamples: %d\n",measurement.validSamples);
	printf("nAcquisition: %d\n",measurement.nAcquisition);
	printf("reserved2: %s\n",measurement.reserved2);
	printf("nSequence: %d\n",measurement.nSequence);
	printf("readTimeHigh: %lu\n",measurement.readTimeHigh);
	printf("readTimeLow: %lu\n",measurement.readTimeLow);
	printf("reserved3: %s\n",measurement.reserved3);
	printf("\n\n");
}
