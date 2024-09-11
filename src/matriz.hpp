#ifndef MATRIZ_HPP
#define MATRIZ_HPP
#include <iostream>
#include <vector>
using namespace std;

class Matriz {
    public:
        vector<vector<int>> lerMatriz(string arquivo);
        void printarMatriz(const vector<vector<int>>& matriz);
        void criarGeracao(const vector<vector<int>>& entrada, vector<vector<int>>& saida);
        void registrarMatriz(const vector<vector<int>>& matriz, const string& nomeArquivo,const int cont);
        void limparMatriz(vector<vector<int>>& matriz);
        void menu();
};

#endif
