JAR   = jar
CHMOD = chmod
CP    = cp
jfindent.jar:           Jfindent.java
	$(JAVAC)        Jfindent.java
	$(JAR)   cfe $@ Jfindent Jfindent*.class
	$(CHMOD) +x  $@

bin_SCRIPTS = jfindent

jfindentdir = $(datadir)/jfindent/lib

jfindent_DATA = jfindent.jar

man1_MANS = jfindent.1

jfindent:
	echo "#/bin/sh" > $@
	echo "$(JAVA) -jar $(jfindentdir)/jfindent.jar" >> $@

install-data-hook:
	gzip -f $(DESTDIR)$(mandir)/man1/$(man1_MANS)

CLEANFILES  = jfindent jfindent.jar *.class
