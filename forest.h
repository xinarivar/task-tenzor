
#ifndef __FILE_FOREST_H__
#define __FILE_FOREST_H__

#include "parser.h"

#include <boost/filesystem.hpp>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = boost::filesystem;
using std::map;
using std::pair;
using std::vector;
using std::string;
using std::find;


/*------------------------------------------------------------------------------------------*/
//  Class FileForest: 
/*------------------------------------------------------------------------------------------*/
class FileForest {
public:
	bool AddIncludePath(const fs::path directory);
	void BuildTree(const fs::path file);
	void Print();

private:
	void PrintTree(vector<fs::path>& parent);
	void AddFrequency(const fs::path file);

private:
	vector<fs::path> pathInclude;
	map< fs::path, vector<fs::path> > listFiles;
	map<fs::path, unsigned int> listFreq;

};

#endif	// __FILE_FOREST_H__
