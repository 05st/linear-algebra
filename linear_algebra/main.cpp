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
		1, 2, 3, 4
	});

	vector.display();

	std::cin.get();
}