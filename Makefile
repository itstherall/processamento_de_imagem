
.PHONY: all, build, clean, folders


all: build

build: folders exe


clean:
	rm -rf objects
	rm -f exe


folders:
	mkdir -p objects

objects/abertura_e_copia.o: src/abertura_e_copia.c
	gcc src/abertura_e_copia.c -Iinclude -c -o objects/abertura_e_copia.o


objects/estruturasdef.o: src/estruturasdef.c
	gcc src/estruturasdef.c -Iinclude -c -o objects/estruturasdef.o

objects/filtros.o: src/filtros.c
	gcc src/filtros.c -Iinclude -c -o objects/filtros.o

objects/movimento_de_imagem.o: src/movimento_de_imagem.c
	gcc src/movimento_de_imagem.c -Iinclude -c -o objects/movimento_de_imagem.o

exe: src/main.c objects/abertura_e_copia.o objects/estruturasdef.o objects/filtros.o objects/movimento_de_imagem.o 
	gcc src/main.c objects/abertura_e_copia.o objects/estruturasdef.o objects/filtros.o objects/movimento_de_imagem.o -Iinclude -o exe
