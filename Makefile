CC = cl
CFLAGS = /W3 /O2 /D_CRT_SECURE_NO_DEPRECATE

build: tema1.exe

tema1.exe: Main.obj Util.obj List.obj HashTable.obj
	$(CC) $(CFLAGS) $** /Fe$@

Main.obj: main.c
Util.obj: Util.h Util.c
List.obj: List.h List.c
HashTable.obj: Header.h HashTable.c

clean:
	del *.obj
	del *.exe
