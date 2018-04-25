import java.util.ArrayList;

public class Train {
    private ArrayList<BoxCar> cars;
    private String origin;
    private int minSpeed;
    private int maxSpeed;
    private int maxCars;
    private int speed;
    private boolean inTransit;
    private String destination;

    public Train(String orig, int minS, int maxS, int maxNumCars){
        origin = orig;
        minSpeed = minS;
        maxSpeed = maxS;
        maxCars = maxNumCars;
        speed = 0;
        inTransit = false;
        cars = new ArrayList<>();
    }

    public void print(){
        System.out.println("PRINT");
        System.out.println("Train Status");
        System.out.println("------------");
        System.out.println("    Current Speed: "+speed);
        System.out.println("    Minimum Speed: "+minSpeed);
        System.out.println("    Maximum Speed: "+maxSpeed);
        if(inTransit){
            System.out.println("    Current Position: The train is in transit from "+origin+" to "+destination);
        } else {
            System.out.println("    Current Position: The train is stopped in "+origin);
        }
        System.out.println("    Current Number of Boxcars: "+cars.size());
        System.out.println("    Maximum Number of Boxcars: "+maxCars);
        for(int i = 0; i < cars.size();i++){
            BoxCar car = cars.get(i);
            System.out.println("    Boxcar: "+i);
            System.out.println("    ----------");
            System.out.println("    Contents:");
            ArrayList cargo = car.getCargo();
            for(int k = 0; k < cargo.size(); k++){
                System.out.println(cargo.get(k).toString());
            }
        }
        System.out.println("");
    }

    public void speedUp(int speedIn){
        System.out.println("SPEEDUP "+speedIn);
        if(inTransit) {
            if(maxSpeed >= speed + speedIn){
                speed = speed + speedIn;
            } else {
                System.out.println("    Error: You are trying to increase the speed past the maximum allowed speed");
            }
        } else {
            System.out.println("    Error: The train is not traveling. Speed can't be changed.");
        }
    }

    public void slowDown(int speedDec){
        System.out.println("SLOWDOWN "+speedDec);
        if(inTransit) {
            if (minSpeed <= speed - speedDec) {
                speed = speed - speedDec;
            } else {
                System.out.println("    Error: You are trying to decrease the speed past the minimum allowed speed.");
            }
        } else {
            System.out.println("    Error: The train is not traveling. Speed can't be changed.");
        }
    }

    public void addCar(String cargo, int maxCap){
        System.out.println("ADDCAR " + cargo + " " + maxCap);
        if(!inTransit) {
            if (maxCars >= cars.size()){
                BoxCar boxCar = new BoxCar(maxCap, cargo);
                cars.add(boxCar);
                boxCar.setCarID(cars.size());
            } else {
                System.out.println("    Error: The trains capacity is maxed out and cars can not be added.");
            }
        } else {
            System.out.println("    Error: Train is in transit and can not have cars added to it at this moment.");
        }
    }

    public void removeCar(int boxcarID){
        System.out.println("REMOVECAR " + boxcarID);
        if(!inTransit) {
            if(cars.size() > 0) {
                if(boxcarID < cars.size()) {
                    if(cars.get(boxcarID).getCargo().size() == 0) {
                        for (int i = boxcarID + 1; i < cars.size(); i++) {
                            cars.get(i).setCarID(cars.get(i).getCarID() - 1);
                        }
                        cars.remove(boxcarID);
                    }else{
                        System.out.println("    Error: Boxcar is not empty");
                    }
                } else {
                    System.out.println("    Error: The car you are trying to remove doesn't exist");
                }
            }else{
                System.out.println("    Error: The train has no cars, so none can be removed.");
            }
        }else{
            System.out.println("    Error: Train is in transit and can not have cars removed from it at this moment.");
        }
    }

    public void depart(String dest){
        System.out.println("DEPART "+dest);
        if(!dest.equals(origin)){
            if(!inTransit) {
                inTransit = true;
                destination = dest;
                speed = minSpeed;
            }else {
                System.out.println("    Error: The train is already in transit.");
            }
        } else {
            System.out.println("    Error: You can't send a train to is origin");
        }
    }

    public void arrive(){
        System.out.println("ARRIVED in "+destination);
        if(inTransit) {
            inTransit = false;
            origin = destination;
            speed = 0;
        } else {
            System.out.println("    Error: Train has already arrived.");
        }
    }

    public void load(StuffCarried stuff){
        System.out.println("Load: " + stuff.toString());
        BoxCar car = cars.get(stuff.getBoxcarID());
        if(car.getCargoType().toLowerCase().equals(stuff.getCargoType().toLowerCase())) {
            if (car.getMaxCapacity() >= car.getCargo().size()+1) {
                Boolean idExists = false;
                for (int i = 0; i < cars.size(); i++) {
                    BoxCar<StuffCarried> curCar = cars.get(i);
                    if(curCar.getCargoType().toLowerCase().equals(stuff.getCargoType().toLowerCase()))
                    {
                        for(int k = 0; k < curCar.getCargo().size(); k++){
                            if (curCar.getCargo().get(k).getStuffID().equals(stuff.getStuffID())) {
                                idExists = true;
                            }
                        }
                    }
                }
                if (!idExists) {
                    car.addCargo(stuff);
                } else {
                    System.out.println("    Error: ID already exists");
                }
            } else {
                System.out.println("    Error: Boxcar has reached its capacity");
            }
        }else{
            System.out.println("    Error: You can't put "+stuff.getCargoType()+" into a Boxcar of "+car.getCargoType());
        }
    }

    public void unload(int carId, String cargoId){
        System.out.println("UNLOAD "+carId+" "+cargoId );
        if(cars.size() != 0){
            if(carId < cars.size()){
                BoxCar<StuffCarried> car = cars.get(carId);
                if(car.getCargo().size()!=0){
                    boolean cargoExists = false;
                    for(int i = 0; i < car.getCargo().size(); i++){
                        if(car.getCargo().get(i).getStuffID().equals(cargoId)){
                            cargoExists = true;
                            car.removeCargo(i);
                        }

                    }
                    if(!cargoExists){
                        System.out.println("    Error: Invalid item id, item not found");
                    }
                }else{
                    System.out.println("    Error: There is nothing in the boxcar to unload.");
                }
            }else{
                System.out.println("    Error: The car that you are trying to unload doesnt exist.");
            }
        } else {
            System.out.println("    Error: There are no boxcars to unload from.");
        }
    }

    public String getOrigin() {
        return origin;
    }

    public void setOrigin(String origin) {
        this.origin = origin;
    }

    public int getMinSpeed() {
        return minSpeed;
    }

    public void setMinSpeed(int minSpeed) {
        this.minSpeed = minSpeed;
    }

    public int getMaxSpeed() {
        return maxSpeed;
    }

    public void setMaxSpeed(int maxSpeed) {
        this.maxSpeed = maxSpeed;
    }

    public int getMaxCars() {
        return maxCars;
    }

    public void setMaxCars(int maxCars) {
        this.maxCars = maxCars;
    }

    public ArrayList<BoxCar> getCars() {
        return cars;
    }
}

