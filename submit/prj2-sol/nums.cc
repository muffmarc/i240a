#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

#include "arrayseq.hh"
#include "dlinkseq.hh"

std::string usage(char* name) {
    return std::string("usage: ")
            + name + " [-a] INTS_FILE_PATH";
}

void readFile(const std::string& filename, Seq<int>* rsp) {
    Seq<int>& seq = *rsp;
    // read in filename into seq
    std::ifstream file(filename);
    if(!file){
    	std::cerr << "cannot read " << filename << ": " << std::strerror(ENOENT) << std::endl;
    	std::exit(ENOENT);
    }
    while(file){
    	int temp;
    	file >> temp;
    	seq.push(temp);
    }
}

int main(int argc, char* argv[]) {
    SeqPtr<int> sp;
    std::string filename;
    if (argc == 2) {
        filename = argv[1];
        sp = DLinkSeq<int>::make();
    } else if (argc == 3) {
        if (std::string(argv[1]) == "-x") {
            std::cout << usage(argv[0]) << std::endl;
            return 0;
        } else if (std::string(argv[1]) != "-a") {
            std::cerr << usage(argv[0]) << std::endl;
            return EINVAL;
        }
        filename = argv[2];
        sp = ArraySeq<int>::make();
    }

    if (argc != 2 && argc != 3) {
        std::cerr << usage(argv[0]) << std::endl;
        return EINVAL;
    }
    
    readFile(filename, sp.get());

    auto beginp = sp->cbegin();
    auto endp = sp->cend();

	auto& begin = *beginp;
	auto& end = *endp;
	--end;
	
	while (begin && end) {
		std::cout << *begin << std::endl;
		std::cout << *end << std::endl;
		++begin;
		--end;
	}
} 
