CC=g++
DEFINE=#-DMAP
CFLAGS=-Wall -std=c++11
FileName=analog
OFILE= ApplicationAnalog.o Couple.o IndexString.o InsertFluxApache.o LigneRequete.o StatistiquesApache.o
MAINFILE=ApplicationAnalog


$(FileName): $(OFILE)
	$(CC) -o $(FileName) $(CFLAGS) $(DEFINE) $^
	mv $(FileName) ../bin/

$(MAINFILE).o : $(MAINFILE).cpp
	$(CC) -c $(CFLAGS) $(DEFINE) $(MAINFILE).cpp

%.o :  %.h %.cpp
	$(CC) -c $(CFLAGS) $(DEFINE) $*.cpp 

.PHONY : clean
clean :
	rm -f $(OFILE) core
.PHONY : test
test :
	make -C ../Tests/ mktest
