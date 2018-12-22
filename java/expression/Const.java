package expression;

import expression.generic.Type;

public class Const<T extends Number> implements TripleExpression<T> {
    private final Type<T> value;
    
    public Const(Type<T> value) {
        this.value = value;
    }
    
    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) {
        return value;
    }
}
