.bin/encodeInput: ./obj/encodeInput.o ./obj/SREC.o ./obj/ASM.o
	cc ./obj/encodeInput.o ./obj/SREC.o ./obj/ASM.o -o ./bin/encodeInput
./obj/encodeInput.o: ./src/encodeInput.c ./inc/encodeInput.h
	cc -c ./src/encodeInput.c -o ./obj/encodeInput.o
./obj/SREC.o: ./src/SREC.c ./inc/SREC.h
	cc -c ./src/SREC.c -o ./obj/SREC.o
./obj/ASM.o: ./src/ASM.c ./inc/ASM.h
	cc -c ./src/ASM.c -o ./obj/ASM.o

all:./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o

