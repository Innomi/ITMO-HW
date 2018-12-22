package expression.generic;

public class Int extends AbstractType<Integer> {
    public Int(Type<Integer> value) {
        super(value);
    }

    public Int(Integer value) {
        super(value);
    }

    public Type<Integer> add(Type<Integer> right) {
        return new Int(Math.addExact(getValue(), right.getValue()));
    }

    public Type<Integer> subtract(Type<Integer> right) {
        return new Int(Math.subtractExact(getValue(), right.getValue()));
    }

    public Type<Integer> multiply(Type<Integer> right) {
        return new Int(Math.multiplyExact(getValue(), right.getValue()));
    }

    public Type<Integer> divide(Type<Integer> right) {
        return new Int(getValue() / right.getValue());
    }
    
    public Type<Integer> mod(Type<Integer> right) {
        return new Int(getValue() % right.getValue());
    }

    public Type<Integer> parse(String str) {
        return new Int(Integer.parseInt(str));
    }

    public Type<Integer> negate() {
        return new Int(Math.negateExact(getValue()));
    }
    
    public Type<Integer> abs() {
        return new Int(Math.abs(getValue()));
    }
    
    public Type<Integer> square() {
        return new Int(Math.multiplyExact(getValue(), getValue()));
    }
}
