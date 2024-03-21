
public class main{
    public static void main(String[] args){
        ARectangle rect01 = new ARectangle(1.5, 1.5, 5.5, 4.9);
        System.out.println(rect01.Area());
        System.out.println(rect01.Parameter());
        System.out.println(rect01.holds(2.5,2.5));
        System.out.println(rect01.holds(new ARectangle(3, 5, 8.5, 3.5)));
        System.out.println(rect01.holds(new ARectangle(3, 5, 2.3, 5.4)));
    }
}