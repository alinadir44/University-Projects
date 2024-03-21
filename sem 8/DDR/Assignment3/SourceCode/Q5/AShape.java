public abstract class AShape{
    public abstract float Area();
    public abstract float Parameter();
    public abstract boolean holds (float ptX, float ptY);
    public abstract boolean holds (AShape shape);
    public abstract boolean covers (AShape shape);
}