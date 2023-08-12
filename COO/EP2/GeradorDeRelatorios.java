import java.io.PrintWriter;
import java.util.*;

import interfaces.IGeradorDeRelatorios;
import models.*;

public class GeradorDeRelatorios implements IGeradorDeRelatorios {
	public void debug(int total, String argFiltro) {

		System.out.println("Gerando relatório para array contendo " + total + " produto(s)");
		System.out.println("parametro filtro = '" + argFiltro + "'");
	}

	public void gerarRelatorioOrdenado(ProdutoCompleto pCompleto, String arquivoSaida, String argFiltro) {
		debug(pCompleto.produtos.size(), argFiltro);

		try (PrintWriter out = new PrintWriter(arquivoSaida)) {
			out.println("<!DOCTYPE html><html>");
			out.println("<head><title>Relatório de produtos</title></head>");
			out.println("<body>");
			out.println("Relatório de Produtos:");
			out.println("<ul>");

			int count = 0;
			Iterator<ProdutoPadrao> itP = pCompleto.produtos.iterator();
			Iterator<Formatacao> itF = pCompleto.formatos.iterator();

			while (itP.hasNext() && itF.hasNext()) {
				ProdutoPadrao proxP = itP.next();
				Formatacao proxF = itF.next();

				out.print("<li>");
				if (proxF.getItalico() && proxF.getNegrito())
					out.print(
							"<span style=\"font-style:italic;font-weight:bold;color:" + proxF.getCor()
									+ "\">");

				else if (proxF.getItalico())
					out.print("<span style=\"font-style:italic;color:" + proxF.getCor() + "\">");

				else if (proxF.getNegrito())
					out.print("<span style=\"font-weight:bold;color:" + proxF.getCor() + "\">");
				else
					out.print("<span style=\"color: " + proxF.getCor() + "\">");

				out.print(proxP.formataParaImpressao());
				out.print("</span>");

				out.println("</li>");
				count++;
			}

			out.println("</ul>");
			out.println(count + " produtos listados, de um total de " + pCompleto.produtos.size() + ".");
			out.println("</body>");
			out.println("</html>");

			out.close();
		} catch (Exception e) {
			System.out.println("ERRRO NO ARQUIVO DE SAIDA" + e.getMessage());
		}
	}
}
