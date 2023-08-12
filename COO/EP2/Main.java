import java.io.*;

import algoritmos.*;
import criterios.*;
import filtros.*;
import interfaces.*;
import ordenacao.*;
import models.ProdutoCompleto;

public class Main {

    public static void main(String[] args) throws FileNotFoundException, IOException {

        if (args.length < 4) {

            System.out.println("Uso:");
            System.out.println("\tjava " + Main.class.getName()
                    + " <caminho do arquivo> <algoritmo> <criterio de ordenação> <criterio de filtragem> <parametro de filtragem>");
            System.out.println("Onde:");
            System.out.println("\tcaminho para o arquivo: o caminho completo do arquivo-fonte no seu sistema");
            System.out.println("\talgoritmo: 'quick' ou 'insertion'");
            System.out.println(
                    "\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c' ou'preco_d' ou 'descricao_d' ou 'estoque_d'");
            System.out.println(
                    "\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual' ou 'entre' ou 'substring'");
            System.out.println(
                    "\tparametro de filtragem: argumentos adicionais necessários para a filtragem. Para intervalo, usar a notação '10-15'");

            System.out.println();
            System.exit(1);
        }

        CarregaProdutos cProdutos = new CarregaProdutos(args[0]);
        ProdutoCompleto produtos = cProdutos.carregarProdutos();
        GeradorDeRelatorios gdr = new GeradorDeRelatorios();

        IAlgoritmo algoritmo;
        IOrdenacao ordem;
        ICriterio criterio;
        IFiltragem filtro;

        if (args[2].contains("preco")) {
            criterio = new Preco();
        } else if (args[2].contains("estoque")) {
            criterio = new QuantidadeEstoque();
        } else {
            criterio = new Descricao();
        }

        if (args[2].contains("_c")) {
            ordem = new Crescente(criterio);
        } else {
            ordem = new Decrescente(criterio);
        }

        if (args[3].contains("categoria_igual")) {
            filtro = new CategoriaIgual(args[4]);

        } else if (args[3].contains("estoque_menor_igual")) {
            filtro = new EstoqueMenorIgual(Integer.parseInt(args[4]));

        } else if (args[3].contains("entre")) {
            String[] valores = args[4].split("-");

            double valor1 = Double.parseDouble(valores[0]);
            double valor2 = Double.parseDouble(valores[1]);

            filtro = new Intervalo(valor1, valor2);
        } else if (args[3].contains("substring")) {
            filtro = new Substring(args[4]);
        } else {
            filtro = new Todos();
        }

        if (args[1] == "quick") {
            algoritmo = new QuickSort(ordem);
        } else {
            algoritmo = new InsertionSort(ordem);
        }

        algoritmo.ordena(0, produtos.produtos.size() - 1, produtos);

        ProdutoCompleto pCompletoFiltrado = filtro.filtra(produtos);

        gdr.gerarRelatorioOrdenado(pCompletoFiltrado, "saida.html", args[3]);
    }
}