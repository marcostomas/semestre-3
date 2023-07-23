public class Ordenacao {
    public static void ordena(int ini, int fim, String algoritmo, Produto[] produtos, String criterio) {

        if (algoritmo.equals(GeradorDeRelatorios.ALG_INSERTIONSORT)) {

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
        } else if (algoritmo.equals(GeradorDeRelatorios.ALG_QUICKSORT)) {

            if (ini < fim) {

                int q = Particionamento.particiona(ini, fim, produtos, criterio);

                ordena(ini, q, algoritmo, produtos, criterio);
                ordena(q + 1, fim, algoritmo, produtos, criterio);
            }
        } else {
            throw new RuntimeException("Algoritmo invalido!");
        }
    }
}
