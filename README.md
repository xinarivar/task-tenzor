# Task "Tenzor"

1. Add file 'parser.h', and class 'IncludeParser' with static method 'Parse'. Class is intended to parse files and find list of files in compiler directive '#include'. Method 'Parse' takes argument string 'path' - path to the file to parse, and return vector of strings - list of included files in default quotes ("" or <>). Method 'Parse' ignore all comments.

2. Add file 'forest.h', 'forest.cpp'. 
	a) 'AddIncludePath' add path to vector 'pathInclude'.
	b) 'BuildTree' is intended to construct tree of all included files and subfiles in file 'const fs::path file'. Constructed tree saves in map 'listFiles'.
	c) 'Print' - print forest of all '*.cpp' file trees. Also count frequency included files and print.
	d) 'PrintTree' - support method, intended to show tree. 'vector<fs::path> parent' - needed to control cycled including files.
	e) 'AddFrequency' - support method, fill 'listFreq' with files and it included frequency.
