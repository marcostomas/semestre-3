class Principal {

	public static void main(String [] args){

		A a = new A();
		B b = new B();

		System.out.println("--------------------------------------");

		System.out.println("a.valor = " + a.valor);
		System.out.println("b.valor = " + b.valor);

		a.valor++;
		b.valor--;

		System.out.println("--------------------------------------");

		System.out.println("a.valor = " + a.valor);
		System.out.println("b.valor = " + b.valor);
	}
}
