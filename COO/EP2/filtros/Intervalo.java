package filtros;

import java.util.*;

import interfaces.IFiltragem;
import models.Formatacao;
import models.ProdutoCompleto;
import models.ProdutoPadrao;

public class Intervalo implements IFiltragem {

    private double valorMenor;
    private double valorMaior;

    public Intervalo(double valorMenor, double valorMaior) {
        this.valorMenor = valorMenor;
        this.valorMaior = valorMaior;
    }

    public boolean menorQue(double valor1, double valor2) {
        if (valor1 <= valor2)
            return true;

        return false;
    }

    public boolean maiorQue(double valor1, double valor2) {
        if (valor1 >= valor2)
            return true;

        return false;
    }

    public ProdutoCompleto filtra(ProdutoCompleto pCompleto) {

        Iterator<ProdutoPadrao> itP = pCompleto.produtos.iterator();
        Iterator<Formatacao> itF = pCompleto.formatos.iterator();

        ArrayList<ProdutoPadrao> produtosFiltrados = new ArrayList<>();
        ArrayList<Formatacao> formatosFiltrados = new ArrayList<>();

        ProdutoPadrao p;
        Formatacao f;

        while (itP.hasNext()) {
            f = itF.next();
            p = itP.next();

            if (this.maiorQue(p.getPreco(), this.valorMenor) && this.menorQue(p.getPreco(), this.valorMaior)) {
                produtosFiltrados.add(p);
                formatosFiltrados.add(f);
            }
        }

        pCompleto.produtos = produtosFiltrados;
        pCompleto.formatos = formatosFiltrados;

        return pCompleto;
    }
}