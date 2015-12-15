
#ifndef __ANALYSER_H__
#define __ANALYSER_H__

#include "forest.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Analyser {
public:
	static void Analyze(FileForest& forest, fs::path directory) {
		fs::directory_iterator it(directory), end;

		for (; it != end; ++it) {
			if (is_regular_file(it->path())) {
				if (it->path().has_extension() && it->path().extension() == ".cpp") {
					std::cout << it->path().string() << std::endl;
					forest.BuildTree(it->path());
				}
			} else if (is_directory(it->path())) {
				Analyze(forest, it->path());
			}
		}
	}
};

#endif	// __ANALYSER_H__
