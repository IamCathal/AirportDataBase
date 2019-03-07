# AirportDataBase
A program to parse and provide search functions for a database file on airports.

I am using a database file from [OpenFlights](https://openflights.org/data.html) that is a global database of over 10,000 airports worldwide. It has such information such as it's name, country, it's IATA identifying code, latitude and longitude and various timezone information. 

### Features to be implemented
* More robust inputs. Clean all invalid inputs from being used in searches.
* Search functions to search by each identifying piece of information for a particular airport.
* A searching system that suggests similar results to the input entered by the user and not only exact results which can often be hard to find.
* Implement a linked list system for practice.
* Possibly update the program to support other datafiles from OpenFlights. There is a similar file that has a database file of airports, train stations and ferry terminals.
* ~~Implement a function where a user can enter a set of coordinates and see if there is any other airports in a specific radius surrounding it.~~
* Implement a quick sort algorithm to rank the closest airports when the user is searching for them rather than having an undordered list.
