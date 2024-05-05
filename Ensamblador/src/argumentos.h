
struct __registro{
    unsigned char NUMERO:3, __unused:5;
};
typedef struct __registro *Registro;

#define TIPO_NUMERO 1
#define TIPO_REGISTRO 2
#define TIPO_ETIQUETA 3

struct __argumento {
    // tipo = 1 -> int*     (Numero constante)
    // tipo = 2 -> Registro (Registro 0-7)
    // tipo = 3 -> char*    (Etiqueta)
    unsigned char tipo;
    void* valor;
};
typedef struct __argumento *Argumento;

Argumento initArgumento(int tipo, void* valor);

Argumento* parsearArgumentos(char raw[]);

void freeArgumento(Argumento arg);

int tipoArgumento(Argumento arg);

void* valorArgumento(Argumento arg);

void printArgumento(Argumento arg);

void toStringArgumento(Argumento arg, char* rtn);

