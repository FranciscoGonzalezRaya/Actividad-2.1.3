#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_CARTAS 52
#define VALOR_CARTA 13
#define MAX_MANO 10

// Representación de las cartas
const char *valores[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const char *palos[] = {"Corazones", "Diamantes", "Picas", "Treboles"};

//Estructura para una carta
struct carta {
    char *valor;
    char *palo;
    int valorNumerico;
};

//Variables
struct carta baraja[TOTAL_CARTAS];
struct carta manoJugador[MAX_MANO];
int NCartasJugador = 0;
int sumJugador = 0;
char eleccion;


//Funcion: Mostrar Carta
void mostrarCarta(struct carta c) {
    printf("  %s de %s\n", c.valor, c.palo);
}

//Suma el valor de las cartas que tienes
int sumMano(struct carta mano[], int numCards) {
    int sum = 0;
    for (int i = 0; i < numCards; i++) {
        sum += mano[i].valorNumerico;
    }
    return sum;
}

int main() {
//Iniciamos la baraja
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        baraja[i].valor = valores[i % VALOR_CARTA];
        baraja[i].palo = palos[i / VALOR_CARTA];
        baraja[i].valorNumerico = (i % VALOR_CARTA) + 1;
        if (baraja[i].valorNumerico > 10) baraja[i].valorNumerico = 10;
        if (i % VALOR_CARTA == VALOR_CARTA - 1) baraja[i].valorNumerico = 11;
    }

//Barajar Baraja
    srand(time(NULL));
    for (int i = 0; i < TOTAL_CARTAS; i++) {
        int j = rand() % TOTAL_CARTAS;
        struct carta temp = baraja[i];
        baraja[i] = baraja[j];
        baraja[j] = temp;
    }

    printf("Bienvenido al Blackjack!\n");

//Asignamos la Carta al jugador
    manoJugador[NCartasJugador++] = baraja[0];
    manoJugador[NCartasJugador++] = baraja[1];
    sumJugador = sumMano(manoJugador, NCartasJugador);

//Muestra sus cartas al jugador
    printf("Tus cartas:\n");
    mostrarCarta(manoJugador[0]);
    mostrarCarta(manoJugador[1]);
    printf("Suma total: %d\n", sumJugador);

//Pregunta si quires cojer mas cartas
    while (sumJugador < 21) {
        printf("Quieres otra carta? (s/n): ");
        scanf(" %c", &eleccion);

        //Si dice que si la añade una carta
        if (eleccion == 's' || eleccion == 'S') {
            manoJugador[NCartasJugador] = baraja[NCartasJugador + 1];
            sumJugador = sumMano(manoJugador, ++NCartasJugador);

            printf("Nueva carta:\n");
            mostrarCarta(manoJugador[NCartasJugador - 1]);
            printf("Suma total: %d\n", sumJugador);
        } else {
            break;
        }
    }

//Resultados
    if (sumJugador == 21) {
        printf("¡Blackjack! Has ganado.\n");
    } else if (sumJugador > 21) {
        printf("Te has pasado. Fin del juego.\n");
    } else {
        printf("Te has plantado con %d. Fin del juego.\n", sumJugador);
    }

    return 0;
}
