package filtros;

import java.util.ArrayList;
import java.util.Iterator;

import interfaces.IFiltragem;
import models.Formatacao;
import models.ProdutoCompleto;
import models.ProdutoPadrao;

public class CategoriaIgual implements IFiltragem {

    String match;

    public CategoriaIgual(String match) {
        this.match = match;
    }

    public ProdutoCompleto filtra(ProdutoCompleto pCompleto) {
        Iterator<ProdutoPadrao> itP = pCompleto.produtos.iterator();
        Iterator<Formatacao> itF = pCompleto.formatos.iterator();

        ArrayList<ProdutoPadrao> produtosFiltrados = new ArrayList<>();
        ArrayList<Formatacao> formatosFiltrados = new ArrayList<>();

        ProdutoPadrao p;
        Formatacao f;

        while (itP.hasNext()) {
            p = itP.next();
            f = itF.next();

            if (p.getCategoria().equals(match)) {
                produtosFiltrados.add(p);
                formatosFiltrados.add(f);
            }
        }

        pCompleto.produtos = produtosFiltrados;
        pCompleto.formatos = formatosFiltrados;

        return pCompleto;
    }
}
