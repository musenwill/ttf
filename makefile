
obj= main.o ttf.o

calc24:$(obj)
	gcc $(obj) -o calc24

main.o:Type.h ttf.h
ttf.o:Type.h ttf.h

.PHONY:clean
clean:
	-rm -f *.o
	

