#include <vector>
#include <iostream>

#include "Matrix.h"
#include "Vector.h"

void main() {
	/*std::vector<std::vector<double>> data2 = {
		{1, 3, 6, -55, 1, 22, 8},
		{-10, 3, 8, 24, 128, 529, 33},
		{6, 1, 3, 9, 6, 8, -3},
	};
	Matrix matrix2 = Matrix(data2);
	matrix2.display();
	std::cout << std::endl;
	(matrix2.transpose()).display();*/

	Vector vector = Vector({
		6, -4, 7
	});

	Vector vector2 = Vector({
		-3, -9, 8
	});

	Vector crossed = vector.cross(vector2);

	vector.display();
	vector2.display();

	std::cout << std::endl << "Crossed: ";

	crossed.display();

	std::cout << std::endl << "Crossed Vector Unit: ";

	(crossed.unit()).display();

	std::cin.get();
}