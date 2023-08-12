package algoritmos;

import models.*;
import interfaces.*;

public class InsertionSort implements IAlgoritmo {
    private IOrdenacao tipoOrdem;

    public InsertionSort(IOrdenacao tipoOrdem) {
        this.tipoOrdem = tipoOrdem;
    }

    public void ordena(int ini, int fim, ProdutoCompleto pCompleto) {
        for (int i = ini; i <= fim; i++) {
            ProdutoPadrao key = pCompleto.produtos.get(i);
            Formatacao key_formato = pCompleto.formatos.get(i);

            int j = (i - 1);

            while (j >= ini) {
                if ((tipoOrdem.ordena(pCompleto, key, j)) == false) {
                    break;
                }
                j--;
            }
            pCompleto.set(j + 1, key, key_formato);
        }
    }
}
