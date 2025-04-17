public class Fraction {
    private int num;
    private int den;

    public Fraction(){};

    public Fraction(int num){
        this.num = num;
        this.den = 1;
    }

    public Fraction(int num,int den){
        assert(den > 0);

        this.num = num;
        this.den = den;
    }

    public int getNum() {
        return num;
    }

    public int getDen() {
        return den;
    }

    private void setNum(int num) {
        this.num = num;
    }

    private void setDen(int den) {
        this.den = den;
    }

    @Override
    public String toString() {
        return den == 1? Integer.toString(num) : Integer.toString(num) + "/" + Integer.toString(den);
    }

    public static Fraction addFrac(Fraction f1, Fraction f2){
        int new_num = (f1.getNum() * f2.getDen()) + (f2.getNum() * f1.getDen());
        int new_den = (f1.getDen() * f2.getDen());

        Fraction new_f = new Fraction();
        new_f.setNum(new_num);
        new_f.setDen(new_den);

        return new_f;
    }

    public static Fraction subFrac(Fraction f1, Fraction f2){
        int new_num = (f1.getNum() * f2.getDen()) - (f2.getNum() * f1.getDen());
        int new_den = (f1.getDen() * f2.getDen());

        Fraction new_f = new Fraction();
        new_f.setNum(new_num);
        new_f.setDen(new_den);

        return new_f;
    }

    public static Fraction multFrac(Fraction f1, Fraction f2){
        int new_num = (f1.getNum() * f2.getNum());
        int new_den = (f1.getDen() * f2.getDen());

        Fraction new_f = new Fraction();
        new_f.setNum(new_num);
        new_f.setDen(new_den);

        return new_f;
    }

    public static Fraction divFrac(Fraction f1, Fraction f2){
        int new_num = (f1.getNum() * f2.getDen());
        int new_den = (f1.getDen() * f2.getNum());

        Fraction new_f = new Fraction();
        new_f.setNum(new_num);
        new_f.setDen(new_den);

        return new_f;
    }

    static int gcd(int a, int b){
        int i;
        if (a < b)
            i = a;
        else
            i = b;
        
        for (i = i; i > 1; i--) {
 
            if (a % i == 0 && b % i == 0)
                return i;
        }
 
        return 1;
    } 
}
