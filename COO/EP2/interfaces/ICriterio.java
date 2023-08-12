package interfaces;

import models.ProdutoPadrao;

public interface ICriterio {
    public int compara(ProdutoPadrao pUm, ProdutoPadrao pDois);

    public Object getValor(ProdutoPadrao i);

}