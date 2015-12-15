
#ifndef __FILE_FOREST_H__
#define __FILE_FOREST_H__

#include "parser.h"

#include <boost/filesystem.hpp>
#include <map>
#include <vector>
#include <string>

namespace fs = boost::filesystem;
using std::map;
using std::pair;
using std::vector;
using std::string;


/*------------------------------------------------------------------------------------------*/
//  Class FileForest: 
/*------------------------------------------------------------------------------------------*/
class FileForest {
public:
	bool AddIncludePath(const fs::path directory);
	void BuildTree(const fs::path file);
	void PrintTree() const;

private:
	vector<fs::path> pathInclude;
	map< fs::path, vector<fs::path> > listFiles;

};

#endif	// __FILE_FOREST_H__
