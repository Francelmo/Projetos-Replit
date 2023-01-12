#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include "../include/GerirPalpite.hpp"

using namespace std;

GerirPalpite::GerirPalpite () {
  //Criando inistância do objeto.
  char p[512];
  bool valida;
  string palpite;
  pair<bool, string> verifica;
  vector<string> palpites;

  //Leitura do arquivo.
  ifstream finP ("data/palpite.txt");

  while(finP.getline(p, 512)) {
    palpite = p;
    palpites.push_back(palpite);
  }

  //Validar arquivo.
  for (vector<string>::iterator it = palpites.begin(); it != palpites.end(); ++it) {
    verifica = validarArquivo(*it);
    valida = verifica.first;
    if (valida == false) {
      falha_leitura (verifica.second);
    }
    else {
      continue;
    }
  }
}

void GerirPalpite::cadastrarPalpite () {
  int j = 0;
  char grupo = 'A';
  bool valida, verifica = true;
  string primeiroTime, segundoTime, time, finalista1, finalista2, buffer;

  //Nome da pessoa.
  getline (cin, buffer); /*!< Lipar o buffer da entrada padrão */
  cout << "Insira o seu nome: ";
  getline(cin, nome_participante);
  cout << "\n";

  //Nome dos times por grupo.
  cout << "Digite os nomes dos times classificados que compõe os grupos em minusculo e sem acentos:\n";
  for (int i=0; i<8; i++) {
    cout << "Primeiro do grupo " << grupo << ": ";
    getline(cin, primeiroTime);
    cout << "Segundo do grupo: " << grupo << ": ";
    getline(cin, segundoTime);

    grupos.push_back(make_pair(primeiroTime, segundoTime));

    grupo += 1;
  }
  cout << "\n";

  //Nome dos times das quartas de final.
  cout << "Insira os nomes dos times classificados que jogarão as quartas de final em minusculo e sem acentos\n";
  while (j<8) {
    cout << "Digite o nome do time: ";
    getline(cin, time);

    valida = validaPalpiteQuartas(time);

    if (valida == true) {
      quartas.push_back(time);
      j++;
    }
    else {
      cout << "Time não corresponde a nenhum atribuido aos grupos, tente novamente!\n";
    }
  }
  cout << "\n";

  j=0;

  //Nome dos semifinalistas.
  cout << "Digite os nomes dos semifinalistas em minusculo e sem acentos\n";
  while (j<4) {
    cout << "Digite o nome do time: ";
    getline(cin, time);

    valida = validaPalpiteSemi(time);

    if (valida == true) {
      semifinalistas.push_back(time);
      j++;
    }
    else {
      cout << "Time não corresponde a nenhum atribuido às quartas de final, tente novamente!\n";
    }
  }
  cout << "\n";

  j=0;

  //Nome dos finalistas.
  cout << "Insira os nomes dos finalistas em minusculo e sem acentos\n";
  while (verifica == true) {
    cout << "Primiero finalista: ";
    getline(cin, finalista1);

    valida = validaPalpiteFinal(finalista1);

    if (valida != true) {
      cout << "Time não corresponde a nenhum atribuido aos semifinalistas, tente novamente!\n";
    }
    else {
      cout << "Segundo finalista: ";
      getline(cin, finalista2);

      valida = validaPalpiteFinal(finalista2);

      if (valida != true) {
      cout << "Time não corresponde a nenhum atribuido aos semifinalistas, tente novamente!\n";
      }
      else {
        finalistas = make_pair(finalista1, finalista2);
        verifica = false;
      }
    }
  }
  cout << "\n";

  verifica = true;

  //Nome do terceiro colocado.
  while (verifica==true) {
    cout << "Digite o nome do terceiro colocado: ";
    getline (cin, terceiro);

    valida = validaPalpiteFinal(terceiro);

    if (finalistas.first.compare(terceiro) == 0) {
      valida = false;
    }
    else if (finalistas.second.compare(terceiro) == 0)    {
      valida = false;  
    }

    if (valida == true) {
      verifica = false;
    }
    else {
      cout << "Time não corresponde a nenhum atribuido aos semifinalistas ou está entre os finalistas, tente novamente!\n";
    }
  }
  cout << "\n";

  verifica = true;

  //Nome do campeão.
  while (verifica==true) {
    cout << "Digite o nome do time campeão: ";
    getline(cin, campeao);

    if ((finalistas.first.compare(campeao) == 0) || (finalistas.second.compare(campeao) == 0)) {
      verifica = false;
    }
    else {
      cout << "Time não corresponde a nenhum atribuido aos finalistas, tente novamente!\n";
    }
  }
  cout << "\n";

  gerarPalpites ();
}

void GerirPalpite::gerarPalpites () {
  //Gravação
  ofstream fout ("data/palpite.txt", ofstream::app);
  
  fout << "\n" << nome_participante << "; ";
  for (vector<pair<string, string>>::iterator it = grupos.begin(); it!=grupos.end(); ++it) {
    if (*it == grupos.back()) {
      fout << it->first << ", " << it->second;
    }
    else {
      fout << it->first << ", " << it->second << ", ";
    }
  }
  fout << "; ";
  for (vector<string>::iterator it = quartas.begin(); it!=quartas.end(); ++it) {
    if (*it == quartas.back()) {
      fout << *it;
    }
    else {
      fout << *it << ", ";
    }
  }
  fout << "; ";
  for (vector<string>::iterator it = semifinalistas.begin(); it!=semifinalistas.end(); ++it) {
    if (*it == semifinalistas.back()) {
      fout << *it;
    }
    else {
      fout << *it << ", ";
    }
  }
  fout << "; ";
  fout << finalistas.first << ", " << finalistas.second << "; ";
  fout << terceiro << ", ";
  fout << campeao << ".";
  fout.close();

  cout << "\n";
}

bool GerirPalpite::validaPalpiteQuartas (string palpite) {
  bool testar = false;
  
  for (vector<pair<string, string>>::iterator it = grupos.begin(); it != grupos.end(); ++it) {
    if ((it->first.compare(palpite) == 0) || (it->second.compare(palpite) == 0)) {
      testar = true;
    }
  }

  return testar;
}

bool GerirPalpite::validaPalpiteSemi (std::string palpite) {
  bool testar = false;
  
  for (vector<string>::iterator it = quartas.begin(); it != quartas.end(); ++it) {
    if (it->compare(palpite) == 0) {
      testar = true;
    }
  }

  return testar;
}

bool GerirPalpite::validaPalpiteFinal (std::string palpite) {
  bool testar = false;
  
  for (vector<string>::iterator it = semifinalistas.begin(); it != semifinalistas.end(); ++it) {
    if (it->compare(palpite) == 0) {
      testar = true;
    }
  }

  return testar;
}

bool GerirPalpite::validaPalpiteClassificacao (std::string palpite) {
  bool testar = false;
  
  if ((finalistas.first.compare(palpite) == 0) || (finalistas.second.compare(palpite) == 0)) {
    testar = true;
  }

  return testar;      
}

void GerirPalpite::resultadosOficias () {
  char grupo = 'A';
  string primeiroTime, segundoTime, time, finalista1, finalista2, buffer;

  getline (cin, buffer); /*!< Lipar o buffer da entrada padrão */

  //Nome dos times classificados por grupo (Oficial).
  cout << "Digite os nomes dos times classificados que compõe os grupos (Oficiais) em minusculo e sem acentos:\n";
  for (int i=0; i<8; i++) {
    cout << "Primeiro do grupo " << grupo << ": ";
    getline(cin, primeiroTime);
    cout << "Segundo do grupo: " << grupo << ": ";
    getline(cin, segundoTime);

    gruposOficiais.push_back(make_pair(primeiroTime, segundoTime));

    grupo += 1;
  }
  cout << "\n";

  //Nome dos times classificados das quartas de final.
  cout << "Insira os nomes dos times classificados que jogaram as quartas de final (Oficial) em minusculo e sem acentos\n";
  for (int i=0; i<8; i++) {
    cout << "Digite o nome do time: ";
    getline(cin, time);

    quartasOficiais.push_back(time);
  }
  cout << "\n";

  //Nome dos semifinalistas (Oficial).
  cout << "Digite os nomes dos semifinalistas (Oficial) em minusculo e sem acentos\n";
  for (int i=0; i<4; i++) {
    cout << "Digite o nome do time: ";
    getline(cin, time);

    semifinalistasOficiais.push_back(time);
  }
  cout << "\n";

  //Nome dos finalistas (Oficial).
  cout << "Insira os nomes dos finalistas (Oficial) em minusculo e sem acentos\n";
  cout << "Primiero finalista (Oficial): ";
  getline(cin, finalista1);
  cout << "Segundo finalista (Oficial): ";
  getline(cin, finalista2);
  finalistasOficiais = make_pair(finalista1, finalista2);
  cout << "\n";

  //Nome do terceiro colocado (Oficial).
  cout << "Digite o nome do terceiro colocado (Oficial): ";
  getline (cin, terceiroOficial);
  cout << "\n";

  //Nome do campeão (Oficial).
  cout << "Digite o nome do time campeão (Oficial): ";
  getline(cin, campeaoOficiail);
  cout << "\n";

  gerarResultadoOficial ();
}

void GerirPalpite::gerarResultadoOficial() {
  //Gravação
  ofstream fout ("data/resultadoOficial.txt");
  
  for (vector<pair<string, string>>::iterator it = gruposOficiais.begin(); it!=gruposOficiais.end(); ++it) {
    if (*it == gruposOficiais.back()) {
      fout << it->first << ", " << it->second;
    }
    else {
      fout << it->first << ", " << it->second << ", ";
    }
  }
  fout << "; ";
  for (vector<string>::iterator it = quartasOficiais.begin(); it!=quartasOficiais.end(); ++it) {
    if (*it == quartasOficiais.back()) {
      fout << *it;
    }
    else {
      fout << *it << ", ";
    }
  }
  fout << "; ";
  for (vector<string>::iterator it = semifinalistasOficiais.begin(); it!=semifinalistasOficiais.end(); ++it) {
    if (*it == semifinalistasOficiais.back()) {
      fout << *it;
    }
    else {
      fout << *it << ", ";
    }
  }
  fout << "; ";
  fout << finalistasOficiais.first << ", " << finalistasOficiais.second << "; ";
  fout << terceiroOficial << ", ";
  fout << campeaoOficiail << ".";
  fout.close();

  cout << "\n";
}

void GerirPalpite::calcularPontos () {
  int decrescimo, pontos=0;
  string resultado, palpite;
  char *pch, str[512];
  vector<string> resultados, palpites, vetorPalpites;

  ifstream arquivoResultado ("data/resultadoOficial.txt");
  ifstream arquivoPalpite ("data/palpite.txt");

  arquivoResultado.seekg (0, arquivoResultado.end);
  int length = arquivoResultado.tellg();
  arquivoResultado.seekg (0, arquivoResultado.beg);

  if (length == 0) {
    falha_leitura ("\n\naguardando cadastro dos resultados oficiais...\n\n");
  }
 
  /// Leitura do arquivo Resultado Oficial.
  if (!arquivoResultado) {
    cerr << "O arquivo não pôde ser aberto\n";
    exit(1);
  } 
  else {
    while (arquivoResultado.getline(str, 512)) {
      resultado = str;
    }
    
    arquivoResultado.close();
  }

  /// Leitura do arquivo Palpite.
  if (!arquivoPalpite) {
    cerr << "O arquivo não pôde ser aberto\n";
    exit(1);
  }
  else {
    while (arquivoPalpite.getline(str, 512)) {
      palpite = str;
      vetorPalpites.push_back(palpite);
    }
    
    arquivoPalpite.close();
  }

  int tam = resultado.length();

  for (int i=0; i<tam; i++) {
      str[i] = resultado[i];
  }
  
  pch = strtok (str, "; , .");
  //Ler do aquivo resultado oficial para um vector
  while (pch!=NULL) {
    string resultado = pch;
    resultados.push_back(resultado);
    pch = strtok (NULL, "; , .");
  }

  ofstream fout ("data/resultado.txt");
  
  for (vector<string>::iterator it = vetorPalpites.begin(); it != vetorPalpites.end(); ++it) {
    tam = it->length();
    
    for (int i=0; i<tam; i++) {
      str[i] = (*it)[i];
    }

    pch = strtok (str, "; , .");
    //Ler do aquivo palpite para um vector
    while (pch!=NULL) {
      string palpite = pch;
      palpites.push_back(palpite);
      pch = strtok (NULL, "; , .");
    }

    //Pontuação para acertos com colocação correta nos grupos.
    for (int i=0, j=1; i<16; i++, j++) {
      if (resultados[i].compare(palpites[j]) == 0)         {
        pontos+=2;
      }
    }

    decrescimo = pontos / 2; /*!< Ação para não ter recontagem de pontos nas demais pontuações */
    
    ///Demais pontuações.
    for (int i=0; i<16; i++) {
      for (int j=1; j<17; j++) {
        if (resultados[i].compare(palpites[j]) == 0)         {
          pontos++; /*!< Pontuação para acertos com colocação errada nos grupos */
        }
      }
    }

    for (int i=16; i<24; i++) {
      for (int j=17; j<25; j++) {
        if (resultados[i].compare(palpites[j]) == 0)         {
          pontos+=2; /*!< Pontuação para qualquer acerto entre as quartas de final */
        }
      }
    }
    
    for (int i=24; i<28; i++) {
      for (int j=25; j<29; j++) {
        if (resultados[i].compare(palpites[j]) == 0)         {
          pontos+=2; /*!< Pontuação para qualquer acerto entre os semifinalistas */
        }
      }
    }
    
    for (int i=28; i<30; i++) {
      for (int j=29; j<31; j++) {
        if (resultados[i].compare(palpites[j]) == 0)         {
          pontos+=2; /*!< Pontuação para qualquer acerto entre os finalistas */
        }
      }
    }
    
    if (resultados[30].compare(palpites[31]) == 0)        {
      pontos+=2; /*!< Pontuação para o acerto do terceiro colocado */
    }
      
    if (resultados[31].compare(palpites[32]) == 0)        {
      pontos+=5; /*!< Pontuação para o acerto do campeão */
    }

    pontos = pontos - decrescimo;

    fout << palpites[0] << ": " << pontos << " pontos\n";

    pontos = decrescimo = 0;
    palpites.clear();
  }
  
  fout.close();
}

pair<bool, string> GerirPalpite::validarArquivo (string p) {
  int tam, cont = 0;
  char palpite[256];
  pair<bool, string> verifica;

  tam = p.length();
  
  //Testar quantidade de ';'.
  for (int i=0; i<tam; i++) {
    if (p[i] == ';') {
      cont++;
    }
  }
  
  if (cont < 5 || cont > 5) {
    verifica = make_pair(false, "Presença de mais ou de menos 5 “;” em alguma linha do palpite.\n");
  }
  else {
    verifica = make_pair(true, "");  
  }
  
  return verifica;
}

void GerirPalpite::falha_leitura (string mens_erro) {
  cout << mens_erro << "\n";
  exit(1);
}