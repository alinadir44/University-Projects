
public class main{
    public static void main(String[] args){
        System.out.println("For rectangle:\n");
        
        IShape shape = new ARectangle(1.5, 1.5, 5.5, 4.9);
        System.out.println(shape.Area());
        System.out.println(shape.Parameter());
        System.out.println(shape.holds(2.5,2.5));
        System.out.println(shape.holds(new ARectangle(3, 5, 8.5, 3.5)));
        System.out.println(shape.holds(new ARectangle(3, 5, 2.3, 5.4)));
        
        
        System.out.println("\nFor circle:\n");
        shape = new ACircle(1.5, 1.5, 4.5);
        System.out.println(shape.Area());
        System.out.println(shape.Parameter());
        System.out.println(shape.holds(2.5,2.5));
        System.out.println(shape.holds(new ACircle(3, 5, 5.0)));
        System.out.println(shape.holds(new ACircle(3, 5, 5.0)));
        
        System.out.println("\nFor square:\n");
        shape = new ASquare(1.5, 1.5, 4.5);
        System.out.println(shape.Area());
        System.out.println(shape.Parameter());
        System.out.println(shape.holds(2.5,2.5));
        System.out.println(shape.holds(new ASquare(3, 5, 5.0)));
        System.out.println(shape.holds(new ASquare(3, 5, 5.0)));
    }
}