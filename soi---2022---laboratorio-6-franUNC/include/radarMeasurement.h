/**************************************************************************
 * @file         radarMeasurement.h
 * @brief        Contains all definitions and functions prototype support 
 * 					for process a file.
 * @version      1.0
 * @date         8. November. 2022
 * @author       Fran Cabrera
 **************************************************************************
 */

#ifndef RADAR_MEASUREMENT_H
#define RADAR_MEASUREMENT_H

#include <stdbool.h>

/**
 * @brief radarMeasurement type definition
 */ 
typedef struct __attribute__((__packed__))
{
	short unsigned int version, //Data version number one                                   |  2bytes
	                   drxVersion; //Version of the Drx that generated the data number one  |  2bytes
	
	char reserved1[4]; //Reserved                                                           |  4bytes
	
	double initCW; //Conversion window start, in seconds                                    |  8bytes
	
	float azimuth, //Azimuth pointing, in degrees                                           |  4bytes
	      elevation; //Elevation pointing, in degrees                                       |  4bytes
	
	short unsigned int idVolume, //Volume identifier                                        |  2bytes
	                   idScanning, //Scanning identifier                                    |  2bytes
	                   idSet, //Set identifier                                              |  2bytes
	 				   idGroup,	 //Group identifier                                         |  2bytes
	 				   idPulse; //Pulse identifier                                          |  2bytes

	bool initScanning, //Start scanning flag                                                | 1byte
	     endScanning, //Last scanning pulse flag	                                        | 1byte
	     endGroup, //Last group pulse flag                                                  | 1byte
	     inhibited;	//Inhibited measurement flag                                            | 1byte	

	short unsigned int validSamples, //Number of valid samples                              | 2bytes
	                   nAcquisition; //Number of acquisitions                               | 2bytes

	char reserved2[2]; //Reserved                                                           | 2bytes

	unsigned int nSequence; //Number of sequence                                            | 4bytes

	long unsigned int readTimeHigh, //Timestamp high field		                            | 8bytes
	                  readTimeLow; //Timestampo low field                                   | 8bytes

	char reserved3[64]; //Reserved                                                          | 64bytes

}radarMeasurement;



void printMeasurement(radarMeasurement measurement);
radarMeasurement* getInstances(char* pathToFile, int* numberOfInstances);
unsigned int getAverage(radarMeasurement* measurement, int instances);

#endif /*RADAR_MEASUREMENT_H*/