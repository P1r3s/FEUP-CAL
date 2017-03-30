#pragma once

class Position
{
	double lat;
	double lon;
public:
	Position() { lat = 0; lon = 0; };
	Position(double latitude, double longitude);
	double getLatRad();
	double getLonRad();
	double getLatDeg() {
		return lat;
	};
	double getLonDeg() {
		return lon;
	};
};

Position::Position(double latitude, double longitude)
{
	lat = latitude;
	lon = longitude;
}