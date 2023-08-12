package ordenacao;

import criterios.Descricao;
import interfaces.*;
import models.*;

public class Crescente implements IOrdenacao {
    private ICriterio criterio;

    public Crescente(ICriterio criterio) {
        this.criterio = criterio;
    }

    // método usado pelo InsertionSort.java
    public boolean ordena(ProdutoCompleto lista_produtos, ProdutoPadrao key, int pos) {
        ProdutoPadrao compare_To = lista_produtos.produtos.get(pos);

        if ((criterio.compara(key, compare_To)) < 0) {
            lista_produtos.avancaPosicao(pos);
            return true;
        } else {
            return false;
        }
    }

    // método usado pelo QuickSort.java
    public int particiona(int ini, int fim, ProdutoCompleto lista_produtos) {
        ProdutoPadrao x = lista_produtos.produtos.get(ini);
        int i = (ini - 1);
        int j = (fim + 1);

        while (true) {

            if (criterio instanceof Descricao) {
                do {
                    j--;
                    criterio.getValor(x);
                } while (criterio.getValor(lista_produtos.produtos.get(j)).toString()
                        .compareToIgnoreCase(criterio.getValor(x).toString()) > 0);

                do {
                    i++;
                } while (criterio.getValor(lista_produtos.produtos.get(i)).toString()
                        .compareToIgnoreCase(criterio.getValor(x).toString()) < 0);

            } else {
                double z;
                double y;
                do {
                    j--;
                    z = Double.parseDouble(criterio.getValor(lista_produtos.produtos.get(j)).toString());
                    y = Double.parseDouble(criterio.getValor(x).toString());
                } while (z > y);

                do {
                    i++;
                    z = Double.parseDouble(criterio.getValor(lista_produtos.produtos.get(i)).toString());
                    y = Double.parseDouble(criterio.getValor(x).toString());
                } while (z < y);
            }

            if (i < j) {
                lista_produtos.trocaPosicao(i, j);
            } else
                return j;
        }
    }
}
