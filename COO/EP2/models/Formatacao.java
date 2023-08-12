package models;

public class Formatacao {
    private boolean ehNegrito;
    private boolean ehItalico;
    private String corLinha;

    public Formatacao(boolean ehNegrito, boolean ehItalico, String corLinha) {
        this.ehNegrito = ehNegrito;
        this.ehItalico = ehItalico;
        this.corLinha = corLinha;
    }

    public boolean getNegrito() {
        return this.ehNegrito;
    }

    public boolean getItalico() {
        return this.ehItalico;
    }

    public String getCor() {
        return this.corLinha;
    }

    public String formataParaImpressao() {
        return "NEGRITO: " + getNegrito() + " ITALICO: " + getItalico() + " COR: " + getCor();
    }
}