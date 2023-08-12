import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import models.Formatacao;
import models.ProdutoCompleto;
import models.ProdutoPadrao;

public class CarregaProdutos {

    String path;
    String divider = ", ";

    public CarregaProdutos(String pathToFile) {
        this.path = pathToFile;
    }

    public CarregaProdutos(String pathToFile, String divider) {
        this.path = pathToFile;
        this.divider = divider;
    }

    public ProdutoCompleto carregarProdutos() {
        ProdutoCompleto pCompleto = new ProdutoCompleto();

        try (BufferedReader br = new BufferedReader(new FileReader(this.path))) {
            String line = br.readLine();
            line = br.readLine();// Para pular a primeira linha do arquivo, que contém os cabeçalhos

            while (line != null) {
                String dadosProduto[] = line.split(this.divider);

                int id = Integer.parseInt(dadosProduto[0]);
                int qtdEstoque = Integer.parseInt(dadosProduto[3]);
                double preco = Double.parseDouble(dadosProduto[4]);
                ProdutoPadrao produto = new ProdutoPadrao(id, dadosProduto[1], dadosProduto[2], qtdEstoque, preco);

                boolean ehNegrito = Boolean.parseBoolean(dadosProduto[5]);
                boolean ehItalico = Boolean.parseBoolean(dadosProduto[6]);
                Formatacao formato = new Formatacao(ehNegrito, ehItalico, dadosProduto[7]);

                pCompleto.adiciona(produto, formato);

                line = br.readLine();
            }
        } catch (IOException e) {
            e.getMessage();
        }

        return pCompleto;
    }
}
