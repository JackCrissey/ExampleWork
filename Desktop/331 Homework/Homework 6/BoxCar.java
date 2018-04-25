import java.util.ArrayList;

public class BoxCar<T> {
    private ArrayList<T> cargo = new ArrayList<>();
    private int maxCapacity;
    private int carID;
    private String cargoType;

    public BoxCar(int capacity, String cargoType){
        maxCapacity = capacity;
        this.cargoType = cargoType;
    }

    public int getCarID() {
        return carID;
    }

    public void setCarID(int carID) {
        this.carID = carID;
    }

    public ArrayList<T> getCargo() {
        return cargo;
    }

    public void addCargo(T stuff){
        cargo.add(stuff);
    }

    public void removeCargo(int index) {
        cargo.remove(index);
    }

    public String getCargoType() {
        return cargoType;
    }

    public int getMaxCapacity() {
        return maxCapacity;
    }

    public void setMaxCapacity(int maxCapacity) {
        this.maxCapacity = maxCapacity;
    }


}
