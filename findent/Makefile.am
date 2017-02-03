AUTOMAKE_OPTIONS = gnu
SUBDIRS = src scripts test
MAINTAINERCLEANFILES = config.h.in~
maintainer-clean-local:
	rm -rf bin share autom4te.cache
# make distcheck complains about bison-related files
# (not flex-related files), so disable distcleancheck:
distcleancheck:
	@:
