ACLOCAL_AMFLAGS = -I m4 --install
AM_CFLAGS = -Wall

DISTCLEANFILES = *~

build_script :
	sh ./build.sh

clean-local:
	rm -f cReddit
	-rm -rf *.dSYM || rmdir *.dSYM

distclean-local:
	-rm -rf autom4te.cache || rmdir autom4te.cache
