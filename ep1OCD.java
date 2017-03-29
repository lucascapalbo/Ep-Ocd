import java.util.Scanner;

public class ep1OCD {
	public static String numero1, numero2;
	public int[] binario1,binario2;
	public static void main(String[] args) {
		ep1OCD ep = new ep1OCD();
		Scanner scan = new Scanner(System.in);
		System.out.println("insira o numero em binario, separado por espacos");
		numero1 = scan.nextLine();
		System.out.println("insira o numero em binario, separado por espacos");
		numero2 = scan.nextLine();
		ep.recebeNumero(4);
		for (int i = 0; i < 4; i++) {
			System.out.println(ep.binario1[i] + " " + ep.binario2[i] + "   " + ep.somaBinarios(ep.binario1, ep.binario2)[i]);
		}
		
	}
	
	void recebeNumero(int bits) {
		String conversao1[] = numero1.split(" ");
		String conversao2[] = numero2.split(" ");
		binario1 = new int[bits];
		binario2 = new int [bits];
		for(int i = 0 ; i < bits; i++){
			binario1[i] = Integer.parseInt(conversao1[i]);
			binario2[i] = Integer.parseInt(conversao2[i]);
		}
	}
	
	int[] somaBinarios(int[] bin1, int[] bin2){
		int[] resultado = new int[bin1.length];
		int aux;
		for(int i = bin1.length -1; i > 0; i--){
			resultado[i] += bin1[i] + bin2[i];
			if(resultado[i] >= 2){
				resultado[i-1] = resultado[i]/2;
				aux = resultado[i];
				resultado[i] = aux%2;
			}
		}
		return resultado;
	}
}
