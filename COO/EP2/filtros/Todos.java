package filtros;

import interfaces.*;
import models.*;

public class Todos implements IFiltragem {
    public ProdutoCompleto filtra(ProdutoCompleto pCompleto) {
        return pCompleto;
    }
}
