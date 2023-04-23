QMAKE=qmake
ZIPNAME=1-xvanoj00-xhrklo00.zip
ZIPFILES=src/* Makefile README.txt $(DOX_CONFIG) $(DOC) examples/*
DOC=doc
DOX_CONFIG=Doxyfile


.PHONY=all target clean run pack doxygen

all: target

target:
	cd src; $(QMAKE) Project.pro
	$(MAKE) -C src --no-print-directory

clean:
	$(MAKE) distclean -C src --no-print-directory
	rm -df bin moc obj ui
	rm -rf $(DOC)/*
	rm -f $(ZIPNAME)


run: target
	./bin/app

pack:
	rm -f $(ZIPNAME)
	zip $(ZIPNAME) $(ZIPFILES)

doxygen:
	@mkdir -p $(DOC)
	doxygen $(DOX_CONFIG)
