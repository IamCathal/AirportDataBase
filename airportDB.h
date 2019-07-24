int intakeData(char *fileName);
double degreesToRadians(double degrees);
double radiansToDegrees(double radians);
double coordDistance(double latitudeSearch, double longitudeSearch, double latitudeCurr, double longitudeCurr);
void searchFunction(char *searchType);
void searchCoords();
void searchMenu(); 
void searchById();

typedef struct airportStruct{
        int ID;
        char *name;
        char *city;
        char *country;
        char *IATA;
        char *ICAO;
        double latitude;
        double longitude;
        int altitude;
        int timezone;
        char *DST;
        char *olsenTimezone;
        char *type;
        char *source;
}airStruct;

typedef struct nearbyAirStruct{
    char *name;
    char *city;
    double distance;
}nearAirStruct;

#define PI 3.14159265358979324
