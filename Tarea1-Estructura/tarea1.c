#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int validar_argumentos(int argc, char *modo, char *clave1, char *clave2, char *entrada, char *salida);
char reemplazar(char c, char *clave1, char *clave2, int largo);

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Error: Debes ingresar 5 argumentos.\n");
        return 1;
    }

    char *archivo_entrada = argv[1];
    char *modo = argv[2];
    char *clave1 = argv[3];
    char *clave2 = argv[4];
    char *archivo_salida = argv[5];

    if (!validar_argumentos(argc, modo, clave1, clave2, archivo_entrada, archivo_salida)) {
        return 1;
    }

    FILE *in = fopen(archivo_entrada, "r");
    FILE *out = fopen(archivo_salida, "w");

    if (in == NULL || out == NULL) {
        printf("Error al abrir archivos.\n");
        return 1;
    }

    char c;
    int largo = strlen(clave1);

    while ((c = fgetc(in)) != EOF) {
        c = reemplazar(c, clave1, clave2, largo);
        fputc(c, out);
    }

    fclose(in);
    fclose(out);

    if (strcmp(modo, "encode") == 0) {
        printf("Mensaje codificado correctamente.\n");
    } else {
        printf("Mensaje decodificado correctamente.\n");
    }

    return 0;
}

int validar_argumentos(int argc, char *modo, char *clave1, char *clave2, char *entrada, char *salida) {
    if (!(strcmp(modo, "encode") == 0 || strcmp(modo, "decode") == 0)) {
        printf("Error: Segundo argumento debe ser 'encode' o 'decode'.\n");
        return 0;
    }

    if (strlen(clave1) != strlen(clave2)) {
        printf("Error: Las claves deben tener el mismo largo.\n");
        return 0;
    }

    if (strcmp(entrada, salida) == 0) {
        printf("Error: Archivo de entrada y salida no pueden ser el mismo.\n");
        return 0;
    }

    // Verifica que las letras sean distintas dentro de cada clave y entre claves
    int i, j;
    for (i = 0; clave1[i] != '\0'; i++) {
        for (j = i + 1; clave1[j] != '\0'; j++) {
            if (clave1[i] == clave1[j]) {
                printf("Error: Clave 1 tiene caracteres repetidos.\n");
                return 0;
            }
        }
    }

    for (i = 0; clave2[i] != '\0'; i++) {
        for (j = i + 1; clave2[j] != '\0'; j++) {
            if (clave2[i] == clave2[j]) {
                printf("Error: Clave 2 tiene caracteres repetidos.\n");
                return 0;
            }
        }
    }

    for (i = 0; clave1[i] != '\0'; i++) {
        for (j = 0; clave2[j] != '\0'; j++) {
            if (clave1[i] == clave2[j]) {
                printf("Error: No debe haber caracteres repetidos entre claves.\n");
                return 0;
            }
        }
    }

    return 1;
}

char reemplazar(char c, char *clave1, char *clave2, int largo) {
    int i;
    char c_lower = tolower(c); 

    for (i = 0; i < largo; i++) {
        if (c_lower == tolower(clave1[i])) {
            char reemplazo = clave2[i];
            return isupper(c) ? toupper(reemplazo) : tolower(reemplazo);
        } else if (c_lower == tolower(clave2[i])) {
            char reemplazo = clave1[i];
            return isupper(c) ? toupper(reemplazo) : tolower(reemplazo);
        }
    }

    return c; 
}