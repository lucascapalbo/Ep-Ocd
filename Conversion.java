public class Conversion {
    public static String toBin(int n){
        //falta declarar o array que será guardado o numero em binarios
        String[] binario= new String[]
        String num = n + "";
        for(int i = num.length-1; i>=0; i--){
            int resto = num.charAt(i).parseInt % 2;
            //falta terminar
        }
    }

    public static int max(int a, int b){
        if (a>b) return a;
        return b;
    }

    public static int min(int a, int b){
        if(a<b) return a;
        return b;
    }
}
