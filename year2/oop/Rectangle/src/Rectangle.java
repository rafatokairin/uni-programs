public class Rectangle {
    private double width = 1.0;
    private double length = 1.0;
    public double getLength() {
        return length;
    }
    public void setLength(double length) {
        if (length > 0.0 || length < 20.0)
            this.length = length;
    }
    public double getWidth() {
        return width;
    }
    public void setWidth(double width) {
        if (length > 0.0 || length < 20.0)
            this.width = width;
    }
    public double calcPerimetro() {
        return 2 * (this.length + this.width);
    }
    public double calcArea() {
        return this.width * this.length;
    }
}