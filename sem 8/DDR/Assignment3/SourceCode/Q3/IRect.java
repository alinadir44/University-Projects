public interface IRect{
    public float Area();
    public float Parameter();
    public boolean holds (ARectangle rect);
    public boolean holds (float ptX,float ptY);
    public boolean covers (ARectangle rect);
}