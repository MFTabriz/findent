if BUILD_JFINDENT
JAR   = jar
CHMOD = chmod
CP    = cp
jfindent jfindent.jar:  Jfindent.java
	$(JAVAC)        Jfindent.java
	$(JAR)   cfe $@ Jfindent Jfindent*.class
	$(CHMOD) +x  $@
	$(CP)        $@ jfindent.jar
bin_SCRIPTS = jfindent jfindent.jar
else
all:
endif
CLEANFILES  = jfindent jfindent.jar *.class
