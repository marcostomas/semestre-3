package models;

import java.util.ArrayList;

public class ProdutoCompleto {

    public ArrayList<ProdutoPadrao> produtos = new ArrayList<>();
    public ArrayList<Formatacao> formatos = new ArrayList<>();

    public void trocaPosicao(int posOrigem, int posDestino) {
        ProdutoPadrao auxP = produtos.get(posDestino);
        Formatacao auxF = formatos.get(posDestino);

        produtos.set(posDestino, produtos.get(posOrigem));
        produtos.set(posOrigem, auxP);

        formatos.set(posDestino, formatos.get(posOrigem));
        formatos.set(posOrigem, auxF);
    }

    public void adiciona(ProdutoPadrao produto, Formatacao formato) {
        produtos.add(produto);
        formatos.add(formato);
    }

    public void avancaPosicao(int pos) {
        produtos.set(pos + 1, produtos.get(pos));
        formatos.set(pos + 1, formatos.get(pos));

    }

    public void set(int posDestino, ProdutoPadrao p, Formatacao f) {
        produtos.set(posDestino, p);
        formatos.set(posDestino, f);
    }

    public void remove(ProdutoPadrao p, Formatacao f) {
        produtos.remove(p);
        formatos.remove(f);
    }
}
