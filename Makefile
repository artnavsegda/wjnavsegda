TARGET=prototype

all:
	gcc -o ${TARGET} ${TARGET}.c -lwjelement -lwjreader

clean:
	rm ${TARGET}
