/**************************************************************************
 * @file         main.c
 * @brief        This program file makes use of the functions defined
 *                 in radarMeasurement.h for process a file.
 * @version      1.0
 * @date         8. November. 2022
 * @author       Fran Cabrera
 **************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>

#include "../include/radarMeasurement.h"

#define PATH "../rawdata/datos"

int main(int argc, char* argv[]){

	radarMeasurement* measurement;
	int instances;
	
	measurement = getInstances(PATH, &instances);

	for(int i=0; i<instances; i++){
		printf("Measurement n° %d\n", i+1);
		printf("---------------------\n");
		printMeasurement(measurement[i]);
	}

	unsigned int average = getAverage(measurement, instances);

	printf("Average of %d valid samples: %d\n", instances, average);
	printf("----------------------------------------------------\n");

	return EXIT_SUCCESS;
}