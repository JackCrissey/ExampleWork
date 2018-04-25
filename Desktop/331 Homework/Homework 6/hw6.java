import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class hw6 {
    public static void main(String[] args){
        Scanner input;
        Train train;
        try {
            FileInputStream stream = new FileInputStream("train_commands.txt");
            input = new Scanner(stream);
            train = new Train("New York", 10, 50, 3);
            while(input.hasNextLine()){
                String line = input.nextLine();
                switch(line){
                    case "PRINT":
                        train.print();
                        break;
                    case "ARRIVE":
                        train.arrive();
                        break;
                    case "DEPART":
                        String destination = input.nextLine();
                        train.depart(destination);
                        break;
                    case "SPEEDUP":
                        int speed = Integer.parseInt(input.nextLine());
                        train.speedUp(speed);
                        break;
                    case "SLOWDOWN":
                        int speed2 = Integer.parseInt(input.nextLine());
                        train.slowDown(speed2);
                        break;
                    case "ADDCAR":
                        String type = input.nextLine();
                        int cap = Integer.parseInt(input.nextLine());
                        train.addCar(type, cap);
                        break;
                    case "REMOVECAR":
                        int carNumber = Integer.parseInt(input.nextLine());
                        train.removeCar(carNumber);
                        break;
                    case "QUIT":
                        System.out.println("QUIT\nQuitting...");
                        break;
                    case "LOAD":
                        String kind = input.nextLine();
                        int carNum = Integer.parseInt(input.nextLine());
                        String id = input.nextLine();
                        if(kind.toLowerCase().equals("person")){
                            String name = input.nextLine();
                            int age = Integer.parseInt(input.nextLine());
                            Person person = new Person(carNum, id, name, age);
                            train.load(person);
                        } else if(kind.toLowerCase().equals("cargo")){
                            int weight = Integer.parseInt(input.nextLine());
                            int height = Integer.parseInt(input.nextLine());
                            Cargo cargo = new Cargo(carNum, id, weight, height);
                            train.load(cargo);
                        }
                        break;
                    case "UNLOAD":
                        int car = Integer.parseInt(input.nextLine());
                        String itemId = input.nextLine();
                        train.unload(car, itemId);
                        break;
                }
            }
        }
        catch(FileNotFoundException stream)
        {
            System.err.println("Could not find file train_commands.txt");
        }
    }
}
