package algoritmos;

import interfaces.*;
import models.ProdutoCompleto;

public class QuickSort implements IAlgoritmo {
    private IOrdenacao tipoOrdem;

    public QuickSort(IOrdenacao tipoOrdem) {
        this.tipoOrdem = tipoOrdem;
    }

    public void ordena(int ini, int fim, ProdutoCompleto pCompleto) {

        if (ini < fim) {
            int q = tipoOrdem.particiona(ini, fim, pCompleto);
            ordena(ini, q, pCompleto);
            ordena(q + 1, fim, pCompleto);
        }
    }

}