#ifndef GERIRPALPITE_HPP
#define GERIRPALPITE_HPP

#include <iostream>
#include <vector>

class GerirPalpite {
  private:
    std::vector<std::string> comparePalpites;
    std::vector<std::string> compareOficial;
    ///Palpite
    std::string nome_participante;
    std::vector<std::pair<std::string, std::string>> grupos;
    std::vector<std::string> quartas;
    std::vector<std::string> semifinalistas;
    std::pair<std::string, std::string> finalistas;
    std::string terceiro;
    std::string campeao;
    ///Oficial
    std::vector<std::pair<std::string, std::string>> gruposOficiais;
    std::vector<std::string> quartasOficiais;
    std::vector<std::string> semifinalistasOficiais;
    std::pair<std::string, std::string> finalistasOficiais;
    std::string terceiroOficial;
    std::string campeaoOficiail;

  public:
    GerirPalpite ();
    void cadastrarPalpite ();
    void gerarPalpites ();
    bool validaPalpiteQuartas (std::string palpite);
    bool validaPalpiteSemi (std::string palpite);
    bool validaPalpiteFinal (std::string palpite);
    bool validaPalpiteClassificacao (std::string palpite);
    void resultadosOficias ();
    void gerarResultadoOficial ();
    void calcularPontos ();
    std::pair<bool, std::string> validarArquivo (std::string s);
    void falha_leitura (std::string mens_erro);
};

#endif //GERIRPALPITE_HPP