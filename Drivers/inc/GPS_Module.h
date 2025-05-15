
#ifndef GPS_MODULE_H
#define GPS_MODULE_H

#include "UART.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#define EARTH_RADIUS 6371000.0f  // Earth's radius in meters
#define M_PI 3.141592653589793

extern float Locations_Latt [12];
extern float Locations_Long [12];
float nmea_to_decimal(float );
float gps_distance_haversine(float , float , float ,float );
void config_Latt(float *);
void config_Long(float *);
int NearerTo(float,float,float*);
float GPS_format_lattitude(const char *);
float GPS_format_longitude(const char *);
const char *GPS_read();





#endif // GPS_MODULE_H

