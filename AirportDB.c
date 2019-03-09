#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define PI  3.14159265358979324

void searchMenu();
struct airport {
		int ID;
		char name[40];
		char city[20];
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

struct nearbyAirport {
	char name[40];
	char city[30];
	double distance;
};


struct airport airportArr[7543]; 

struct nearbyAirport nearbyAirportArr[400];

struct nearbyAirport swap;

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
	
		rewind(fptr);
	
			char *token;
			char delim[3] = ",\"";
			char noInfoString[2] = "na"; // Some entries have no data and have the entry "\N", these are replaced with "na"
			
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
							printf("\nNo airport with ID \"%d\" found.\n", userInput);
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
		
		return(distance); // Returns the actual displacement between airports, complicated since it calculates the distance on a sphere.
	}

	
	void searchFunction(char *searchType) {
		
			int i, found = 0;
			char userInput[40] = "";
			
			printf("****************************************");
			
			
			/* To decrease redundant code, this function deals with searching for all string searches using
			a series of else if statements */
			while (strcmp(userInput, "0") != 0 ) {
				if ( strcmp(searchType, "name") == 0) { printf("\n\nEnter an airport name (0 to exit):"); }
				else if (strcmp (searchType, "city")== 0) { printf("\n\nEnter a city (0 to exit):");}		
					else if (strcmp (searchType, "country")== 0) { printf("\n\nEnter a country (0 to exit):");}		
						else if (strcmp (searchType, "IATA")== 0) { printf("\n\nEnter an IATA (0 to exit):");}
							else if (strcmp (searchType, "ICAO")== 0) { printf("\n\nEnter an ICAO (0 to exit):");}
						
						
						scanf(" %[^\n]s", userInput);  // Reads up until the enter key is pressed which can let the user type in multiple words.
				
				int count = 0;
				for (i = 0; i < numLines; i++) {
					/* If the respected match is found it prints out the airport information */
					if ( strcmpi(userInput, airportArr[i].city) == 0 ||  strcmpi(userInput, airportArr[i].name) == 0 || 
						strcmpi(userInput, airportArr[i].country) == 0 || strcmpi(userInput, airportArr[i].IATA) == 0 ||
						strcmpi(userInput, airportArr[i].ICAO) == 0 ) {
						
						count++;
						
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
				
				printf("\nThere were %d airports found", count); 		
				printf("\n****************************************");
					
							if ( i == numLines && found != 1) { 
						if (userInput == 0) {
							searchMenu();
						} 	else { // Prints the respected outputs if nothing of the searched for item is found
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
	
	int i, k, found = 0; 
	double userDistance;
	char userInput[40];	
	double latitudeInput, longitudeInput; // latitudeInput and longitudeInput are the users coordinates that are entered
	double latitudeCurr, longitudeCurr;	// latitudeCurr and longitudeCurr are the coordinates to be comapared against for each repitition of the searching for loop

			
			while (userInput != 0) {
				
				printf("Please enter an airport: ");
					scanf(" %[^\n]s", userInput);
				
				printf("Please enter a search radius (0 to exit): ");
					scanf(" %lf", &userDistance);
						
						while ( userDistance > 1000) {
							printf("\nRadius too large, please enter a value under 500.\n");
							printf("Please enter a search radius (0 to exit): ");
								scanf(" %lf", &userDistance);
						}
		
				if (strcmp(userInput, "0") == 0) {
				searchMenu();
			} 
		
				
			char *token;
			char delim[2] = " ";
			
			double seperation = 0; // Holds the value for the actual displacement between the two sets of coordinates in comparison to eachother
	
				 for (i = 0; i < numLines; i++) {
				 	if (strcmpi(userInput, airportArr[i].name) == 0) {
				 		latitudeInput = airportArr[i].latitude;
				 		longitudeInput = airportArr[i].longitude;
					 }
				 }
				 	printf("\n");
				 	
				 	for( i = 0; i < numLines; i++) {
				 		latitudeCurr = airportArr[i].latitude;
				 		longitudeCurr = airportArr[i].longitude;
				 		
				 		seperation = coordDistance(latitudeInput, longitudeInput, latitudeCurr, longitudeCurr);
				 		// If the coordinates are within userDistance and it is not the coordinates of an existing airport (0km away) print this airport's information
				 		
				 			// Fills array of structures of nearby airports, max 400 due to logic
					 		if ( seperation < userDistance && seperation > 2) {
					 			strcpy(nearbyAirportArr[found].name, airportArr[i].name);
					 			strcpy(nearbyAirportArr[found].city, airportArr[i].city);
					 			nearbyAirportArr[found].distance = seperation;
							 	found++;
							 }
							 
					 }
					 
					// Bubble sort to sort out these in ascending order 
					for ( i = 0; i < found - 1; i++) {
						
							for (k = 0; k < found - 1 - i; k++) {
								if (nearbyAirportArr[k].distance > nearbyAirportArr[k + 1].distance) {
									swap = nearbyAirportArr[k];
									nearbyAirportArr[k] = nearbyAirportArr[k+1];
									nearbyAirportArr[k+1] = swap;
								}
							}
					}
					
						printf("\n****************************************\n");	
						//  Prints the results in a nice format, must make the terminal screen big for this to be viewed correctly
						 printf("\n");

						 printf("%40s%17s     %s\n", "Airport", "City", "Distance");
						 printf("%40s%17s     %s\n", "=======", "====", "========");
						 
						 for (i = 0; i < found; i++) {
						 	printf("%40s%21s     %.0lfkm\n", nearbyAirportArr[i].name, nearbyAirportArr[i].city, nearbyAirportArr[i].distance);
						 }		 printf("\n");
						 
					
				 	printf("\n****************************************\n");	
				 		
					 }
					 // If unsuccessful in it's search, inform the user
					 if ( i == numLines && found < 1) { 
						if (userInput == 0) {
							searchMenu();
						} 	else {
							printf("\nNo airports within %d km  found.\n", 100);
						}
						
						
					}
					
					printf("\n****************************************\n");	
			}
			
							

	

	
	void searchMenu() {
		
		int option = 0;
	
		// This function handles the search menu interface and links to all other functions	
		if (opened >= 1) {
			printf("\n****************************************\n");	
		}
		printf("1. Search by ID\n");
		printf("2. Search by name\n");    
		printf("3. Search by city\n");
		printf("4. Search by country\n");
		printf("5. Search by IATA\n");
		printf("6. Search by ICAO\n");
		printf("7. Search for airports near an airport\n");
	
		opened++;
		
		printf("\nWhich search would you like to use: ");
		scanf("%d", &option);
		
			switch (option) {
				case 1:	searchById();
				case 2: searchFunction("name");   	// As stated above, 1 function is used for all string searches,
				case 3: searchFunction("city");		// just with different arguments to differenciate them 
				case 4: searchFunction("country");
				case 5: searchFunction("IATA");
				case 6: searchFunction("ICAO");
				case 7: searchCoords();
	
				
			}
	}
	
	

	void main() {
		
		char file[] = "airportstext.txt";

		intakeData(file);
		
		searchMenu();
			
	}
	
