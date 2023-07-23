public class Particionamento {
    public static int particiona(int ini, int fim, Produto[] produtos, String criterio) {

        Produto x = produtos[ini];
        int i = (ini - 1);
        int j = (fim + 1);

        while (true) {

            if (criterio.equals(GeradorDeRelatorios.CRIT_DESC_CRESC)) {

                do {
                    j--;

                } while (produtos[j].getDescricao().compareToIgnoreCase(x.getDescricao()) > 0);

                do {
                    i++;

                } while (produtos[i].getDescricao().compareToIgnoreCase(x.getDescricao()) < 0);
            } else if (criterio.equals(GeradorDeRelatorios.CRIT_PRECO_CRESC)) {

                do {
                    j--;

                } while (produtos[j].getPreco() > x.getPreco());

                do {
                    i++;

                } while (produtos[i].getPreco() < x.getPreco());
            }

            else if (criterio.equals(GeradorDeRelatorios.CRIT_ESTOQUE_CRESC)) {

                do {
                    j--;

                } while (produtos[j].getQtdEstoque() > x.getQtdEstoque());

                do {
                    i++;

                } while (produtos[i].getQtdEstoque() < x.getQtdEstoque());

            } else {

                throw new RuntimeException("Criterio invalido!");
            }

            if (i < j) {
                Produto temp = produtos[i];
                produtos[i] = produtos[j];
                produtos[j] = temp;
            } else
                return j;
        }
    }
}
