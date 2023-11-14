build:
	# compile test.c link to libtermswipe.so
	gcc -o test test.c -L.. -ltermswipe -I..
	LD_LIBRARY_PATH=$(LD_LIBRARY_PATH):.. ./test

build_lib:
	cd ../src; make