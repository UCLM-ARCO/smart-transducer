# -*- mode: makefile-gmake; coding: utf-8 -*-
DESTDIR ?= ~

all:

install:
	install -vd $(DESTDIR)/usr/share/slice/st
	install -m 644 slice/st.ice $(DESTDIR)/usr/share/slice/st
	install -vd $(DESTDIR)/usr/bin
	install -v -m 555 tools/st-client.py  $(DESTDIR)/usr/bin/st-client
