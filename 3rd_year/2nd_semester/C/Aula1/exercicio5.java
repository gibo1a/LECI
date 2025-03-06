import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class exercicio5 {
    public static void main(String[] args){
        HashMap<String,Integer> numbers = new HashMap<String,Integer>();

            try {
                File myObj = new File("numbers.txt");
                Scanner myReader = new Scanner(myObj);
                while (myReader.hasNextLine()) {
                    String[] line = myReader.nextLine().split(" - ");
                    numbers.put(line[1], Integer.parseInt(line[0]));
                }
                myReader.close();
            }catch(FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }

            ArrayList<Integer> operands = new ArrayList<Integer>();
            
            for(String arg : args){
                if(arg.contains("-")){
                    String[] parsedargs = arg.split("-");
                    for(String parg:parsedargs){
                        if(numbers.keySet().contains(parg)){
                            operands.add(numbers.get(parg));
                        }else{
                            try{
                                operands.add(Integer.parseInt(parg));
                            }catch(Exception e){
                                continue;
                            }
                        }
                    }

                }

                if(numbers.keySet().contains(arg)){
                    operands.add(numbers.get(arg));
                }else{
                    try{
                        operands.add(Integer.parseInt(arg));
                    }catch(Exception e){
                        continue;
                    }
                }
            }

            int final_sum = 0;
            int last_number = 0;

            for(int i = 0;i < operands.size();i++){
                if(operands.get(i) > last_number && last_number != 0){
                    last_number *= operands.get(i);
                }else if(operands.get(i) <= last_number){
                    final_sum += last_number;
                    last_number = operands.get(i);
                }else{
                    last_number = operands.get(i);
                }
            }
            final_sum += last_number;

            System.out.println(final_sum);
    }

}
