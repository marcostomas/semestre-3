public class Ordenacao {
    public void ordenaInsertion(int ini, int fim, Produto[] produtos, String criterio) {
        for (int i = ini; i <= fim; i++) {

            Produto x = produtos[i];
            int j = (i - 1);

            while (j >= ini) {

                if (criterio.equals(GeradorDeRelatorios.CRIT_DESC_CRESC)) {

                    if (x.getDescricao().compareToIgnoreCase(produtos[j].getDescricao()) < 0) {

                        produtos[j + 1] = produtos[j];
                        j--;
                    } else
                        break;
                } else if (criterio.equals(GeradorDeRelatorios.CRIT_PRECO_CRESC)) {

                    if (x.getPreco() < produtos[j].getPreco()) {

                        produtos[j + 1] = produtos[j];
                        j--;
                    } else
                        break;
                } else if (criterio.equals(GeradorDeRelatorios.CRIT_ESTOQUE_CRESC)) {

                    if (x.getQtdEstoque() < produtos[j].getQtdEstoque()) {

                        produtos[j + 1] = produtos[j];
                        j--;
                    } else
                        break;
                } else
                    throw new RuntimeException("Criterio invalido!");
            }

            produtos[j + 1] = x;
        }
    }

    public void ordenaQuick(int ini, int fim, Produto[] produtos, String criterio) {
        if (ini < fim) {

            int q = Particionamento.particiona(ini, fim, produtos, criterio);

            ordenaQuick(ini, q, produtos, criterio);
            ordenaQuick(q + 1, fim, produtos, criterio);
        }
    }

}
