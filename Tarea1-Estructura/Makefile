# Compilador
CC = gcc

# Flags de compilación (puedes dejarlo vacío)
CFLAGS =

# Nombre del ejecutable
TARGET = tarea1.exe

# Archivo fuente
SRC = tarea1.c

# Regla por defecto
all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	del $(TARGET)
