import java.io.File;
import java.io.FileNotFoundException;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class exercicio6 {
    public static void main(String[] args){
        Map<String,String> dic1 = new HashMap<String,String>();
        Map<String,String> dic2 = new HashMap<String,String>();

        try {
            File myObj = new File("dic2.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                String[] line = myReader.nextLine().split("\\s{2,}");
                dic1.put(line[0],line[1]);
            }
            myReader.close();
        }catch(FileNotFoundException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }

            try {
                File myObj = new File("dic1.txt");
                Scanner myReader = new Scanner(myObj);
                while (myReader.hasNextLine()) {
                    String[] line = myReader.nextLine().split(" ");
                    dic1.put(line[0],line[1]);
                }
                myReader.close();
            }catch(FileNotFoundException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }

            for(String arg : args){
                if(dic1.keySet().contains(arg)){
                    System.out.print(dic1.get(arg) + " ");
                }else{
                    System.out.print(arg + " ");
                }
            }
    }
}
