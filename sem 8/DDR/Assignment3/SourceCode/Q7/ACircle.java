

public class ACircle implements IShape {
    private float ptX;
    private float ptY;
    private float radius;
    
    public ACircle(){
        this.ptX = 0;
        this.ptY = 0;
        this.radius = 1;
    }
    
    public ACircle(float ptX, float ptY, float radius){
        this.ptX = ptX;
        this.ptY =ptY;
        this.radius = radius;
    }
    
    @Override
    public float Area(){
        return 3.142*radius*radius;
    }
    
    @Override
    public float Parameter(){
        return 2*3.142*radius;
    }
    
    public float getX(){
        return ptX;
    }
    
    public float getY(){
        return ptX;
    }
    
    public void setX(float ptX){
        this.ptX = ptX;
    }
    
    public void setY(float ptY){
        this.ptY = ptY;
    }
    
    public float getRadius(){
        return this.radius;
    }
    
    @Override
    public boolean holds(float ptX,float ptY){
        return Math.pow(ptX-this.ptX,2) + Math.pow(ptY - this.ptY,2) <= Math.pow(radius,2);
    }
    
    @Override
    public boolean holds(IShape shape) {
        if (shape instanceof ACircle) {
            ACircle circle = (ACircle) shape;
            float distanceSquared = (Math.pow(ptX - circle.getX(), 2) +
                                              Math.pow(ptY - circle.getY(), 2));
            float combinedRadius = radius + circle.getRadius();
            return distanceSquared <= combinedRadius * combinedRadius;
        }
        return false; // For other shapes, return false
    }
    
    @Override
    public boolean covers(IShape shape) {
        if (shape instanceof ACircle) {
            ACircle circle = (ACircle) shape;
            float distanceSquared = (Math.pow(ptX - circle.getX(), 2) +
                                              Math.pow(ptY - circle.getY(), 2));
            float combinedRadius = radius + circle.getRadius();
            return distanceSquared <= combinedRadius * combinedRadius;
        }
        return false; // For other shapes, return false
    }
}