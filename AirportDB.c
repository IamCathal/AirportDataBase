#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airportDB.h"

airStruct *airportArr[7543]; 
nearAirStruct *nearbyAirportArr[350];
nearAirStruct *swap;

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
		char lineRaw[300]; 
		char latString[20], longString[20], timezoneString[3]; 
			
		while (!feof(fptr)) {
			ch = fgetc(fptr);
			if (ch == '\n') {
				numLines++;
			}
		}
	
	rewind(fptr);
	
	char *token;
	char delim[3] = ",\"";
	char noInfoString[3] = "na"; 
			
	for (i = 0 ; i < numLines; i++) {
			
		airportArr[i] = (airStruct *) malloc(sizeof(airStruct));	
				
		fgets(lineRaw, 250, fptr);
			
			token = strtok(lineRaw, delim);
				airportArr[i]->ID = atoi(token);
					
			token = strtok(NULL, delim);
				airportArr[i]->name = (char *) malloc(sizeof(char)*(strlen(token)+1));
				strcpy(airportArr[i]->name, token);
					
			token = strtok(NULL, delim);
				airportArr[i]->city = (char *) malloc(sizeof(char)*(strlen(token)+1));
				strcpy(airportArr[i]->city, token);
				
			token = strtok(NULL, delim);
				airportArr[i]->country = (char *) malloc(sizeof(char)*(strlen(token)+1));
				strcpy(airportArr[i]->country, token);
					
				/* If the string is "empty" (\N), it is replaced with the string  "na" */	
			token = strtok(NULL, delim);
				airportArr[i]->IATA = (char *) malloc(sizeof(char)*(strlen(token)+1));
					if (strcmp(token, "\\N") == 0) {
						strcpy(airportArr[i]->IATA, noInfoString); 
					} else {
						strcpy(airportArr[i]->IATA, token); 
					}
					
			token = strtok(NULL, delim);
				airportArr[i]->ICAO = (char *) malloc(sizeof(char)*(strlen(token)+1));
				strcpy(airportArr[i]->ICAO, token);
					
			token = strtok(NULL, delim);
				strcpy(latString, token);
				airportArr[i]->latitude = atof(latString);
					
			token = strtok(NULL, delim);
				strcpy(longString, token);
				airportArr[i]->longitude = atof(longString);
					
			token = strtok(NULL, delim);
				airportArr[i]->altitude = atof(token);
					
			token = strtok(NULL, delim);
				strcpy(timezoneString, token);
				airportArr[i]->timezone = atoi(timezoneString);	
					
			token = strtok(NULL, delim);
				airportArr[i]->DST = (char *) malloc(sizeof(char)*(strlen(token)+1));
					if (strcmp(token, "\\N") == 0) {
						strcpy(airportArr[i]->DST, noInfoString); 
					} else {
						strcpy(airportArr[i]->DST, token); 
					}
					
			token = strtok(NULL, delim);
				airportArr[i]->olsenTimezone = (char *) malloc(sizeof(char)*(strlen(token)+1));
					if (strcmp(token, "\\N") == 0) {
						strcpy(airportArr[i]->olsenTimezone, noInfoString); 
					} else {
						strcpy(airportArr[i]->olsenTimezone, token); 
					}

			token = strtok(NULL, delim);
				airportArr[i]->type = (char *) malloc(sizeof(char)*(strlen(token)+1));
					if (strcmp(token, "\\N") == 0) {
						strcpy(airportArr[i]->type, noInfoString); 
					} else {
						strcpy(airportArr[i]->type, token); 
					}
				
			token = strtok(NULL, delim);
				airportArr[i]->source = (char *) malloc(sizeof(char)*(strlen(token)+1));
					if (strcmp(token, "\\N") == 0) {
						strcpy(airportArr[i]->source, noInfoString); 
					} else {
						strcpy(airportArr[i]->source, token); 
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

        for (i = 0; i < numLines; i++) {
            if (airportArr[i]->ID == userInput) {
                printf(
                "\n****************************************\nID: %d\nName: "
                "%s\nCity: %s\nCountry: %s\nIATA: %s\nICAO: %s\nLatitude: "
                "%lf\nLongitude: %lf\nAltitude: %d\nTiemzone: %d\nDST: "
                "%s\nO-Timezone: %s\nType: %s\nSource: %s\n",
                airportArr[i]->ID, airportArr[i]->name, airportArr[i]->city,
                airportArr[i]->country, airportArr[i]->IATA,
                airportArr[i]->ICAO, airportArr[i]->latitude,
                airportArr[i]->longitude, airportArr[i]->altitude,
                airportArr[i]->timezone, airportArr[i]->DST,
                airportArr[i]->olsenTimezone, airportArr[i]->type,
                airportArr[i]->source);
                
                printf("\n****************************************");
                found = 1;
            }
        }

        if (i == numLines && found != 1) {
            /* If the search has gone atleast once and the input is 0 it goes
             * back to search menu */
            if (userInput == 0) {
                searchMenu();
            } else {
                /* If the search has gone atleast once and nothing was found it
                 * tells the user */
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
		
	latitudeSearch = degreesToRadians(latitudeSearch); 
	longitudeSearch = degreesToRadians(longitudeSearch); 
	latitudeCurr = degreesToRadians(latitudeCurr);   
	longitudeCurr = degreesToRadians(longitudeCurr);  
	
	long double longDist = longitudeCurr - longitudeSearch; 
	long double latDist = latitudeCurr - latitudeSearch;  
		
	long double distance = pow( sin(latDist / 2), 2 ) + cos( latitudeSearch) * cos( latitudeCurr) * pow( sin(longDist / 2), 2);
		
	distance = 2 * asin( sqrt(distance) );
		
	distance = distance * 6371;
	/* Returns the distance in KM */
	return(distance); 
}

	
void searchFunction(char *searchType) {
		
	int i, found = 0;
	char userInput[40] = "";
			
	printf("****************************************");
			
	/* To decrease redundant code, this function deals with searching for all string searches */
	while (strcmp(userInput, "0") != 0 ) {					
		printf("\n\nEnter %s (0 to exit):", searchType);
		scanf(" %[^\n]s", userInput); 
		
	if (strcmp(userInput, "0") == 0) {
		searchMenu();
	}
				
	int airportsFound= 0;
	for (i = 0; i < numLines; i++) {
		if ( strcmpi(userInput, airportArr[i]->city) == 0 ||  strcmpi(userInput, airportArr[i]->name) == 0 || 
			strcmpi(userInput, airportArr[i]->country) == 0 || strcmpi(userInput, airportArr[i]->IATA) == 0 ||
			strcmpi(userInput, airportArr[i]->ICAO) == 0 ) {
						
			airportsFound++;
						
			printf("\n****************************************\nID: %d\nName: %s\nCity: %s\nCountry: %s\nIATA: %s\nICAO: %s\nLatitude: %lf\nLongitude: %lf\nAltitude: %d\nTimezone: %d\nDST: %s\nO-Timezone: %s\nType: %s\nSource: %s\n",
			airportArr[i]->ID, 
			airportArr[i]->name,
			airportArr[i]->city,
			airportArr[i]->country, 
			airportArr[i]->IATA, 
			airportArr[i]->ICAO,
			airportArr[i]->latitude, 
			airportArr[i]->longitude, 
			airportArr[i]->altitude,
			airportArr[i]->timezone, 
			airportArr[i]->DST, 
			airportArr[i]->olsenTimezone,
			airportArr[i]->type, 
			airportArr[i]->source);
			printf("\n****************************************");
			found = 1;
			}	
	}  
				
	printf("\nThere were %d airports found", airportsFound); 		
	printf("\n****************************************");
			
	if ( i == numLines && found != 1) { 
		if (userInput == 0) {
			searchMenu();
			} else { 
			/* Prints the respected outputs if nothing of the searched for item is found */
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
	}
}


void searchCoords() {
	
	int i, k, found = 0, airportExists = 0;
	double userDistance;
	char userInput[80];
	double latitudeInput, longitudeInput; 
	double latitudeCurr, longitudeCurr;
			
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
			
	double seperation = 0; 
	
	for (i = 0; i < numLines; i++) {
		if (strcmpi(userInput, airportArr[i]->name) == 0) {
			latitudeInput = airportArr[i]->latitude;
				longitudeInput = airportArr[i]->longitude;
				airportExists++;
			}
	}
	
	if (airportExists == 0) {
		printf("\nAirport does not exist\n");
		searchMenu();
	}

		printf("\n");
				 	
	for( i = 0; i < numLines; i++) {
		latitudeCurr = airportArr[i]->latitude;
		longitudeCurr = airportArr[i]->longitude;
			 		
		seperation = coordDistance(latitudeInput, longitudeInput, latitudeCurr, longitudeCurr);		
		/* If seperation is within the range specified
		and not under 2km (itself), print it's info */
		if ( seperation < userDistance && seperation > 2) {
			 			
			nearbyAirportArr[found] = (nearAirStruct *) malloc(sizeof(nearAirStruct));
						
			nearbyAirportArr[found]->name = (char *)malloc(sizeof(char*)*(strlen(airportArr[i]->name)+1));
			strcpy(nearbyAirportArr[found]->name, airportArr[i]->name);
			nearbyAirportArr[found]->city = (char *)malloc(sizeof(char*)*(strlen(airportArr[i]->city)+1));
			strcpy(nearbyAirportArr[found]->city, airportArr[i]->city);
			nearbyAirportArr[found]->distance = seperation;
			found++;
		}					 
	}
				 
	/* Bubble sort, inneficient but it does the job*/
	for ( i = 0; i < found - 1; i++) {		
		for (k = 0; k < found - 1 - i; k++) {
			if (nearbyAirportArr[k]->distance > nearbyAirportArr[k + 1]->distance) {
				swap = nearbyAirportArr[k];
				nearbyAirportArr[k] = nearbyAirportArr[k+1];
				nearbyAirportArr[k+1] = swap;
			}
		}
	} 
			
	printf("\n****************************************\n");	
				
	/* Prints the results in a nice format */
	printf("\n");

	printf("%40s%17s     %s\n", "Airport", "City", "Distance");
	printf("%40s%17s     %s\n", "=======", "====", "========");
				 
	for (i = 0; i < found; i++) {
		printf("%40s%21s     %.0lfkm\n", nearbyAirportArr[i]->name, nearbyAirportArr[i]->city, nearbyAirportArr[i]->distance);
	}		
				 
	printf("\n%d airports found within a %.2lfkm radius", found, userDistance);
	printf("\n****************************************\n");	
		 		
	}
				/* If search is unsuccessful, inform the user */
		if ( i == numLines && found < 1) { 
			if (userInput == 0) {
				searchMenu();
			} else {
				printf("\nNo airports within %d km  found.\n", 100);
			}			
		}
					
		printf("\n****************************************\n");	
}
		
			
void searchMenu() {
		
	int option = 0;

	if (opened >= 1) {
		printf("\n****************************************\n");	
	}
	
	printf("\n%s\n%s\n%s\n%s",
	"    db    88 88\"\"Yb 88\"\"Yb  dP\"Yb  88\"\"Yb 888888 8888b.  88\"\"Yb",
  "   dPYb   88 88__dP 88__dP dP   Yb 88__dP   88    8I  Yb 88__dP", 
 "  dP__Yb  88 88\"Yb  88\"\"\"  Yb   dP 88\"Yb    88    8I  dY 88\"\"Yb",
" dP\"\"\"\"Yb 88 88  Yb 88      YbodP  88  Yb   88   8888Y\"  88oodP\n");

printf("\n**********************************************************************\n");	
	
	printf("1. Search by ID\n");
	printf("2. Search by name\n");    
	printf("3. Search by city\n");
	printf("4. Search by country\n");
	printf("5. Search by IATA\n");
	printf("6. Search by ICAO\n");
	printf("7. Search for airports near an airport\n");
	
	opened++;
		
	printf("\nWhich search function would you like to use: ");
	scanf("%d", &option);
	
		switch (option) {
			case 1:	searchById();
			case 2: searchFunction("a name");   	
			case 3: searchFunction("a city");	
			case 4: searchFunction("a country");
			case 5: searchFunction("an IATA");
			case 6: searchFunction("an ICAO");
			case 7: searchCoords();	
		}
}
	
	
void main() {
		
	char file[] = "airportstext.txt";
	intakeData(file);	
	searchMenu();
			
}
	

