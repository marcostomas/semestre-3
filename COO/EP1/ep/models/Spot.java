package ep.models;

import ep.Color;
import ep.exceptions.*;

/**
 * Classe contendo ações e informações sobre cada espaço (quadrado) no tabuleiro
 */
public class Spot {
    private Piece piece;
    private Position pos;
    private Color color;

    /**
     * Construtor para espaços com peça e com cor
     * 
     * @param piece Peça que inicia nesse espaço do tabuleiro
     * @param pos   Posição do espaço no tabuleiro
     * @param color Cor do espaço no tabuleiro (Templo)
     */
    public Spot(Piece piece, Position pos, Color color) {
        this.color = color;
        this.piece = piece;
        this.pos = pos;
    }

    /**
     * Construtor para espaços com peça e sem cor
     * 
     * @param piece Peça que inicia nesse espaço do tabuleiro
     * @param pos   Posição do espaço no tabuleiro
     */
    public Spot(Piece piece, Position pos) {
        this.piece = piece;
        this.pos = pos;
        this.color = Color.NONE;
    }

    /**
     * Construtor para espaços sem peça e sem cor
     * 
     * @param pos Posição do espaço no tabuleiro
     */
    public Spot(Position pos) {
        this.pos = pos;
        this.color = Color.NONE;
        this.piece = null;
    }

    /**
     * Método que devolve a posição (coordenadas) do espaço
     * 
     * @return Objeto Position contendo a posição (coordenadas) do espaço
     */
    public Position getPosition() {
        return this.pos;
    }

    /**
     * Método que devolve a peça contida neste espaço
     * 
     * @return Objeto Piece caso tenha uma peça ou null caso o espaço esteja vazio
     */
    public Piece getPiece() {
        return this.piece;
    }

    /**
     * Método que devolve a cor do espaço
     * 
     * @return Enum Color com a cor do espaço. Caso o espaço não tenha cor, o valor
     *         do enum será NONE
     */
    Color getColor() {
        return this.color;
    }

    /**
     * Método que verifica se a posição é válida no tabuleiro
     * 
     * @return Um booleano que indica se o objeto representa uma posição válida no
     *         tabuleiro
     */
    public boolean isValid() {

        int row = pos.getRow();
        int col = pos.getCol();

        // checando se os valores estão dentro da faixa
        boolean isValidRow = row >= 0 && row < 5;
        boolean isValidCol = col >= 0 && col < 5;

        return isValidRow && isValidCol;
    }

    /**
     * Método que ocupa o espaço atual com a peça passada
     * 
     * @param piece A peça para ocupar este espaço
     * @exception IllegalMovementException Caso o espaço já esteja ocupado por uma
     *                                     peça da mesma cor
     */
    protected void occupySpot(Piece piece) throws IllegalMovementException {

        if (this.piece != null && this.piece.getColor() == piece.getColor()) {
            throw new IllegalMovementException("Lugar já ocupado por peça da mesma cor");
        }

        this.piece = piece;

    }

    /**
     * Método que "libera" o espaço atual, ou seja, deixa-o vazio
     */
    protected void releaseSpot() {
        this.piece = null;
    }
}