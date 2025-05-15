#include <math.h>
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"
#include "GPS_Module.h"
#include "LCD.h"
#include "strintofloat.h"
#include "floattostring.h"
float Locations_Latt[12] ={0,3003.91107,3003.855712,3003.82492,3003.7971190,3003.818847,3003.855468,3003.842041,3003.942382,3003.871826,3003.896728,3003.874755};
float Locations_Long [12]={0,03116.80906,3116.835449,03116.83434,3116.737304,3116.707031,3116.716552,3116.747314,3116.704101,3116.670654,3116.709472,3116.816138};

float nmea_to_decimal(float nmea_coord) {
    int degrees = (int)(nmea_coord / 100); ////3026.4567==>30.264567==>30
    float minutes = nmea_coord - (degrees * 100);//3026.4567-30*100
    float decimal_degrees = degrees + (minutes / 60.0f);///26.4567/60==>0.4496+30==>30.4496
    return decimal_degrees; ////
}

int NearerTo(float current_latt,float current_long,float* min_dis )
{
	float min_distance = 0.0;
	float distance [12];
	int i;
	int minIndex = 0;	
	
	for(i=0;i<12;i++)
	{
		
		float distanceFromElement =gps_distance_haversine(nmea_to_decimal(Locations_Latt[i]),nmea_to_decimal(Locations_Long[i]),nmea_to_decimal(current_latt),nmea_to_decimal(current_long));
		distance[i]=distanceFromElement;

	}
	  
    for (i = 1; i < 12; i++) {
        if (distance[i] < distance[minIndex]) {
            minIndex = i;
        }
		}
		
		min_distance = distance[minIndex];
		*min_dis = min_distance;
		return minIndex;
}

float gps_distance_haversine(float lat1_deg, float lon1_deg, float lat2_deg, float lon2_deg) {
    // Convert degrees to radians
    float lat1 = lat1_deg * (M_PI / 180.0f);
    float lon1 = lon1_deg * (M_PI / 180.0f);
    float lat2 = lat2_deg * (M_PI / 180.0f);
    float lon2 = lon2_deg * (M_PI / 180.0f);

    // Differences
    float dlat = lat2 - lat1;
    float dlon = lon2 - lon1;

    // Haversine formula
    float a = sinf(dlat / 2.0f) * sinf(dlat / 2.0f) +
              cosf(lat1) * cosf(lat2) *
              sinf(dlon / 2.0f) * sinf(dlon / 2.0f);

    float c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));

    // Distance in meters
    float distance = EARTH_RADIUS * c;

    return distance;
		
}


void config_Latt(float *locationsLat)
{
	int i;
	    for (i = 0; i < 6;i++) {
        Locations_Latt[i]=locationsLat[i];
    }
}
void config_Long(float *locationsLong)
{
	int i;
	    for (i = 0; i < 6;i++) {
        Locations_Long[i]=locationsLong[i];
    }
}


float GPS_format_lattitude(const char * GPS){
	
int noOfComma	=0;
char Lat [20];
int LatIndex =0;
	int i; 
	for( i=0 ; i<67;i++)
	{

		///Check if i reached the end of the GPS to terminate the for loop     ///for further optimization check no of commas
		if(GPS[i]=='*')

		{
			break;
		}



		///Counter for the number of commas
			else if(GPS[i]==',')
			{
				noOfComma++;
			}




			///if to copy the lat  ///add 1 to index to return size

			if ( noOfComma>=2&&noOfComma<3)
			{
				Lat[LatIndex]=GPS[i+1];
				LatIndex++;

			}
			else if(noOfComma==3)
			{
				Lat[LatIndex-1]='\0';
		
	
					float ret =stringToFloat(Lat);
				
				return ret;
			}

		}
			return 0.0;
	      
}
	float GPS_format_longitude(const char *GPS)
	{
	
	int noOfComma	=0;
	char Lon [20];
	int LonIndex =0;
		int i=0;
		for(i =0 ; i<82;i++)
		{

			///Check if i reached the end of the GPS to terminate the for loop     ///for further optimization check no of commas
			if(GPS[i]=='*')

			{
				break;
			}


		
			///Counter for the number of commas
				if(GPS[i]==',')
				{
					noOfComma++;
				}





				///if to copy the lat  ///add 1 to index to return size

			
				if ( noOfComma>=4&&noOfComma<5)
				{
					Lon[LonIndex]=GPS[i+1];
					LonIndex++;

				}
				else if(noOfComma==5)
				{
						
					Lon[LonIndex-1]='\0';
					float ret = stringToFloat(Lon);	
					return ret;

				}
			}

		return 0.0;
							 
	}

    
    /////Read////////////////////////////
  
const char *GPS_read() {
static char GPS[80];
char GPS_logName[] = "$GPGGA";
    char recievedChar;
    char flag = 1;
	UART_ConfigType uart = {
    EIGHT_BITS,
		ONE_STOP_BIT,
    u1_B
		};
		
		init_uart(&uart);

    do {
			int c;
        flag = 1;
			
        for ( c=0 ; c < 6; c++) {
            if (recieveByte_uart(u1_B) != GPS_logName[c]) {
                flag = 0;
                break;
            }
        }
    }
    while (flag == 0);
    {
        
strcpy(GPS, ""); // Init GPS Array

	int fillGPScounter = 0;
			
do {
    recievedChar = recieveByte_uart(u1_B);
    GPS[fillGPScounter++] = recievedChar;
   }
while (recievedChar != '*');

    }
    // Here I make sure that I received the correct log
    
    return GPS;
    
    
    
    
}

