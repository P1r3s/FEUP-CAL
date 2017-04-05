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
	double getDist(Position that) {
		return 100000*sqrt(pow((this->getLatDeg() - that.getLatDeg()), 2) + pow((this->getLonDeg() - that.getLonDeg()), 2));
		//return sqrt(pow(6371000 * sin((3.1415926 * this->getLatDeg() - that.getLatDeg()) / 180), 2) + pow(6371000 * sin((3.1415926 * this->getLatDeg() - that.getLatDeg()) / 180), 2));
	}
};

Position::Position(double latitude, double longitude)
{
	lat = latitude;
	lon = longitude;
}