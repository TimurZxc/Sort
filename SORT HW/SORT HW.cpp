

#include <iostream>
#include <fstream>
#include "sorters.h"

bool generate_file(int N, const char* fname) {
	std::ofstream outFile(fname);
	if (!outFile) return false;
	while (N-- > 0)
		outFile << ' ' << rand() % 10000;
	outFile.close();
	return true;
}

bool isSortedFile(const char* fname) {
	std::ifstream infile(fname);
	int x, y;
	infile >> x;
	infile >> y;
	while (!infile.eof()) {
		if (x >= y) {
			infile >> x;
			infile >> y;
		}
		else {
			return false;
		}
	}
	return true;
}

void MergeFileSorting(const char* fname) {
	std::ifstream infile(fname);
	int a[1000];
	int b = 0;
	while (!infile.eof()) {
		
		infile >> a[b++];
		if (b == 1000) {
			MergeSortA<int>(a, 1000);
			std::ofstream outFile("Sort.txt");
			while (b-- > 0)
				outFile << ' ' << a[b];
			outFile.close();
			b = 0;
		}
		
	}
	

}


int main()
{
	char fname[] = "data.txt";
	if (!generate_file(100000, fname)) {
		std::cout << "Can not create file for test!" << std::endl;
		return 1;
	}

	MergeFileSorting(fname);

	if (isSortedFile("Sort.txt")) {
		std::cout << "File Sort.txt is sorted." << std::endl;
	}
	else {
		std::cout << "File Sort.txt is not sorted." << std::endl;
	}

	return 0;
}
