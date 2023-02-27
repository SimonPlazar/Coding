MAKE_FILES := Makefile.client Makefile.server
TARGETS := all debug release clean

$(TARGETS): $(MAKE_FILES)
	for f in $^; do $(MAKE) $@ -f $$f; done
