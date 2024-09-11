#include "matriz.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<int>> Matriz::lerMatriz(string nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    vector<vector<int>> matriz;

    if (arquivo.is_open()) {
        string linha;
        getline(arquivo, linha); // lê a primeira linha para obter o tamanho da matriz
        int tamanho = stoi(linha);
        matriz.resize(tamanho, vector<int>(tamanho));

        for (int i = 0; i < tamanho; ++i) {
            getline(arquivo, linha); // lê uma linha inteira
            stringstream ss(linha);
            for (int j = 0; j < tamanho; ++j) {
                ss >> matriz[i][j]; // lê o próximo número da linha
            }
        }

        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }
    return matriz;
}

void Matriz::printarMatriz(const vector<vector<int>>& matriz) {
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl << endl;
    }
}
/* 
[i-1,j-1][i-1,j][i-1,j+1]
[i,j-1]  [i,j]  [i,j+1]
[i+1,j-1][i+1,j][i+1,j+1]
*/ 
void Matriz::criarGeracao(const vector<vector<int>>& entrada, vector<vector<int>>& saida) {
    size_t tamanho = entrada.size();
    saida = entrada;
    for (size_t i = 0; i < tamanho; ++i) {
        for (size_t j = 0; j < entrada[i].size(); ++j) {
            int contador0 = 0, contador1 = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if (di == 0 && dj == 0) 
                        continue; // proprio elemento
                    size_t ni = i + di;
                    size_t nj = j + dj;
                    if (ni < tamanho && nj < entrada[i].size()) {
                        if (entrada[ni][nj] == 0)
                            contador0++;
                        else
                            contador1++;
                    }
                }
            }
            // Aplicando regras
            if (entrada[i][j] == 1 && (contador1 < 2 || contador1 > 3)) {
                saida[i][j] = 0; // Morte por solidão ou superpopulação
            } else if (entrada[i][j] == 0 && contador1 == 3) {
                saida[i][j] = 1; // Nascimento por reprodução
            } else {
                saida[i][j] = entrada[i][j]; // Mantem o atual
            }
        }
    }
}

void Matriz::registrarMatriz(const vector<vector<int>>& matriz, const string& nomeArquivo,const int cont){
    ofstream arquivo(nomeArquivo,ios::app);
    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return;
    }
    arquivo << "GERAÇÃO [" << cont << "]" << endl << endl;
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << endl << endl;
    }
    arquivo.close();
    cout << "Matriz registrada com sucesso no arquivo: " << nomeArquivo << endl;
}

void Matriz::limparMatriz(vector<vector<int>>& matriz){
    for (size_t i = 0; i < matriz.size(); ++i) {
        for (size_t j = 0; j < matriz[i].size(); ++j) {
            matriz[i][j] = 0;
        }
    }   
}

void Matriz::menu(){
    int geracoes;
    cout << endl << endl << "Quantas [GERAÇÕES] serão geradas e registradas ? ";
    cin >> geracoes;
    Matriz m;
    vector<vector<int>> matriz1 = m.lerMatriz("datasets/entrada.mps");
    vector<vector<int>> matriz2;
    m.registrarMatriz(matriz1,"datasets/geracoes.mps",0);
    for(int a=0;a<geracoes;a++){
        if(a%2==0){
            cout << endl << endl << "[MATRIZ 1]:" << endl << endl;
            m.printarMatriz(matriz1);
            m.criarGeracao(matriz1,matriz2);
            cout << endl << endl << "[MATRIZ 2]:" << endl << endl;
            m.printarMatriz(matriz2);
            m.registrarMatriz(matriz2,"datasets/geracoes.mps",a+1);
            m.limparMatriz(matriz1);
        } else {
            m.criarGeracao(matriz2,matriz1);
            cout << endl << endl << "[MATRIZ 1]:" << endl << endl;
            m.printarMatriz(matriz1);
            m.registrarMatriz(matriz1,"datasets/geracoes.mps",a+1);
            m.limparMatriz(matriz2);
        }
    }   
}