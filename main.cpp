
#include <iostream>
#include "analyser.h"


int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Usage: analyser <directory> [options]\n";
		std::cout << "Options:\n";
		std::cout << "\t-I <directory>\n";
		return -1;
	}

	FileForest forest;
	fs::path dir(argv[1]);

	for (int i = 2; i < argc; ++i) {
		if (strcmp(argv[i], "-I") == 0 && i < argc) {
			fs::path tmp(argv[++i]);
			forest.AddIncludePath(tmp);
		}
	}

	Analyser::Analyze(forest, dir);
	forest.Print();

	return 0;
}
