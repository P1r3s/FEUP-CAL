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
	bool operator==(Position that) {
		return this->getLatDeg() == that.getLatDeg() && this->getLonDeg() == that.getLonDeg();
	}
	bool operator!=(Position that) {
		return this->getLatDeg() != that.getLatDeg() || this->getLonDeg() != that.getLonDeg();
	}
};

Position::Position(double latitude, double longitude)
{
	lat = latitude;
	lon = longitude;
}