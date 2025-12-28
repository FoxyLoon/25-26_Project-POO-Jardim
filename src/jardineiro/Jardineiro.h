#ifndef JARDINEIRO_H
#define JARDINEIRO_H

// Representa o jardineiro e a sua posição dentro ou fora do jardim
class Jardineiro
{
public:
    Jardineiro();
    ~Jardineiro();

    // Setters
    void entraNoJardim(int l, int c);
    void moveNoJardim(int l, int c);
    void saiDoJardim();

    // Getters
    bool isNoJardim() const;
    int getLinha() const;
    int getColuna() const;

private:
    bool noJardim;
    int linha, coluna;
};

#endif
