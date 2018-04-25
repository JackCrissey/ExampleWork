public class StuffCarried {
    protected int boxcarID;
    protected String stuffID;
    protected String cargoType;

    /*public StuffCarried(int carID, String stuffID){
        boxcarID = carID;
        this.stuffID = stuffID;
    }*/

    public int getBoxcarID() {
        return boxcarID;
    }

    public void setBoxcarID(int boxcarID) {
        this.boxcarID = boxcarID;
    }

    public String getStuffID() {
        return stuffID;
    }

    public void setStuffID(String stuffID) {
        this.stuffID = stuffID;
    }

    public String getCargoType() {
        return cargoType;
    }

    public void setCargoType(String cargoType) {
        this.cargoType = cargoType;
    }
}
