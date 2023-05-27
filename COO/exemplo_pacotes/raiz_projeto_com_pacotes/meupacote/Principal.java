package meupacote;

import meupacote.moduloA.A;
import meupacote.moduloB.B;
import meupacote.moduloB.X;

/*
import meupacote.moduloA.*;
import meupacote.moduloB.*;
*/

class Principal {

	public static void main(String [] args){

		A a = new A();
		B b = new B();
		X x = new X();		
		//meupacote.moduloA.X x = new meupacote.moduloA.X();

		System.out.println("--------------------------------------");

		System.out.println("a.valor = " + a.valor);
		System.out.println("b.valor = " + b.valor);
		System.out.println("x.valor = " + x.valor);

		a.valor++;
		b.valor--;
		x.valor *= 2;

		System.out.println("--------------------------------------");

		System.out.println("a.valor = " + a.valor);
		System.out.println("b.valor = " + b.valor);
		System.out.println("x.valor = " + x.valor);
	}
}
