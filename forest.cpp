
#include "forest.h"

bool FileForest::AddIncludePath (const fs::path directory) {
	if (exists(directory) && is_directory(directory)) {
		pathInclude.push_back(directory);

		return true;
	}

	return false;
}

void FileForest::BuildTree (const fs::path file) {
	if (exists(file) && is_regular_file(file)) {
		map< fs::path, vector<fs::path> >::iterator found = listFiles.find(file);
		if (found != listFiles.end()) return;

		vector<string> filesInclude = IncludeParser::Parse(file.string());

		fs::path tmp;
		vector<fs::path> listTmp;

		for (vector<string>::iterator it(filesInclude.begin()); it != filesInclude.end(); ++it) {
			if (it->at(0) == '\"') {
				tmp = file.parent_path() / it->substr(1, it->length() - 2);
				if (exists(tmp) && is_regular_file(tmp)) {
					listTmp.push_back(tmp);
				}
			} else if (it->at(0) == '<') {
				bool deleted = true;
				
				for (vector<fs::path>::iterator jt(pathInclude.begin()); jt != pathInclude.end(); ++jt) {
					tmp = *jt / it->substr(1, it->length() - 2);
					if (exists(tmp) && is_regular_file(tmp)) {
						listTmp.push_back(tmp);
						deleted = false;
						break;
					}
				}	// for jt

				if (deleted == true) {
					tmp = it->substr(1, it->length() - 2);
					listTmp.push_back(tmp);
				}
			}
		}	// for it

		listFiles.insert( pair< fs::path, vector<fs::path> >(file, listTmp) );
		
		for (vector<fs::path>::iterator it(listTmp.begin()); it != listTmp.end(); ++it) {
			BuildTree(*it);
		}
	}
}

void FileForest::PrintTree () const {
	map< fs::path, vector<fs::path> >::const_iterator it(listFiles.begin());
	for (; it != listFiles.end(); ++it) {
		std::cout << it->first.filename().string() << std::endl;

		vector<fs::path>::const_iterator jt(it->second.begin());
		for (; jt != it->second.end(); ++jt) {
			std::cout << ".." << jt->filename().string() << std::endl;
		}
	}
}
