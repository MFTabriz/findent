AUTOMAKE_OPTIONS = gnu

SUBDIRS = src scripts test vim gedit emacs doc deps

MAINTAINERCLEANFILES = config.h.in~

EXTRA_DIST = bootstrap getversion LICENCE README.1st README.windows  \
	     maketar makezip makedeb makesid README.2nd debian \
	     makeupload pbuilderscript \
	     debian.disco debian.wheezy debian.sid debian.stretch \
	     simplemake.sh

maintainer-clean-local:
	rm -rf bin share autom4te.cache

if MAKEWIN
all-local:
	test -f src/findent && mv src/findent src/findent.exe ; exit 0
endif

builtparser builtlexer:
	cd src; $(MAKE) $@
