#include <iostream>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <assert.h>
#include <unordered_map>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

typedef unsigned int Count;

bool wordCountCompare(const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
	if(a.second == b.second){
		return a.first<b.first;
	}
	return (a.second > b.second);
}

int main(int argc, char* argv[]) {

	if (argc < 5){
		std::cerr << "usage: " << argv[0] << " MAX_N_OUT" << " MIN_WORD_LEN" << " MAX_WORD_LEN" << " FILE..." << std::endl;
		std::exit(1);
	}
	
	auto args = std::vector<std::string>(&argv[0], &argv[argc]);
	std::size_t endIndex;
	
	const char* names[] = {"MAX_N_OUT", "MIN_WORD_LEN", "MAX_WORD_LEN"};
	std::size_t data[3];
	std::size_t &max_out(data[0]), &min_len(data[1]), &max_len(data[2]);
	int parsing = 0;
	try {
	    for (; parsing < 3; parsing++) {
			data[parsing] = std::stoi(args[parsing + 1], &endIndex);
			if (endIndex != args[parsing + 1].length()) {
			    throw std::runtime_error(std::string("bad integer value ") + argv[parsing + 1] + " for " + names[parsing]);
			}
		}
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EINVAL;
	}

	if (max_len < min_len) {
		std::cerr << "MIN_WORD_LEN " << min_len << " is greater than MAX_WORD_LEN " << max_len << std::endl;
		return EINVAL;
	}
	
	//std::map<std::string, int> mapped = countnums(std::vector<std::string>(&argv[4], &argv[argc], min_len, max_len);
	std::unordered_map<std::string, Count> map;
	std::ifstream in(argv[4]);

    if (!in.good()) {
        std::cerr << "cannot read " << argv[4] << ':' << std::endl;
        std::cerr << '\t' << std::strerror(ENOENT) << std::endl; 
        return ENOENT;
    }
	
    while (in.good()) {
		std::string  word;
		in >> word;
		std::string altWord;
		for (char c : word) {
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
				altWord += std::tolower(c);
			}
		}

		if (altWord.length() >= min_len && altWord.length() <= max_len) {
			map[altWord] += 1;
		}
    }

    if (!in.eof()) {
        std::cerr << std::strerror(EIO) << ' ' << argv[4] << std::endl;
        return EIO;
    }
    
    typedef std::pair<std::string, Count> WordCount;
    
    auto wordCounts = std::vector<WordCount>(map.begin(), map.end());
	sort(wordCounts.begin(), wordCounts.end(), wordCountCompare);
	
	for (std::size_t i = 0; i < std::min(max_out, wordCounts.size()); i++) {
		std::cout<< wordCounts[i].first << ": " << wordCounts[i].second << std::endl;
	}	
}
