package expression.generic;

public class MyFloat extends AbstractType<Float> {
    public MyFloat(Type<Float> value) {
        super(value);
    }

    public MyFloat(Float value) {
        super(value);
    }
    
    public MyFloat(Double value) {
        super(value.floatValue());
    }

    public Type<Float> add(Type<Float> right) {
        return new MyFloat(getValue() + right.getValue());
    }

    public Type<Float> subtract(Type<Float> right) {
        return new MyFloat(getValue() - right.getValue());
    }

    public Type<Float> multiply(Type<Float> right) {
        return new MyFloat(getValue() * right.getValue());
    }

    public Type<Float> divide(Type<Float> right) {
        return new MyFloat(getValue() / right.getValue());
    }
    
    public Type<Float> mod(Type<Float> right) {
        return new MyFloat(getValue() % right.getValue());
    }

    public Type<Float> parse(String str) {
        return new MyFloat(Float.parseFloat(str));
    }

    public Type<Float> negate() {
        return new MyFloat(-getValue());
    }
    
    public Type<Float> abs() {
        return new MyFloat(Math.abs(getValue()));
    }
    
    public Type<Float> square() {
        return new MyFloat(getValue() * getValue());
    }
}
