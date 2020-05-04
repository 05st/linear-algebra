#include <vector>
#include <iostream>
#include <string>
#include <chrono>

using namespace std::chrono;

class Matrix {
public:
	std::vector<double> getRow(int index) {
		return this->data[index];
	}

	std::vector<double> getColumn(int index) {
		std::vector<double> column;

		for (std::vector<double> row : this->data) {
			column.push_back(row[index]);
		}

		return column;
	}

	Matrix operator +(Matrix matrix) {
		std::vector<std::vector<double>> sum;
		
		for (int rowIndex = 0; rowIndex < this->data.size(); rowIndex++) {
			std::vector<double> sumRow;
			std::vector<double> row = this->getRow(rowIndex);
			for (int elementIndex = 0; elementIndex < row.size(); elementIndex++) {
				sumRow.push_back(row[elementIndex] +matrix.getRow(rowIndex)[elementIndex]);
			}
			sum.push_back(sumRow);
		}

		return Matrix(sum);
	}

	Matrix operator *(double scalar) {
		std::vector<std::vector<double>> scaled;

		for (int rowIndex = 0; rowIndex < this->data.size(); rowIndex++) {
			std::vector<double> scaledRow;
			std::vector<double> row = this->getRow(rowIndex);
			for (int elementIndex = 0; elementIndex < row.size(); elementIndex++) {
				scaledRow.push_back(row[elementIndex] * scalar);
			}
			scaled.push_back(scaledRow);
		}

		return Matrix(scaled);
	}

	Matrix operator *(Matrix matrix) {
		std::vector<std::vector<double>> product;

		int columnsInSecondMatrix = matrix.getRow(0).size();

		for (int rowIndex = 0; rowIndex < this->data.size(); rowIndex++) {
			std::vector<double> productRow;

			for (int columnIndex = 0; columnIndex < columnsInSecondMatrix; columnIndex++) {
				std::vector<double> row = this->getRow(rowIndex);
				std::vector<double> column = matrix.getColumn(columnIndex);

				double dotProduct = 0;
				for (int elementIndex = 0; elementIndex < row.size(); elementIndex++) {
					dotProduct += row[elementIndex] * column[elementIndex];
				}

				productRow.push_back(dotProduct);
			}

			product.push_back(productRow);
		}

		return Matrix(product);
	}

	Matrix operator -(Matrix matrix) {
		return Matrix(this->data) + (matrix * -1);
	}

	bool isSquare() {
		int columns = this->getRow(0).size();
		if (columns == this->data.size()) {
			return true;
		}
		return false;
	}

	double determinant() {
		if (this->isSquare()) {
			int size = this->data.size();

			if (size == 1) {
				return this->getRow(0)[0];
			}
			else if (size >= 2) {
				return determinantRecursive(Matrix(this->data));
			}
		}

		return -1; // could not compute determinant or matrix is not a square
	}

	void display() {
		for (std::vector<double> row : this->data) {
			std::string ftext = "|";
			for (double element : row) {
				std::string text = std::to_string(element);
				if (text.find('.') != std::string::npos) {
					text = text.substr(0, text.find_last_not_of('0') + 1);
					if (text.find('.') == text.size() - 1) {
						text = text.substr(0, text.size() - 1);
					}
				}
				ftext = ftext + " "  + text + "\t";
			}

			
			std::cout << ftext + " |" << std::endl;
		}
	}

	Matrix(std::vector<std::vector<double>> data) {
		this->data = data;
	}
private:
	std::vector<std::vector<double>> data;

	double determinantRecursive(Matrix matrix) {
		if (matrix.isSquare()) {
			int size = matrix.data.size();
			if (size == 2) {
				std::vector<double> firstRow = matrix.getRow(0);
				std::vector<double> secondRow = matrix.getRow(1);

				return firstRow[0] * secondRow[1] - firstRow[1] * secondRow[0];
			}
			else if (size >= 3) {
				double sum = 0;
				for (int columnIndex = 0; columnIndex < matrix.getRow(0).size(); columnIndex++) {
					std::vector<std::vector<double>> excludedMatrixData;
					for (int rowIndex = 1; rowIndex < matrix.data.size(); rowIndex++) { // exclude first row
						std::vector<double> row = matrix.getRow(rowIndex);
						row.erase(row.begin() + columnIndex);
						excludedMatrixData.push_back(row);
					}

					double mult = 0;
					double det = determinantRecursive(Matrix(excludedMatrixData));
					if (columnIndex % 2 == 0) {
						mult = 1;
					}
					else {
						mult = -1;
					}

					sum += det * (mult * matrix.getColumn(columnIndex)[0]);
				}
				return sum;
			}
		}
	}
};

void main() {
	/*std::vector<std::vector<double>> data = { {1, 1, 0, 0, 0, 0}, { 2,2,2,0,0,0 }, { 0,3,3,3,0,0 }, { 0,0,4,4,4,0 }, { 0,0,0,5,5,5 }, { 0,0,0,0,6,6 } };

	Matrix matrix = Matrix(data);
	matrix.display();
	std::cout << matrix.determinant() << std::endl << std::endl;*/

	auto start = high_resolution_clock::now();
	std::vector<std::vector<double>> data2 = {
		{1, 3, 6, -55, 1, 22, 8},
		{-10, 3, 8, 24, 128, 529, 33},
		{6, 1, 3, 9, 6, 8, -3},
		{-3, -76, -2, 6, 1, 5, 2},
		{-51, 12, 3, 7, 3, 1, 7},
		{8, 4, 7, 3, 1, 6, -4},
		{1, 3, -2, -6, 23, 6, 1}
	};
	Matrix matrix2 = Matrix(data2);
	matrix2.display();
	std::cout << matrix2.determinant();
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << std::endl << (duration.count() / 1e+6);


	/*std::vector<std::vector<double>> data = {
		{1,0,0,0,0,0,0,0,0,0,0,0,},
		{0,1,0,0,0,0,0,0,0,0,0,0,},
		{0,0,1,0,0,0,0,0,0,0,0,0,},
		{0,0,0,1,0,0,0,0,0,0,0,0,},
		{0,0,0,0,1,0,0,0,0,0,0,0,},
		{0,0,0,0,0,1,0,0,0,0,0,0,},
		{0,0,0,0,0,0,1,0,0,0,0,0,},
		{0,0,0,0,0,0,0,1,0,0,0,0,},
		{0,0,0,0,0,0,0,0,1,0,0,0,},
		{0,0,0,0,0,0,0,0,0,1,0,0,},
		{0,0,0,0,0,0,0,0,0,0,1,0,},
		{0,0,0,0,0,0,0,0,0,0,0,1,},
	};

	Matrix matrix = Matrix(data);
	matrix.display();
	std::cout << matrix.determinant() << std::endl << std::endl;*/

	std::cin.get();
}