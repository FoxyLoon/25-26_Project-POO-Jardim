#include "Regador.h"

Regador::Regador(int id): Ferramenta(id) {}
Regador::~Regador() {}
char Regador::simbolo() const { return 'g'; }
