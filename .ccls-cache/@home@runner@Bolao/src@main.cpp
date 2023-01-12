#include <iostream>
#include <fstream>
#include <string>
#include "../include/GerirPalpite.hpp"

using namespace std;

/**
  * Inicio da função main.
  */
int main() {
  int opcao;
  bool t = true;

  cout << ">  Validando arquivo de palpites, por favor aguarde... \n";
  cout << "------------------------------------------------------\n";

  GerirPalpite *admPalpite = new GerirPalpite();

  while (t == true) {
    cout << "\nMenu:\n";
    cout << "1 - Cadastrar palpites\n";
    cout << "2 - Ver palpites cadastrados\n";
    cout << "3 - Cadastrar resultados oficiais\n";
    cout << "4 - Ver pontuação final\n";
    cout << "5 - Sair\n";
    cout << "Sua escolha: ";
    cin >> opcao;
    
    if (opcao == 1) {
      cout << "\nCadastrar palpites:\n";
      admPalpite->cadastrarPalpite();
    }
    else if (opcao == 2) {
      int op;

      cout << "\nVer palpites cadastrados:\n\n";
      
      //Leitura:
      ifstream finS("data/palpite.txt");
      char s;
      while (finS.get(s)) { cout << s; }
      finS.close();
      cout << "\n\n";

      cout << "\nVoltar ao Menu inicial ou Sair?\n";
      cout << "1 - Voltar \n";
      cout << "2 - Sair \n";
      cout << "Sua escolha: ";
      cin >> op;

      if (op == 1) {
        continue;
      }
      else {
        cout << "Programa finalizado.";
        t=false;
      }
    }
    else if (opcao == 3) {
      cout << "Cadastrar resultados oficiais:\n";
      admPalpite->resultadosOficias();
    }
    else if(opcao == 4) {
      int op;

      admPalpite->calcularPontos();
      
      cout << "\nVer pontuação final:\n\n";
      
      //Leitura:
      ifstream finS("data/resultado.txt");
      char s;
      while (finS.get(s)) { cout << s; }
      finS.close();
      cout << "\n\n";

      cout << "\nVoltar ao menu inicial ou Sair?\n";
      cout << "1 - Voltar \n";
      cout << "2 - Sair \n";
      cout << "Sua escolha: ";
      cin >> op;

      if (op == 1) {
        continue;
      }
      else {
        cout << "Programa finalizado.";
        t=false;
      }
    }
    else if (opcao == 5) {
      cout << "Programa finalizado.";
      t=false;
    }
    else {
      cout << "Erro na escolha das opções, tente novamente! \n";
    }
  }
  
  return 0;
}