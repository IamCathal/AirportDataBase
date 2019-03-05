#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
		struct airport *next;
};

struct airport airportArr[7543];

struct airport *first, *current, *last;   

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
		
		//printf("There are %d lines in the file\n", numLines);
		
			
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
						
			/*	printf("\n****************************************\nID: %d\nName: %s\nCity: %s\nCountry: %s\nIATA: %s\nICAO: %s\nLatitude: %lf\nLongitude: %lf\nAltitude: %d\nTiemzone: %d\nDST: %s\nO-Timezone: %s\nType: %s\nSource: %s\n",
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
						airportArr[i].source); */
						
			}
		
			fclose(fptr);
					
		} 
}


/*	int binaryData(char *fileName, int numLines) {
		
		FILE *fptr;
		int i;
		
		fptr = fopen("airportDBDAT.dat", "wb+");
			
				for (i = 0; i < numLines; i++) {
					fwrite(&airportArr[i], sizeof(struct airport), 1, fptr);
				}
				
				fclose(fptr);
				
				fptr = fopen("airportDBDAT.dat", "rb");
		
				first = current = last = NULL;
				i = 0;
				
				while (!feof(fptr)) {
					current = (struct airport*) malloc ( sizeof( struct airport ) );
					
					fread(current, sizeof( struct airport ), 1, fptr);
					i++;
					
					if (first == NULL) {
						first = last;
						current = last;
					}
					
					else {
						if ( i = (numLines - 1) )
						last->next = current;
						last = current;
						current->next = NULL;
					}
				}	
			
				//printf("\nCurrent name: %s", first->ID);
				printf("yuppa");
		
				
	}   */
	
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
						if (userInput == 0) {
							searchMenu();
						} 	else {
							printf("\nNo airport with ID \"%s\" found.\n", userInput);
						}
						
						
					}	
			} 			
		}
			
			
	
	void searchFunction(char *searchType) {
			int i, found = 0;
			char userInput[40] = "";
			
			printf("****************************************");
			
			while (userInput != "0") {
				if ( strcmp(searchType, "name") == 0) { printf("\n\nEnter an airport name (0 to exit):"); }
				else if (strcmp (searchType, "city")== 0) { printf("\n\nEnter a city (0 to exit):");}		
						scanf(" %[^\n]s", userInput);
				
				
				for (i = 0; i < numLines; i++) {
					if ( strcmpi(userInput, airportArr[i].city) == 0 ||  strcmpi(userInput, airportArr[i].name) == 0 ) {
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
							}
						}
			}
			
			if (strcmp(userInput, "0") == 0) {
				searchMenu();
			}
			
		
		}
	}

	
	
	int searchMenu() {
		
		int option;
		char nameString[] = "name";
		char cityString[] = "city";
		
		if (opened >= 1) {
			printf("\n****************************************\n");	
		}
		printf("1. Search by ID\n");
		printf("2. Search by name\n");    
		printf("3. Search by city\n");
	
		opened++;
		
		printf("\nWhich search would you like to use: ");
		scanf("%d", &option);
		
			switch (option) {
				case 1:	searchById();
				case 2: searchFunction(nameString);
				case 3: searchFunction(cityString);
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
	
	

