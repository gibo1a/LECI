import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class exercicio2 {
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        System.out.println("Introduce mathematic operation");
        System.out.println("Write exit to end");
        ArrayList<String> equation = new ArrayList<String>();
        HashMap<String,Float> variables = new HashMap<String,Float>();
        while(true){
            String line = sc.nextLine();
            if(line.equals("exit")){
                break;
            }
            equation.add(line);
        }

        System.out.println(equation);

        String regex = "[\\s\\n]";

        for(String eq : equation){
            String[] operands = new String[3];
            if(eq.contains("=")){
                operands = eq.split("=");
                System.out.println(operands[1]);
                System.out.println(operands[1]);
                if(!(operands[1].contains("+") || operands[1].contains("-") || operands[1].contains("*") || operands[1].contains("/"))){
                    if(variables.keySet().contains(operands[0])){
                        variables.replace(operands[0],Float.parseFloat(operands[1]));
                    }else{
                        variables.put(operands[0],Float.parseFloat(operands[1]));
                    }
                    System.out.println(variables.get(operands[0]));
                }else{
                    String[] math = operands[1].split(regex);
                    //System.out.println(math[1]);
                    switch (math[1]) {
                        case "+":
                            variables.replace(operands[0],Float.parseFloat(math[0]) + Float.parseFloat(math[2]));
                            break;
                        case "-":
                            variables.replace(operands[0],Float.parseFloat(math[0]) - Float.parseFloat(math[2]));
                            break;
                        case "/":
                            variables.replace(operands[0],Float.parseFloat(math[0]) / Float.parseFloat(math[2]));
                            break;           
                        case "*":
                            variables.replace(operands[0],Float.parseFloat(math[0]) * Float.parseFloat(math[2]));
                            break;
                        default:
                            System.err.println("Invalid operand");
                            break;
                    }
                }
            }else{
                operands = eq.split(regex);
            }

            /*switch (operands[1]) {
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
            }*/
        }
        sc.close();
    }  
}
