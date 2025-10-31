#ifndef JARDINEIRO_H
#define JARDINEIRO_H

// Representa o jardineiro e a sua posição dentro ou fora do jardim
class Jardineiro {
private:
    bool noJardim;
    int linha, coluna;
public:
    Jardineiro();
    void entrarNoJardim(int l, int c);
    void sairDoJardim();
    bool isNoJardim() const;
    int getLinha() const;
    int getColuna() const;
};

#endif
