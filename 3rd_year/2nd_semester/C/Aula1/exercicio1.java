import java.util.Scanner;

public class exercicio1{
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Introduce mathematic operation");

        String operation = sc.nextLine();

        String regex = "[\\s\\n]";

        String[] operands = operation.split(regex);
        System.out.println(operands);

        switch (operands[1]) {
            case "+":
                System.out.println(Float.parseFloat(operands[0]) + Float.parseFloat(operands[2]));
                break;
            case "-":
                System.out.println(Float.parseFloat(operands[0]) - Float.parseFloat(operands[2]));
                break;
            case "/":
                System.out.println(Float.parseFloat(operands[0]) / Float.parseFloat(operands[2]));
                break;           
            case "*":
                System.out.println(Float.parseFloat(operands[0]) * Float.parseFloat(operands[2]));
                break;
            default:
                System.err.println("Invalid operand");
                break;
        }
        sc.close();

    }
}