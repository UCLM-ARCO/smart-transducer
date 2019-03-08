
all:

package: clean
	mkdir src
	slice2c ../slice/st.ice
	mv st.h src/
	zip st-latest.zip library.json src/*
	cp st-latest.zip st-$$(cat ../.version).zip

.PHONY: clean
clean:
	$(RM) -r src/ *.zip


