package expression;

import expression.generic.Type;

public interface TripleExpression<T extends Number> {
    Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z);
}
