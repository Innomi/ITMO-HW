package expression;

import expression.generic.Type;

public class CheckedMultiply<T extends Number> extends BinaryOperation<T> implements TripleExpression<T> {
    public CheckedMultiply(TripleExpression<T> leftOperand, TripleExpression<T> rightOperand) {
        super(leftOperand, rightOperand);
    }
    
    protected Type<T> evaluateImpl(Type<T> left, Type<T> right) {
        return left.multiply(right);
    }
}
