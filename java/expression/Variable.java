package expression;

import expression.generic.Type;

public class Variable<T extends Number> implements TripleExpression<T> {
    String name;
    
    public Variable(String name) {
        this.name = name;
    }
    
    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) {
        if (name.equals("y")) {
            return y;
        }
        if (name.equals("z")) {
            return z;
        }
        return x;
    }
}
