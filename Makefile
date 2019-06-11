# -*- mode: makefile-gmake; coding: utf-8 -*-
DESTDIR ?= ~
SLICEDIR = $(shell python3 -c "import Ice; print(Ice.getSliceDir())")

all:


install:
	install -vd $(DESTDIR)$(SLICEDIR)/st
	install -m 644 slice/st.ice $(DESTDIR)$(SLICEDIR)/st
	install -vd $(DESTDIR)/usr/bin
	install -v -m 555 tools/st-client.py  $(DESTDIR)/usr/bin/st-client
