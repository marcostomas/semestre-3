package ep;

import ep.exceptions.*;
import ep.interfaces.*;
import ep.models.*;

public class GameImpl implements Game {

    public Color getSpotColor(Position position) {
        int row = position.getRow();

        if (row == 0)
            return Color.BLUE;
        else if (row == 4)
            return Color.RED;
        else
            return Color.NONE;
    }

    public Piece getPiece(Position position) {
        position.
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
}