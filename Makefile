CXX = gcc
CXXFLAGS = -Wall

OBJS = LinkedList.o LexicalAnalyzer.o RDParser.o main.o

app : ${OBJS}
	${CXX} $(CXXFLAGS) -o $@ ${OBJS}

main.o : main.c RDParser.h
LinkedList.o: LinkedList.c LinkedList.h
LexicalAnalyzer.o: LexicalAnalyzer.c LexicalAnalyzer.h LinkedList.h
RDParser.o: RDParser.c RDParser.h LexicalAnalyzer.h

clean :
	rm ${OBJS} app