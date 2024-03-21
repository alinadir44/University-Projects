

public class ASquare implements IShape {
    private float ptX;
    private float ptY;
    private float len;
    
    public ASquare(){
        this.ptX = 0;
        this.ptY = 0;
        this.len = 1;
    }
    
    public ASquare(float ptX, float ptY, float wt,float ht){
        this.ptX = ptX;
        this.ptY =ptY;
        this.len = 1;
    }
    
    @Override
    public float Area(){
        return len*len;
    }
    
    @Override
    public float Parameter(){
        return 4*len;
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
    
    public float getL(){
        return len;
    }
    
    @Override
    public boolean holds(float ptX,float ptY){
        float halflength = this.len / 2;
        float leftX = this.ptX - halflength;
        float rightX = this.ptX + halflength;
        float topY = this.ptY - halflength;
        float bottomY = this.ptY + halflength;
        
        return (ptX >= leftX && ptX <= rightX && ptY >= topY && ptY <= bottomY);
    }
    
    @Override
    public boolean holds (IShape shape){
        if(shape instanceof ASquare){
            ASquare rect  = (ASquare) shape;
        float innerHalflength = rect.getL() / 2;

         float outerHalflength = this.len / 2;
        
         float innerLeftX = rect.getX() - innerHalflength;
         float innerRightX = rect.getX() + innerHalflength;
         float innerTopY = rect.getY() - innerHalflength;
         float innerBottomY = rect.getY() + innerHalflength;
         float outerLeftX = this.ptX - outerHalflength;
         float outerRightX = this.ptX + outerHalflength;
         float outerTopY = this.ptY - outerHalflength;
         float outerBottomY = this.ptY + outerHalflength;
        
        return (
          innerLeftX >= outerLeftX &&
          innerRightX <= outerRightX &&
          innerTopY >= outerTopY &&
          innerBottomY <= outerBottomY
        );
        }else
        return false;
    }
    
    @Override
    public boolean covers (IShape shape){
        
        if(shape instanceof ASquare){
            ASquare rect  = (ASquare) shape;
            float r1LX = this.ptX-this.len/2;
         float r1LY = this.ptY+this.len/2;

         float r1RX  = this.ptX+this.len/2;
         float r1RY =  this.ptY-this.len/2;
        
        
         float r2LX = rect.getX()-rect.getL()/2;
         float r2LY = rect.getY()+rect.getL()/2;

         float r2RX = rect.getX()+rect.getL()/2;
         float r2RY = rect.getY()-rect.getL()/2;
        
            // if rectangle has area 0, no overlap
            if (r1LX == r1RX || r1LY == r1RY || r2RX == r2LX || r2LY == r2RY)
                return false;
        
            // If one rectangle is on left side of other
            if (r1LX > r1RX || r2LX > r1RX)
                return false;
        
            // If one rectangle is above other
            if (r1RY > r2LY || r2RY > r1LY)
            return false;
    
        return true;
        }
        return false;
         
    }
}