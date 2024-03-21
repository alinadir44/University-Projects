public interface IShape{
    public float Area();
    public float Parameter();
    public boolean holds (float ptX, float ptY);
    public boolean holds (IShape shape);
    public boolean covers (IShape shape);
}