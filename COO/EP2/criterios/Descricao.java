package criterios;

import interfaces.ICriterio;
import models.ProdutoPadrao;

public class Descricao implements ICriterio {
    public int compara(ProdutoPadrao pUm, ProdutoPadrao pDois) {
        return pUm.getDescricao().compareToIgnoreCase(pDois.getDescricao());
    }

    public Object getValor(ProdutoPadrao i) {
        return i.getDescricao();
    }
}