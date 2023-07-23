import java.io.PrintWriter;
import java.io.IOException;

import java.util.*;

public class GeradorDeRelatorios {

	public static final String ALG_INSERTIONSORT = "quick";
	public static final String ALG_QUICKSORT = "insertion";

	public static final String CRIT_DESC_CRESC = "descricao_c";
	public static final String CRIT_PRECO_CRESC = "preco_c";
	public static final String CRIT_ESTOQUE_CRESC = "estoque_c";

	public static final String FILTRO_TODOS = "todos";
	public static final String FILTRO_ESTOQUE_MENOR_OU_IQUAL_A = "estoque_menor_igual";
	public static final String FILTRO_CATEGORIA_IGUAL_A = "categoria_igual";

	// operador bit a bit "ou" pode ser usado para combinar mais de
	// um estilo de formatacao simultaneamente (veja como no main)
	public static final int FORMATO_PADRAO = 0b0000;
	public static final int FORMATO_NEGRITO = 0b0001;
	public static final int FORMATO_ITALICO = 0b0010;

	private Produto[] produtos;
	private String algoritmo;
	private String criterio;
	private String filtro;
	private String argFiltro;
	private int format_flags;

	public GeradorDeRelatorios(Produto[] produtos, String algoritmo, String criterio, String filtro, String argFiltro,
			int format_flags) {

		this.produtos = new Produto[produtos.length];

		for (int i = 0; i < produtos.length; i++) {

			this.produtos[i] = produtos[i];
		}

		this.algoritmo = algoritmo;
		this.criterio = criterio;
		this.format_flags = format_flags;
		this.filtro = filtro;
		this.argFiltro = argFiltro;
	}

	public void debug() {

		System.out.println("Gerando relatório para array contendo " + produtos.length + " produto(s)");
		System.out.println("parametro filtro = '" + argFiltro + "'");
	}

	public void geraRelatorio(String arquivoSaida) throws IOException {

		debug();

		Ordenacao.ordena(0, produtos.length - 1, this.algoritmo, this.produtos, this.criterio);

		PrintWriter out = new PrintWriter(arquivoSaida);

		out.println("<!DOCTYPE html><html>");
		out.println("<head><title>Relatorio de produtos</title></head>");
		out.println("<body>");
		out.println("Relatorio de Produtos:");
		out.println("<ul>");

		int count = 0;

		for (int i = 0; i < produtos.length; i++) {

			Produto p = produtos[i];
			boolean selecionado = false;

			if (filtro.equals(FILTRO_TODOS)) {

				selecionado = true;
			} else if (filtro.equals(FILTRO_ESTOQUE_MENOR_OU_IQUAL_A)) {

				if (p.getQtdEstoque() <= Integer.parseInt(argFiltro))
					selecionado = true;
			} else if (filtro.equals(FILTRO_CATEGORIA_IGUAL_A)) {

				if (p.getCategoria().equalsIgnoreCase(argFiltro))
					selecionado = true;
			} else {
				throw new RuntimeException("Filtro invalido!");
			}

			if (selecionado) {

				out.print("<li>");

				if ((format_flags & FORMATO_ITALICO) > 0) {

					out.print("<span style=\"font-style:italic\">");
				}

				if ((format_flags & FORMATO_NEGRITO) > 0) {

					out.print("<span style=\"font-weight:bold\">");
				}

				out.print(p.formataParaImpressao());

				if ((format_flags & FORMATO_NEGRITO) > 0) {

					out.print("</span>");
				}

				if ((format_flags & FORMATO_ITALICO) > 0) {

					out.print("</span>");
				}

				out.println("</li>");
				count++;
			}
		}

		out.println("</ul>");
		out.println(count + " produtos listados, de um total de " + produtos.length + ".");
		out.println("</body>");
		out.println("</html>");

		out.close();
	}

	public static Produto[] carregaProdutos() {

		return new Produto[] {

				new ProdutoPadrao(1, "O Hobbit", "Livros", 2, 34.90),
				new ProdutoPadrao(2, "Notebook Core i7", "Informatica", 5, 1999.90),
				new ProdutoPadrao(3, "Resident Evil 4", "Games", 7, 79.90),
				new ProdutoPadrao(4, "iPhone", "Telefonia", 8, 4999.90),
				new ProdutoPadrao(5, "Calculo I", "Livros", 20, 55.00),
				new ProdutoPadrao(6, "Power Glove", "Games", 3, 499.90),
				new ProdutoPadrao(7, "Microsoft HoloLens", "Informatica", 1, 19900.00),
				new ProdutoPadrao(8, "OpenGL Programming Guide", "Livros", 4, 89.90),
				new ProdutoPadrao(9, "Vectrex", "Games", 1, 799.90),
				new ProdutoPadrao(10, "Carregador iPhone", "Telefonia", 15, 499.90),
				new ProdutoPadrao(11, "Introduction to Algorithms", "Livros", 7, 315.00),
				new ProdutoPadrao(12, "Daytona USA (Arcade)", "Games", 1, 12000.00),
				new ProdutoPadrao(13, "Neuromancer", "Livros", 5, 45.00),
				new ProdutoPadrao(14, "Nokia 3100", "Telefonia", 4, 249.99),
				new ProdutoPadrao(15, "Oculus Rift", "Games", 1, 3600.00),
				new ProdutoPadrao(16, "Trackball Logitech", "Informatica", 1, 250.00),
				new ProdutoPadrao(17, "After Burner II (Arcade)", "Games", 2, 8900.0),
				new ProdutoPadrao(18, "Assembly for Dummies", "Livros", 30, 129.90),
				new ProdutoPadrao(19, "iPhone (usado)", "Telefonia", 3, 3999.90),
				new ProdutoPadrao(20, "Game Programming Patterns", "Livros", 1, 299.90),
				new ProdutoPadrao(21, "Playstation 2", "Games", 10, 499.90),
				new ProdutoPadrao(22, "Carregador Nokia", "Telefonia", 14, 89.00),
				new ProdutoPadrao(23, "Placa Aceleradora Voodoo 2", "Informatica", 4, 189.00),
				new ProdutoPadrao(24, "Stunts", "Games", 3, 19.90),
				new ProdutoPadrao(25, "Carregador Generico", "Telefonia", 9, 30.00),
				new ProdutoPadrao(26, "Monitor VGA 14 polegadas", "Informatica", 2, 199.90),
				new ProdutoPadrao(27, "Nokia N-Gage", "Telefonia", 9, 699.00),
				new ProdutoPadrao(28, "Disquetes Maxell 5.25 polegadas (caixa com 10 unidades)", "Informatica", 23,
						49.00),
				new ProdutoPadrao(29, "Alone in The Dark", "Games", 11, 59.00),
				new ProdutoPadrao(30, "The Art of Computer Programming Vol. 1", "Livros", 3, 240.00),
				new ProdutoPadrao(31, "The Art of Computer Programming Vol. 2", "Livros", 2, 200.00),
				new ProdutoPadrao(32, "The Art of Computer Programming Vol. 3", "Livros", 4, 270.00)
		};
	}
}
