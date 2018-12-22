package expression.generic;

public class MyByte extends AbstractType<Byte> {
    public MyByte(Type<Byte> value) {
        super(value);
    }

    public MyByte(Byte value) {
        super(value);
    }
    
    public MyByte(Integer value) {
        super(value.byteValue());
    }
    
    private Byte makeByte(int v) {
        Integer temp = v & 0xFF;
        return temp.byteValue();
    }

    public Type<Byte> add(Type<Byte> right) {
        return new MyByte(makeByte(getValue() + right.getValue()));
    }

    public Type<Byte> subtract(Type<Byte> right) {
        return new MyByte(makeByte(getValue() - right.getValue()));
    }

    public Type<Byte> multiply(Type<Byte> right) {
        return new MyByte(makeByte(getValue() * right.getValue()));
    }

    public Type<Byte> divide(Type<Byte> right) {
        return new MyByte(makeByte(getValue() / right.getValue()));
    }
    
    public Type<Byte> mod(Type<Byte> right) {
        return new MyByte(makeByte(getValue() % right.getValue()));
    }

    public Type<Byte> parse(String str) {
        return new MyByte(makeByte(Byte.parseByte(str)));
    }

    public Type<Byte> negate() {
        return new MyByte(makeByte(-getValue()));
    }
    
    public Type<Byte> abs() {
        return new MyByte(makeByte(Math.abs(getValue())));
    }
    
    public Type<Byte> square() {
        return new MyByte(makeByte(getValue() * getValue()));
    }
}
