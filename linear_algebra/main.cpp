#include <vector>
#include <iostream>
#include <string>

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

	double determinant() {

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
};

void main() {
	std::vector<std::vector<double>> data = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
		{10, 11, 12}
	};

	std::vector<std::vector<double>> data2 = {
		{1, 2, 3, 4},
		{5, 6, 7, 8},
		{9, 10, 11, 12}
	};

	Matrix matrix = Matrix(data);
	Matrix matrix2 = Matrix(data2);

	matrix.display();
	std::cout << "*" << std::endl;
	matrix2.display();
	std::cout << "=" << std::endl;

	Matrix productMatrix = matrix * matrix2;
	productMatrix.display();

	std::cin.get();
}