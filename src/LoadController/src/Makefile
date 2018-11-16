# -*- mode: makefile; coding: utf-8 -*-

SLICE2C_FLAGS = -I $(shell pwd)/../../../slice \
                -I ../.piolibdeps/IceC\ IoT\ node_ID1935/slice
SLICE = lifelike.ice

all: $(SLICE:%.ice=%.h)

%.h: %.ice
	slice2c $(SLICE2C_FLAGS) $^

.PHONY: clean
clean:
	$(RM) $(SLICE:%.ice=%.h)

