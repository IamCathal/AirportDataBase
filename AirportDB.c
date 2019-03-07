#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define PI  3.14159265358979324

struct airport {
		int ID;
		char name[30];
		char city[30];
		char country[40];
		char IATA[5];
		char ICAO[5];
		double latitude;
		double longitude;
		int altitude;
		int timezone;
		char DST[2];
		char olsenTimezone[30];
		char type[15];
		char source[20];
};

struct airport airportArr[7543];  

int numLines = 0;
int opened = 0;


int intakeData(char *fileName) {
	
	  FILE *fptr;
	  fptr = fopen(fileName, "r");
	  char ch;
	  
	  if (fptr == NULL) {
	  	printf("Error opening file!");
	  } else {
		
		int i;
		 
		char lineRaw[300]; // Variable to get a whole line in the file 
		
		char latString[20], longString[20], timezoneString[3]; // Stores the latitude, longitude and timezones in strings before being converted
			
		while (!feof(fptr)) {
			ch = fgetc(fptr);
			if (ch == '\n') {
				numLines++;
			}
		}
		
		
		rewind(fptr); // rewinds file pointer to the beginning
		
			
			char *token;
			char delim[3] = ",\"";
			char noInfoString[2] = "na"; 
			
			for (i = 0 ; i < numLines; i++) {
				
				fgets(lineRaw, 250, fptr);
				
					token = strtok(lineRaw, delim);
						airportArr[i].ID = atoi(token);
						
					token = strtok(NULL, delim);
						strcpy(airportArr[i].name, token);
						
					token = strtok(NULL, delim);
						strcpy(airportArr[i].city, token);
					
					token = strtok(NULL, delim);
						strcpy(airportArr[i].country, token);
						
					/* If the string is "empty" (\N), it is replaced with the string  "na" */	
						
					token = strtok(NULL, delim);
						if (strcmp(token, "\\N") == 0) {
							strcpy(airportArr[i].IATA, noInfoString); 
						} else {
							strcpy(airportArr[i].IATA, token); 
						}
						
					token = strtok(NULL, delim);
						strcpy(airportArr[i].ICAO, token);
						
					token = strtok(NULL, delim);
						strcpy(latString, token);
						airportArr[i].latitude = atof(latString);
						
					token = strtok(NULL, delim);
						strcpy(longString, token);
						airportArr[i].longitude = atof(longString);	
						
					token = strtok(NULL, delim);
						airportArr[i].altitude = atof(token);
						
					token = strtok(NULL, delim);
						strcpy(timezoneString, token);
						airportArr[i].timezone = atoi(timezoneString);	
						
					token = strtok(NULL, delim);
						if (strcmp(token, "\\N") == 0) {
							strcpy(airportArr[i].DST, noInfoString); 
						} else {
							strcpy(airportArr[i].DST, token); 
						}
						
					token = strtok(NULL, delim);
						if (strcmp(token, "\\N") == 0) {
							strcpy(airportArr[i].olsenTimezone, noInfoString); 
						} else {
							strcpy(airportArr[i].olsenTimezone, token); 
						}

					token = strtok(NULL, delim);
						if (strcmp(token, "\\N") == 0) {
							strcpy(airportArr[i].type, noInfoString); 
						} else {
							strcpy(airportArr[i].type, token); 
						}
					
					token = strtok(NULL, delim);
						if (strcmp(token, "\\N") == 0) {
							strcpy(airportArr[i].source, noInfoString); 
						} else {
							strcpy(airportArr[i].source, token); 
						}
										
			}
		
			fclose(fptr);
					
		} 
}


		void searchById() {
			
			int userInput = 1;
			int i, found = 0;
		
			printf("****************************************");
			
			while (userInput != 0) {
				
				printf("\nEnter an ID to search(0 to exit): ");
				scanf("%d", &userInput);
				found = 0;
				
				for (i = 0; i < numLines; i++ ) {
					if (airportArr[i].ID == userInput) {
						printf("\n****************************************\nID: %d\nName: %s\nCity: %s\nCountry: %s\nIATA: %s\nICAO: %s\nLatitude: %lf\nLongitude: %lf\nAltitude: %d\nTiemzone: %d\nDST: %s\nO-Timezone: %s\nType: %s\nSource: %s\n",
						airportArr[i].ID, 
						airportArr[i].name,
						airportArr[i].city,
						airportArr[i].country, 
						airportArr[i].IATA, 
						airportArr[i].ICAO,
						airportArr[i].latitude, 
						airportArr[i].longitude, 
						airportArr[i].altitude,
						airportArr[i].timezone, 
						airportArr[i].DST, 
						airportArr[i].olsenTimezone,
						airportArr[i].type, 
						airportArr[i].source);
						printf("\n****************************************");
						found = 1;	
					}
				}
					
				
					if ( i == numLines && found != 1) { 
					/* If the search has gone atleast once and the input is 0 it goes back to search menu */
						if (userInput == 0) {
							searchMenu();
						} 	else {
					/* If the search has gone atleast once and nothing was found it tells the user */
							printf("\nNo airport with ID \"%s\" found.\n", userInput);
						}
						
						
					}	
			} 			
		}
		
	double degreesToRadians(double degrees) {
		return (degrees * PI / 180);
	}
	
	double radiansToDegrees(double radians) {
		return (radians * 180 / PI);
	}
	
	double coordDistance(double latitudeSearch, double longitudeSearch, double latitudeCurr, double longitudeCurr) {
		
		latitudeSearch = degreesToRadians(latitudeSearch); // latitudeSearch is the user entered latitude
		longitudeSearch = degreesToRadians(longitudeSearch); // longitudeSearch is the user entered longitude
		latitudeCurr = degreesToRadians(latitudeCurr);   // latitudeCurr is the latitude of the current entry being compared against
		longitudeCurr = degreesToRadians(longitudeCurr);  // longitudeCurr is the longitude of the current entry being compared against
		
		long double longDist = longitudeCurr - longitudeSearch; // Total longitudanal distance
		long double latDist = latitudeCurr - latitudeSearch;  // Total latitudinal distance
		
		long double distance = pow( sin(latDist / 2), 2 ) + cos( latitudeSearch) * cos( latitudeCurr) * pow( sin(longDist / 2), 2);
		
		distance = 2 * asin( sqrt(distance) );
		
		distance = distance * 6371;
		
		return(distance);
	}

	
	void searchFunction(char *searchType) {
		
			int i, found = 0;
			char userInput[40] = "";
			
			printf("****************************************");
			
			
			/* To decrease redundant code, this function deals with searching for all string searches using
			a series of else if statements */
			while (userInput != "0") {
				if ( strcmp(searchType, "name") == 0) { printf("\n\nEnter an airport name (0 to exit):"); }
				else if (strcmp (searchType, "city")== 0) { printf("\n\nEnter a city (0 to exit):");}		
					else if (strcmp (searchType, "country")== 0) { printf("\n\nEnter a country (0 to exit):");}		
						else if (strcmp (searchType, "IATA")== 0) { printf("\n\nEnter an IATA (0 to exit):");}
							else if (strcmp (searchType, "ICAO")== 0) { printf("\n\nEnter an ICAO (0 to exit):");}
						
						
						scanf(" %[^\n]s", userInput);  // Reads up until the enter key is pressed which can let the user type in multiple words.
				
				
				for (i = 0; i < numLines; i++) {
					/* If the respected match is found it prints out the airport information */
					if ( strcmpi(userInput, airportArr[i].city) == 0 ||  strcmpi(userInput, airportArr[i].name) == 0 || 
						strcmpi(userInput, airportArr[i].country) == 0 || strcmpi(userInput, airportArr[i].IATA) == 0 ||
						strcmpi(userInput, airportArr[i].ICAO) == 0 ) {
							
						printf("\n****************************************\nID: %d\nName: %s\nCity: %s\nCountry: %s\nIATA: %s\nICAO: %s\nLatitude: %lf\nLongitude: %lf\nAltitude: %d\nTiemzone: %d\nDST: %s\nO-Timezone: %s\nType: %s\nSource: %s\n",
						airportArr[i].ID, 
						airportArr[i].name,
						airportArr[i].city,
						airportArr[i].country, 
						airportArr[i].IATA, 
						airportArr[i].ICAO,
						airportArr[i].latitude, 
						airportArr[i].longitude, 
						airportArr[i].altitude,
						airportArr[i].timezone, 
						airportArr[i].DST, 
						airportArr[i].olsenTimezone,
						airportArr[i].type, 
						airportArr[i].source);
						printf("\n****************************************");
						found = 1;
					}
				}    		if ( i == numLines && found != 1) { 
						if (userInput == 0) {
							searchMenu();
						} 	else {
							if ( strcmp(searchType, "name") == 0) {
								printf("\nNo airport with name \"%s\" found.\n", userInput);	
							} else  if ( strcmp(searchType, "city") == 0) {
								printf("\nNo airport with city \"%s\" found.\n", userInput);	
							} else  if ( strcmp(searchType, "country") == 0) {
								printf("\nNo airport with country \"%s\" found.\n", userInput);	
							} else  if ( strcmp(searchType, "IATA") == 0) {
								printf("\nNo airport with IATA \"%s\" found.\n", userInput);	
							} else  if ( strcmp(searchType, "ICAO") == 0) {
								printf("\nNo airport with ICAO \"%s\" found.\n", userInput);	
							}
						}
			}
			 /* If input is 0 the program returns to the search menu */
			if (strcmp(userInput, "0") == 0) {
				searchMenu();
			}
			
		
		}
	}
	
	void searchCoords() {
	
	int i, found = 0, userDistance; // userDistance is the radius of search that the user defines to find airports in.
	char userInput[20];	
	double latitudeInput, longitudeInput;  // The search coordinates
	double latitudeCurr, longitudeCurr;	 // The comparison coordinates	
			
			while (userInput != 0) {
				
				printf("Please enter the latitude and longitude (decimal degrees, 0 to exit): ");
				scanf(" %[^\n]s", userInput); 
				
				printf("Please enter radius of the circle in km to search: ");
				scanf("%d", &userDistance);
				
				
				if (strcmp(userInput, "0") == 0) {
				searchMenu();
			}
				
			char *token;
			char delim[2] = " ";
			
			double seperation = 0;
	
				 token = strtok(userInput, delim);
				 	latitudeInput = atof(token); 
				 
				 token = strtok(NULL, delim);
				 	longitudeInput = atof(token);
				 	
				 	printf("\n");
				 	
				 	for( i = 0; i < numLines; i++) {
				 		latitudeCurr = airportArr[i].latitude;
				 		longitudeCurr = airportArr[i].longitude;
				 		
				 		seperation = coordDistance(latitudeInput, longitudeInput, latitudeCurr, longitudeCurr);
						 /* If an airport within range and not itself is found, it's name is displayed */
				 		if ( seperation < userDistance && seperation != 0) {
				 			printf("%s in %s is %.0lfkm away from your coordinates.\n", airportArr[i].name, airportArr[i].city, seperation);
						 	found++;
						 }
				 		
				 		
					 }
					 
					 if ( i == numLines && found < 1) { 
						if (userInput == 0) {
							searchMenu();
						} 	else {
							printf("\nNo airports within %d km  found.\n", userDistance);
						}
						
						
					}
					
					printf("\n****************************************\n");	
			}
			
							
		}
	

	
	int searchMenu() {
		
		int option;
	
		
		if (opened >= 1) {
			printf("\n****************************************\n");	
		}
		printf("1. Search by ID\n");
		printf("2. Search by name\n");    
		printf("3. Search by city\n");
		printf("4. Search by country\n");
		printf("5. Search by IATA\n");
		printf("6. Search by ICAO\n");
		printf("7. Search by Lattitude/Longitude\n");
	
		opened++;
		
		printf("\nWhich search would you like to use: ");
		scanf("%d", &option);
		
			switch (option) {
				case 1:	searchById();
				case 2: searchFunction("name");
				case 3: searchFunction("city");
				case 4: searchFunction("country");
				case 5: searchFunction("IATA");
				case 6: searchFunction("ICAO");
				case 7: searchCoords();
	
				
			}
	}

	void main() {
		
		char file[] = "airportstext.txt";
		char datFile[] = "airportDBDAT.dat";
		int option;
		
		intakeData(file);
		
		//binaryData(datFile, lineCount);
		
		searchMenu();
			
	}
	
