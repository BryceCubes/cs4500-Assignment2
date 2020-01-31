ARRAYSPECREPO = https://github.com/angeliama98/CS4500-A1-Part2.git
ARRAYSPECHASH = 5be2a8b94b34132afe899bf8c98512933ad3ae44
QUEUESPECREPO = https://github.com/kylesferrazza/swdev-a1-p2.git
QUEUESPECHASH = 3168375d54aa7364309aaa8469128fcb7e6e8d21
MAPSPECREPO = https://github.com/az0977776/cs4500-a1p2-design.git
MAPSPECHASH = ff9ccbce51f8bdf182455580eb8cc2e585a64670

run: dircheck
	- make first
	- make second
	- make third

first:
	docker build -t cs4500:0.1 . 
	- rm -rf ./part1/test-array
	git clone $(ARRAYSPECREPO) ./part1/test-array
	cd ./part1/test-array; git checkout $(ARRAYSPECHASH)
	cd ./part1; cp array.h queue.h map.h string.h object.h Makefile boolean.h integer.h float.h test-array.cpp ./test-array 
#	TODO: cp anything else to compile and run e.g. googletests? my-tests.cpp edited-tests.cpp 
	- docker run -ti -v `pwd`:/test cs4500:0.1 bash -c "cd /test/part1/test-array ; make testArray"

second:
	docker build -t cs4500:0.1 . 
	- rm -rf ./part1/test-queue
	git clone $(QUEUESPECREPO) ./part1/test-queue
	cd ./part1/test-queue; git checkout $(QUEUESPECHASH)
	cd ./part1; cp array.h queue.h map.h string.h object.h Makefile ./test-queue 
#	TODO: cp anything else to compile and run e.g. googletests? my-tests.cpp edited-tests.cpp 
	- docker run -ti -v `pwd`:/test cs4500:0.1 bash -c "cd /test/part1/test-queue ; make testQueue"

third:
	docker build -t cs4500:0.1 . 
	- rm -rf ./part1/test-map
	git clone $(MAPSPECREPO) ./part1/test-map
	cd ./part1/test-map; git checkout $(MAPSPECHASH)
	cd ./part1; cp array.h queue.h map.h string.h object.h Makefile pair.h ./test-map
#	TODO: cp anything else to compile and run e.g. googletests? my-tests.cpp edited-tests.cpp 
	- docker run -ti -v `pwd`:/test cs4500:0.1 bash -c "cd /test/part1/test-map ; make testMap"

dircheck: ./part1 ./part1/array.h ./part1/queue.h ./part1/map.h ./part1/string.h ./part1/object.h ./part1/Makefile ./part1/MEMO.md ./part2 ./part2/REPO.md
	echo "Directory structure looks OK"
	- rm -rf dirtest-dir
	wc -l < ./part2/REPO.md | xargs test 2 -gt 
	echo "REPO.md file is 0 or 1 lines"
# B/c text files should always end w/a newline: stackoverflow.com/questions/729692/why-should-text-files-end-with-a-newline
	cat ./part2/REPO.md | xargs -n 1 -I{} git clone -q {} dirtest-dir
	echo "REPO.md file contains a valid git clone URL"
	rm -rf dirtest-dir
