package criterios;

import interfaces.ICriterio;
import models.ProdutoPadrao;

public class QuantidadeEstoque implements ICriterio {
    public int compara(ProdutoPadrao pUm, ProdutoPadrao pDois) {
        if (pUm.getQtdEstoque() < pDois.getQtdEstoque())
            return -1;
        else if (pUm.getQtdEstoque() == pDois.getQtdEstoque())
            return 0;
        return 1;
    }

    public Object getValor(ProdutoPadrao i) {
        return i.getQtdEstoque();
    }
}