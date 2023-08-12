package ordenacao;

import criterios.Descricao;
import interfaces.*;
import models.*;

public class Decrescente implements IOrdenacao {
    private ICriterio criterio;

    public Decrescente(ICriterio criterio) {
        this.criterio = criterio;
    }

    // método usado pelo InsertionSort.java
    public boolean ordena(ProdutoCompleto pCompleto, ProdutoPadrao key, int pos) {
        ProdutoPadrao compare_To = pCompleto.produtos.get(pos);

        if ((criterio.compara(key, compare_To)) > 0) {
            pCompleto.avancaPosicao(pos);
            return true;
        } else {
            return false;
        }
    }

    // método usado pelo QuickSort.java
    public int particiona(int ini, int fim, ProdutoCompleto pCompleto) {
        ProdutoPadrao x = pCompleto.produtos.get(ini);
        int i = (ini - 1);
        int j = (fim + 1);

        while (true) {
            if (criterio instanceof Descricao) {
                do {
                    j--;
                    criterio.getValor(x);
                } while (criterio.getValor(pCompleto.produtos.get(j)).toString()
                        .compareToIgnoreCase(criterio.getValor(x).toString()) < 0);

                do {
                    i++;
                } while (criterio.getValor(pCompleto.produtos.get(i)).toString()
                        .compareToIgnoreCase(criterio.getValor(x).toString()) > 0);
            } else {
                double z;
                double y;
                do {
                    j--;
                    z = Double.parseDouble(criterio.getValor(pCompleto.produtos.get(j)).toString());
                    y = Double.parseDouble(criterio.getValor(x).toString());
                } while (z < y);

                do {
                    i++;
                    z = Double.parseDouble(criterio.getValor(pCompleto.produtos.get(i)).toString());
                    y = Double.parseDouble(criterio.getValor(x).toString());
                } while (z > y);
            }

            if (i < j) {
                pCompleto.trocaPosicao(i, j);
            } else
                return j;
        }
    }

}
