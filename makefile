run.exe: main.o medicalRecord.o
	gcc main.o medicalRecord.o -o run.exe

main.o: main.c medicalRecord.h
	gcc -Wall -c main.c

medicalRecord.o: medicalRecord.c medicalRecord.h
	gcc -Wall -c medicalRecord.c

clean:
	rm *.o run.exe
