public class Person extends StuffCarried{
    private String name;
    private int age;

    public Person(int boxcarID, String govID, String name, int age) {
        if(age >= 0) {
            this.boxcarID = boxcarID;
            this.stuffID = govID;
            this.name = name;
            this.age = age;
            cargoType = "person";
        } else {
            System.out.println("    Error:Age can't be less than 0");
        }
    }

    public String toString(){
        String info;
        info= "        Government Id: "+stuffID+", Name: "+name+", Age: "+age;
        return info;
    }

    public int getBoxcarID() {
        return boxcarID;
    }

    public void setBoxcarID(int boxcarID) {
        this.boxcarID = boxcarID;
    }

    public String getGovID() {
        return stuffID;
    }

    public void setGovID(String govID) {
        this.stuffID = govID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }
}
