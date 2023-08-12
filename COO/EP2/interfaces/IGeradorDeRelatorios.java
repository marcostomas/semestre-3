package interfaces;

import models.ProdutoCompleto;

public interface IGeradorDeRelatorios {
    public void gerarRelatorioOrdenado(ProdutoCompleto pCompleto, String arquivoSaida, String argFiltro);

    public void debug(int total, String argFiltro);
}
