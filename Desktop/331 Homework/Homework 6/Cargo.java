public class Cargo extends StuffCarried{
    private int weight;
    private int height;

    public Cargo(int boxcarID, String cargoID, int weight, int height){
        if(weight > 0 ){
            if(height > 0){
                this.boxcarID = boxcarID;
                this.stuffID = cargoID;
                this.weight = weight;
                this.height = height;
                this.cargoType = "cargo";
            }else{
                System.out.println("    Error:The height can not be negative");
            }
        }else {
            System.out.println("    Error: The weight can not be negative");
        }
    }

    public String toString(){
        String info;
        info= "        Cargo Id: "+stuffID+", Weight: "+weight+", Height: "+height;
        return info;
    }

    public int getBoxcarID() {
        return boxcarID;
    }

    public void setBoxcarID(int boxcarID) {
        this.boxcarID = boxcarID;
    }

    public String getCargoID() {
        return stuffID;
    }

    public void setCargoID(String cargoID) {
        this.stuffID = cargoID;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getHeight() {
        return height;
    }

    public void setHeight(int height) {
        this.height = height;
    }
}
