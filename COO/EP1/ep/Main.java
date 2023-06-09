package ep;

import ep.exceptions.*;
import ep.interfaces.*;
import ep.models.*;

public class Main implements Game {

    public Color getSpotColor(Position position) {
        return Color.RED;
        // Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public Piece getPiece(Position position) {
        return new Piece(null, false);
        // Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public Card getTableCard() {
        return new Card(null, null, null);
        // Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public Player getRedPlayer() {
        return new Player(null, null, getTableCard(), getTableCard());
        // Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public Player getBluePlayer() {
        return new Player(null, null, getTableCard(), getTableCard());
        // Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public boolean checkVictory(Color color) {
        return true;// Falta implementar corretamente. Coloquei apenas para tirar o erro.
    }

    public void printBoard() {

    }

    public void makeMove(Piece piece, Card card, Position position)
            throws IncorrectTurnOrderException, IllegalMovementException, InvalidCardException, InvalidPieceException {

    }

    public static void main(String[] args) {
        System.out.println("Olá, mundo! Agora estou vivo!");
    }

}