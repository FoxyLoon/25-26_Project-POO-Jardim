#include "Solo.h"
#include "../plantas/Planta.h"
#include "../ferramentas/Ferramenta.h"

char Solo::getSimboloVisivel() const {
    // Prioridade de visualização: Planta > Ferramenta > vazio
    // (Jardineiro é tratado externamente na função mostrarComJardineiro)

    if (temPlanta()) {
        return planta->simbolo();
    }

    if (temFerramenta()) {
        return ferramenta->simbolo();
    }

    // Posição vazia
    return ' ';
}