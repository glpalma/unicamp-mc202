// feita com Pedro Bordignon
#define M 113

int hash(int RA_aluno) { // RA_aluno é um inteiro de 4 dígitos único de cada estudante
    return (RA_aluno % M);
}
