
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

void FileForest::AddFrequency (const fs::path file) {
	int init = 1;
	map<fs::path, unsigned int>::iterator freq =  listFreq.find(file);

	if (freq == listFreq.end()) {
		if (file.extension() == ".cpp") init = 0;
		listFreq.insert(pair<fs::path, unsigned int>(file, init));
	} else freq->second++;
}

void FileForest::PrintTree (vector<fs::path>& parent) {
	string dots;
	for (int i = 0; i < parent.size() - 1; ++i) {
		dots += "..";
	}

	map< fs::path, vector<fs::path> >::iterator found = listFiles.find(parent.back());
	if (found != listFiles.end()) {
		AddFrequency(parent.back());
		std::cout << dots << found->first.filename().string() << std::endl;

		vector<fs::path>::const_iterator it(found->second.begin());
		for (;it != found->second.end(); ++it) {
			vector<fs::path>::iterator cycle = find(parent.begin(), parent.end(), *it);
			if (cycle == parent.end()) {
				parent.push_back(*it);
				PrintTree(parent);
				parent.erase(parent.end() - 1);
			} else {
				std::cout << dots << ".." << it->filename().string() << " (c)" << std::endl;
			}
		}
	} else {
		AddFrequency(parent.back());
		std::cout << dots << parent.back().filename().string() << " (!)" << std::endl;
	}
}

void FileForest::Print () {
	listFreq.clear();

	vector<fs::path> tree;
	map< fs::path, vector<fs::path> >::const_iterator it(listFiles.begin());
	for (; it != listFiles.end(); ++it) {
		if (it->first.extension() == ".cpp") {
			tree.push_back(it->first);
			PrintTree(tree);
			tree.erase(tree.begin());
		}
	}

	std::cout << std::endl;
	map<fs::path, unsigned int>::const_iterator jt(listFreq.begin());
	for (; jt != listFreq.end(); ++jt) {
		std::cout << jt->first.filename().string() << '\t' << jt->second << std::endl;
	}
}

