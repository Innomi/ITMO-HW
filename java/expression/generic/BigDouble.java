package expression.generic;

public class BigDouble extends AbstractType<Double> {
    public BigDouble(Type<Double> value) {
        super(value);
    }

    public BigDouble(Double value) {
        super(value);
    }

    public Type<Double> add(Type<Double> right) {
        return new BigDouble(getValue() + right.getValue());
    }

    public Type<Double> subtract(Type<Double> right) {
        return new BigDouble(getValue() - right.getValue());
    }

    public Type<Double> multiply(Type<Double> right) {
        return new BigDouble(getValue() * right.getValue());
    }

    public Type<Double> divide(Type<Double> right) {
        return new BigDouble(getValue() / right.getValue());
    }
    
    public Type<Double> mod(Type<Double> right) {
        return new BigDouble(getValue() % right.getValue());
    }

    public Type<Double> parse(String str) {
        return new BigDouble(Double.parseDouble(str));
    }

    public Type<Double> negate() {
        return new BigDouble(-getValue());
    }
    
    public Type<Double> abs() {
        return new BigDouble(Math.abs(getValue()));
    }
    
    public Type<Double> square() {
        return new BigDouble(getValue() * getValue());
    }
}
