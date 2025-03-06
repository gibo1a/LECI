import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import WordSoup;
import Direction;

public class WSGenerator {
    public static void main(String[] args){
        char randomLetter = (char) ('A' + random.nextInt(26));

        ArrayList<String> words = LoadWords(args[0]);
        char[][] WS = GenerateWS(words);
    }   
}