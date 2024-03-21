

public class ARectangle implements IRect {
    private float ptX;
    private float ptY;
    private float wt;
    private float ht;
    
    public ARectangle(){
        this.ptX = 0;
        this.ptY = 0;
        this.wt = 1;
        this.ht = 1;
    }
    
    public ARectangle(float ptX, float ptY, float wt,float ht){
        this.ptX = ptX;
        this.ptY =ptY;
        this.wt = wt;
        this.ht = ht;
    }
    
    @Override
    public float Area(){
        return wt*ht;
    }
    
    @Override
    public float Parameter(){
        return 2*(ht+wt);
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
    
    public float getW(){
        return wt;
    }
    
    public float getH(){
        return ht;
    }
    
    @Override
    public boolean holds(float ptX,float ptY){
        float halfWidth = this.wt / 2;
        float halfHeight = this.ht / 2;
        float leftX = this.ptX - halfWidth;
        float rightX = this.ptX + halfWidth;
        float topY = this.ptY - halfHeight;
        float bottomY = this.ptY + halfHeight;
        
        return (ptX >= leftX && ptX <= rightX && ptY >= topY && ptY <= bottomY);
    }
    
    @Override
    public boolean holds (ARectangle rect){
        float innerHalfHeight = rect.getH() / 2;
        float innerHalfWidth = rect.getW() / 2;

         float outerHalfWidth = this.wt / 2;
         float outerHalfHeight = this.ht / 2;
        
         float innerLeftX = rect.getX() - innerHalfWidth;
         float innerRightX = rect.getX() + innerHalfWidth;
         float innerTopY = rect.getY() - innerHalfHeight;
         float innerBottomY = rect.getY() + innerHalfHeight;
         float outerLeftX = this.ptX - outerHalfWidth;
         float outerRightX = this.ptX + outerHalfWidth;
         float outerTopY = this.ptY - outerHalfHeight;
         float outerBottomY = this.ptY + outerHalfHeight;
        
        return (
          innerLeftX >= outerLeftX &&
          innerRightX <= outerRightX &&
          innerTopY >= outerTopY &&
          innerBottomY <= outerBottomY
        );
    }
    @Override
    public boolean covers (ARectangle rect){
         float r1LX = this.ptX-this.wt/2;
         float r1LY = this.ptY+this.ht/2;

         float r1RX  = this.ptX+this.wt/2;
         float r1RY =  this.ptY-this.ht/2;
        
        
         float r2LX = rect.getX()-rect.getW()/2;
         float r2LY = rect.getY()+rect.getW()/2;

         float r2RX = rect.getX()+rect.getW()/2;
         float r2RY = rect.getY()-rect.getW()/2;
        
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
}