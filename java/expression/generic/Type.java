package expression.generic;

public interface Type<T extends Number> {
    T getValue();
    Type<T> parse(String str);
    Type<T> add(Type<T> right);
    Type<T> subtract(Type<T> right);
    Type<T> multiply(Type<T> right);
    Type<T> divide(Type<T> right);
    Type<T> mod(Type<T> right);
    Type<T> negate();
    Type<T> abs();
    Type<T> square();
}
