#include "FerramentaZ.h"
#include <sstream>

FerramentaZ::FerramentaZ() : Ferramenta(), cargasBateria(CAPACIDADE_BATERIA) {}

FerramentaZ::~FerramentaZ() {}

char FerramentaZ::simbolo() const {
    return 'z';
}

std::string FerramentaZ::nome() const {
    return "Harmonizador de Solo";
}

bool FerramentaZ::aplicar(Solo &solo) {
    if (!estaUtilizavel()) {
        return false;
    }
    
    // Ajusta água para o valor ótimo
    int diferencaAgua = AGUA_OTIMA - solo.agua;
    if (diferencaAgua > 0) {
        // Precisa adicionar água (até 15 unidades)
        int adicionar = (diferencaAgua > 15) ? 15 : diferencaAgua;
        solo.agua += adicionar;
    } else if (diferencaAgua < 0) {
        // Precisa remover água (até 15 unidades)
        int remover = (-diferencaAgua > 15) ? 15 : -diferencaAgua;
        solo.agua -= remover;
        if (solo.agua < 0) solo.agua = 0;
    }
    
    // Ajusta nutrientes para o valor ótimo
    int diferencaNutrientes = NUTRIENTES_OTIMOS - solo.nutrientes;
    if (diferencaNutrientes > 0) {
        // Precisa adicionar nutrientes (até 10 unidades)
        int adicionar = (diferencaNutrientes > 10) ? 10 : diferencaNutrientes;
        solo.nutrientes += adicionar;
    } else if (diferencaNutrientes < 0) {
        // Precisa remover nutrientes (até 10 unidades)
        int remover = (-diferencaNutrientes > 10) ? 10 : -diferencaNutrientes;
        solo.nutrientes -= remover;
        if (solo.nutrientes < 0) solo.nutrientes = 0;
    }
    
    // Consome uma carga
    cargasBateria--;
    
    if (cargasBateria <= 0) {
        return false;  // bateria esgotada, deve ser reciclado
    }
    
    return true;
}

bool FerramentaZ::estaUtilizavel() const {
    return cargasBateria > 0;
}

std::string FerramentaZ::getInfo() const {
    std::ostringstream oss;
    oss << "Harmonizador de Solo #" << getNumeroSerie() 
        << " - Bateria: " << cargasBateria 
        << "/" << CAPACIDADE_BATERIA << " cargas";
    return oss.str();
}