package criterios;

import interfaces.ICriterio;
import models.ProdutoPadrao;

public class Preco implements ICriterio {
    public int compara(ProdutoPadrao pUm, ProdutoPadrao pDois) {
        if (pUm.getPreco() < pDois.getPreco())
            return -1;
        else if (pUm.getPreco() == pDois.getPreco())
            return 0;
        return 1;
    }

    public Object getValor(ProdutoPadrao i) {
        return i.getPreco();
    }
}