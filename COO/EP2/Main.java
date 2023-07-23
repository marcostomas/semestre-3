import java.io.IOException;

public class Main {
    public static void main(String[] args) {

        if (args.length < 4) {

            System.out.println("Uso:");
            System.out.println("\tjava " + GeradorDeRelatorios.class.getName()
                    + " <algoritmo> <critério de ordenação> <critério de filtragem> <parâmetro de filtragem> <opções de formatação>");
            System.out.println("Onde:");
            System.out.println("\talgoritmo: 'quick' ou 'insertion'");
            System.out.println("\tcriterio de ordenação: 'preco_c' ou 'descricao_c' ou 'estoque_c'");
            System.out.println("\tcriterio de filtragem: 'todos' ou 'estoque_menor_igual' ou 'categoria_igual'");
            System.out.println("\tparâmetro de filtragem: argumentos adicionais necessários para a filtragem");
            System.out.println("\topções de formatação: 'negrito' e/ou 'italico'");
            System.out.println();
            System.exit(1);
        }

        String opcao_algoritmo = args[0];
        String opcao_criterio_ord = args[1];
        String opcao_criterio_filtro = args[2];
        String opcao_parametro_filtro = args[3];

        String[] opcoes_formatacao = new String[2];
        opcoes_formatacao[0] = args.length > 4 ? args[4] : null;
        opcoes_formatacao[1] = args.length > 5 ? args[5] : null;
        int formato = GeradorDeRelatorios.FORMATO_PADRAO;

        for (int i = 0; i < opcoes_formatacao.length; i++) {

            String op = opcoes_formatacao[i];
            formato |= (op != null
                    ? op.equals("negrito") ? GeradorDeRelatorios.FORMATO_NEGRITO
                            : (op.equals("italico") ? GeradorDeRelatorios.FORMATO_ITALICO : 0)
                    : 0);
        }

        GeradorDeRelatorios gdr = new GeradorDeRelatorios(GeradorDeRelatorios.carregaProdutos(),
                opcao_algoritmo,
                opcao_criterio_ord,
                opcao_criterio_filtro,
                opcao_parametro_filtro,
                formato);

        try {
            gdr.geraRelatorio("saida.html");
        } catch (IOException e) {

            e.printStackTrace();
        }
    }
}
