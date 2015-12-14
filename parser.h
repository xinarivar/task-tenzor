
#ifndef __INCLUDE_PARSER_H__
#define __INCLUDE_PARSER_H__

#include <fstream>
#include <string>
#include <vector>

/*------------------------------------------------------------------------------------------*/
//  Class IncludeParser: Find all include files in path.
/*------------------------------------------------------------------------------------------*/
class IncludeParser {
public:
	// Return vector of included pathes.
	static std::vector<std::string> Parse(const std::string path) {
		std::vector<std::string> retValue;
		std::ifstream file(path.c_str(), std::ifstream::in);
		
		if (!file.is_open()) {
			return retValue;
		}

		std::size_t posFound = 0;
		std::string fileLine;
		bool comment = false;

		while (file.good()) {
			std::getline(file, fileLine);

			// Find end of comment '*/' if comment '/*' was opened earlier.
			if (comment) {
				posFound = fileLine.find("*/");
				if (posFound != std::string::npos) {
					comment = false;
					fileLine = fileLine.substr(posFound + 2);
				} else continue;
			}

			// Cut substring begining at '//'
			posFound = fileLine.find("//");
			if (posFound != std::string::npos) {
				if (posFound != 0) {
					fileLine = fileLine.substr(0, posFound);
				} else continue;
			}

			// Cut substring begining at '/*' 
			// or ignore lines while not find end of comment '*/'
			posFound = fileLine.find("/*");
			if (posFound != std::string::npos) {
				std::size_t posEnd = fileLine.find("*/");
				if (posEnd != std::string::npos) {
					fileLine = fileLine.substr(0, posFound) + fileLine.substr(posEnd + 2, fileLine.length());
				} else {
					comment = true;
					fileLine = fileLine.substr(0, posFound);
				}
			}

			// Find directive '#include'
			// Add file path to returning vector
			posFound = fileLine.find("#include"); 
			if (posFound != std::string::npos) {
				fileLine = fileLine.substr(posFound + 8);

				std::size_t posFirst = fileLine.find_first_of("<\"");
				std::size_t posLast = fileLine.find_last_of(">\"");

				if (posFirst != posLast) {
					retValue.push_back(fileLine.substr(posFirst, posLast - posFirst + 1));
				}
			}
		}	// while eof file
		
		file.close();
		return retValue;
	}
};

#endif	// __INCLUDE_PARSER_H__
