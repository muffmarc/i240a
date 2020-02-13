#include <iostream>
#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <vector>
#include <set>

typedef std::set<std::string> FileNames;

std::map<int, FileNames> 
readNums(std::vector<std::string> fileNames)
{
  std::map<int, FileNames> map; //empty collection
  for (auto fileName : fileNames) { //let compiler figure out fileName is string
    std::ifstream in(fileName); //open file
    if (!in) {
      std::cerr << "cannot read \"" << fileName << "\"" << std::endl;
      std::exit(1);
    }
    int i;
    while (in >>i) {
      map[i].insert(fileName);
    }
    if (!in.eof()) {
      std::cerr << "i/o error on file \"" << fileName << "\"" << std::endl;
      std::exit(1);
    }
  } //for
  return map;
}

static std::ostream&
operator<<(std::ostream& out, const std::set<std::string>& set)
{
  for (auto element : set) { out << element << " "; }
  return out;
}

static void
interact(const std::map<int, FileNames>& map)
{
  std::string i;
  std::cout << ">> ";
  while (std::cin >> i) {
    try {
      std::ifstream in(i);
	  if (!in){
	    std::cerr << "cannot read \"" << i << "\"" << std::endl;
	  }
	  else{
		int sum = 0;
		int num;
		while (in >> num){
			sum+=num;
		}
	    std::cout<< i << ": " << sum << std::endl;
	  } 
    }
    catch (std::out_of_range& err) {
      std::cout << i << ": " << "NOT FOUND" << std::endl;
    }
    std::cout << ">> ";
  } //while
}

int
main(int argc, char* argv[])
{
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " FILE..." << std::endl;
    std::exit(1);
  }
  auto map = readNums(std::vector<std::string>(&argv[1], &argv[argc]));
  interact(map);
}

