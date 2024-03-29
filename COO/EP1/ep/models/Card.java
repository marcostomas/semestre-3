package ep.models;

import ep.Color;

/**
 * Classe que contém informações das cartas
 */
public class Card {
    private String name;
    private Color color;
    private Position[] positions;

    /**
     * Construtor que define os principais atributos de uma cara
     * 
     * @param name      Nome da carta
     * @param color     Cor da carta
     * @param positions Todas as posições relativas de movimento
     */
    public Card(String name, Color color, Position[] positions) {
        this.name = name;
        this.color = color;
        this.positions = positions;
    }

    /**
     * Método que devolve o nome da carta
     * 
     * @return String que contém o nome da carta
     */
    public String getName() {
        return this.name;
    }

    /**
     * Método que devolve a cor da carta
     * 
     * @return Enum Color que contém a cor da carta
     */
    public Color getColor() {
        return this.color;
    }

    /**
     * Método que devolve todas as possíveis posições relativas de movimento.
     * A posição atual da peça é o ponto de origem (0,0). Uma carta possui as
     * possíveis posições de movimento em relação ao ponto de origem.
     * 
     * @return Um array de Position contendo todas as possíveis posições de
     *         movimento em relação ao ponto de origem
     */
    public Position[] getPositions() {
        return this.positions;
    }

    /**
     * Método que cria todas as cartas do jogo, embaralha-as e devolve as 5 que
     * serão utilizadas na partida.
     * 
     * @return Vetor de cartas com todas as cartas do jogo
     */
    public static Card[] createCards() {
        Color[] colors = Color.values();
    	Position[] positions = {new Position(1, 0), new Position(0, 1), new position(-1, 0), new Position (0, -1)};
    	String[] names = {"TIGER", "DRAGON", "FROG", "RABBIT", "CRAB", "ELEPHANT", "GOOSE", "ROOSTER"};
    	
    	Card[] cards = new Card[5];
    	
    	for(int i = 0; i < 5; i++){
    		int indiceCorAleatoria = (int) (Math.random() * colors.lenght);
    		Color corAleatoria = colors[indiceCorAleatoria];
    		
    		Card card = new Card(names[i], corAleatoria, positions);
    		cards[i] = card;
    	}
    	
        return cards;
    }
}
