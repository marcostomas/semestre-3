package interfaces;

import models.*;

public interface IOrdenacao {
    // Método usado pelo Insertion Sort que recebe a chave e a posição do arranjo a
    // ser comparada
    public boolean ordena(ProdutoCompleto pCompleto, ProdutoPadrao key, int pos);

    public int particiona(int ini, int fim, ProdutoCompleto pCompleto);

}