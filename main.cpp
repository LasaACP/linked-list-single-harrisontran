//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

// TODO make the functions in slist ---- DONE
// TODO make that code efficient    ---- DONE, I think
// TODO sort the linked list by distance from Austin
// TODO output the furthest airport's lon and lat
// TODO make a sublist of airports within 100km of Austin

#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include "slist.h"
#define austin_lat 30.1944 // Austin's latitude
#define austin_lon 97.67 // Austin's absolute longitude west of the prime meridian

using namespace std;

class Airport {
public:
	char code[5];
	double longitude;
	double latitude;
};

void simpleSortTotal(LinkedList l);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
	ifstream infile;
	int i = 0;
	char cNum[10];
	Airport* airportArr[13500];

	infile.open("./USAirportCodes.csv", ifstream::in);
	if (infile.is_open()) {
		int c = 0;
		while (infile.good()) {
			airportArr[c] = new Airport();
			infile.getline(airportArr[c]->code, 256, ',');
			infile.getline(cNum, 256, ',');
			airportArr[c]->latitude = atof(cNum);
			infile.getline(cNum, 256, '\n');
			airportArr[c]->longitude = atof(cNum);
			i++;
			c++;
		}
		infile.close();
	} else {
		cout << "Error opening file";
	}
	// Initialize Linked List
	LinkedList airports;
	for(int i = 1; i < 13430; i++) {
		airports.add(airportArr[i]->code,airportArr[i]->latitude,airportArr[i]->longitude);
	}
	// Sort the list by distance
	simpleSortTotal(airports);
	cout << "Size of linked list: " << airports.size();
	// Find the first entry whose distance exceeds 100km
	int hundred_threshold = 0;
	for(int i = 0; i < airports.size(); i++) {
		int distance = distanceEarth(austin_lat, austin_lon, airports.get(i).lat, airports.get(i).lon);
		if(distance >= 100) {
			hundred_threshold = i;
			break;
		}
	}
	// Fetch a list of airports within 100 km
	LinkedList airportsWithinHundredKM = airports.subList(0,hundred_threshold);
	cout << airportsWithinHundredKM.toString();
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm * asin(sqrt((u * u) + (cos(lat1r) * cos(lat2r)) * (v * v)));
}

/**
 * Uses a bubble sort!
 */
void simpleSortTotal(LinkedList l) {
	int index_counter = 0;
	int selection_counter;
	for (node *index = l.head; index->next != nullptr; index = index->next) {
		selection_counter = index_counter;
		for (node *selection = index->next; selection != nullptr; selection =
				selection->next) {
			if (distanceEarth(austin_lat, austin_lon, index->lat, index->lon)
					> distanceEarth(austin_lat, austin_lon, selection->lat,
							selection->lon)) {
				l.exchg(index_counter,selection_counter);
			}
			selection_counter++;
	  }
		index_counter++;
	}
}
