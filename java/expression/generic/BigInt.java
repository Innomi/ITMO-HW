package expression.generic;

import java.math.BigInteger;

public class BigInt extends AbstractType<BigInteger> {
    public BigInt(Type<BigInteger> value) {
        super(value);
    }

    public BigInt(BigInteger value) {
        super(value);
    }

    public Type<BigInteger> add(Type<BigInteger> right) {
        return new BigInt(getValue().add(right.getValue()));
    }

    public Type<BigInteger> subtract(Type<BigInteger> right) {
        return new BigInt(getValue().subtract(right.getValue()));
    }

    public Type<BigInteger> multiply(Type<BigInteger> right) {
        return new BigInt(getValue().multiply(right.getValue()));
    }

    public Type<BigInteger> divide(Type<BigInteger> right) {
        return new BigInt(getValue().divide(right.getValue()));
    }
    
    public Type<BigInteger> mod(Type<BigInteger> right) {
        return new BigInt(getValue().remainder(right.getValue()));
    }

    public Type<BigInteger> parse(String str) {
        return new BigInt(new BigInteger(str));
    }

    public Type<BigInteger> negate() {
        return new BigInt(getValue().negate());
    }
    
    public Type<BigInteger> abs() {
        return new BigInt(getValue().abs());
    }
    
    public Type<BigInteger> square() {
        return new BigInt(getValue().multiply(getValue()));
    }
}
