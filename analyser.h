
#ifndef __ANALYSER_H__
#define __ANALYSER_H__

#include "forest.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

class Analyser {
public:
	// Recursively browse directory and build inlcuded files tree for all '.cpp' files.
	static void Analyze(FileForest& forest, fs::path directory) {
		fs::directory_iterator it(directory), end;

		for (; it != end; ++it) {
			if (is_regular_file(it->path())) {
				if (it->path().has_extension() && it->path().extension() == ".cpp") {
					forest.BuildTree(it->path());
				}
			} else if (is_directory(it->path())) {
				// Browse subdirectory
				Analyze(forest, it->path());
			}
		}
	}
};

#endif	// __ANALYSER_H__
