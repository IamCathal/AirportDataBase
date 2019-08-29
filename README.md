# AirportDataBase
A program to parse and provide search functions for a global database file on airports. I am using the data from [OpenFlights](https://openflights.org/data.html) which has over 10,000 entries. Each entry has 14 data points that range from name and ICAO code to it's exact coordinates.

![](https://media.giphy.com/media/igbF5ZRCpiReptf7Io/giphy.gif)

### Features to be implemented
* More robust inputs. Clean all invalid inputs from being used in searches.
* A searching system that suggests similar results to the input entered by the user and not only exact results which can often be hard to find.
* Possibly update the program to support other datafiles from OpenFlights. There is a similar file that has a database file of airports, train stations and ferry terminals.
* A GUI to make the program look nice and organised.

### Implemented features
* Implement a function where a user can enter a set of coordinates and see if there is any other airports in a specific radius surrounding it.
* Dynamic allocation to allow to minimise wasted memory due to the huge variety of lengths of airport names.
* Implemented a sorting system to rank the closest airports when the user is searching for them rather than having an undordered list.
* Search functions to search by each identifying piece of information for a particular airport.
