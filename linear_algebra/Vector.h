#pragma once
#include <vector>
#include <string>
#include <iostream>

class Vector {
public:
	Vector operator +(Vector vector) {
		std::vector<double> sumData;

		for (int index = 0; index < this->data.size(); index++) {
			sumData.push_back(this->data[index] + vector.data[index]);
		}

		return Vector(sumData);
	}

	Vector operator *(double scalar) {
		std::vector<double> scaledData;

		for (double element : this->data) {
			scaledData.push_back(element * scalar);
		}

		return Vector(scaledData);
	}

	Vector operator -(Vector vector) {
		return Vector(this->data) + (vector * -1);
	}

	double dot(Vector vector) {
		double sum = 0;

		for (int index = 0; index < this->data.size(); index++) {
			sum += this->data[index] * vector.data[index];
		}

		return sum;
	}

	

	double magnitude() {
		return sqrt(this->sqrMagnitude());
	}

	double sqrMagnitude() {
		return this->dot(Vector(this->data));
	}

	void display() {
		std::string ftext = "|";

		for (double element : this->data) {
			std::string text = std::to_string(element);
			if (text.find('.') != std::string::npos) {
				text = text.substr(0, text.find_last_not_of('0') + 1);
				if (text.find('.') == text.size() - 1) {
					text = text.substr(0, text.size() - 1);
				}
			}
			ftext = ftext + " " + text + "\t";
		}

		std::cout << ftext + " |" << std::endl;
	}

	Vector(std::vector<double> data) {
		this->data = data;
	}

	std::vector<double> data;
};