CXXFLAGS = -g -Wall -std=c++17

all:		nums seq-test

nums:		seq.hh arrayseq.hh dlinkseq.hh command.cc nums.cc
	g++ $(CXXGLAGS) seq.hh arrayseq.hh dlinkseq.hh command.cc nums.cc -o nums
	
seq-test:	seq.hh arrayseq.hh dlinkseq.hh command.cc seq-test.cc
	g++ $(CXXGLAGS) seq.hh arrayseq.hh dlinkseq.hh command.cc seq-test.cc -o seq-test

CXX_FILES = $(wildcard *.cc)
TARGETS = $(CXX_FILES:%.cc=%)


#all:		$(TARGETS) .gitignore

.phony:		clean
clean:
		rm -f *.o *~ $(TARGETS)

.gitignore:	$(CXX_FILES)
		cat </dev/null >$@
		for t in $(TARGETS); do echo $$t >>$@; done
