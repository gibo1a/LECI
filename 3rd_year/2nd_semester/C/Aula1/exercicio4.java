import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Scanner;

public class exercicio4 {
    public static void main(String args[]){
        HashMap<String,Integer> numbers = new HashMap<String,Integer>();

        try {
            File myObj = new File("numbers.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String[] line = myReader.nextLine().split("-");
                numbers.put(line[1].trim(), Integer.parseInt(line[0].trim()));
            }
            myReader.close();
        }catch(FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

        for(String arg : args){
            if(numbers.keySet().contains(arg)){
                System.out.print(numbers.get(arg) + " ");
            }else{
                System.out.print(arg + " ");
            }
        }
    }
}

