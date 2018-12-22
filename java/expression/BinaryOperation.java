package expression;

import expression.generic.Type;

public abstract class BinaryOperation<T extends Number> implements TripleExpression<T> {
    private TripleExpression<T> leftOperand, rightOperand;
    
    public BinaryOperation(TripleExpression<T> leftOperand, TripleExpression<T> rightOperand) {
        this.leftOperand = leftOperand;
        this.rightOperand = rightOperand;
    }
    
    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) {
        Type<T> left = leftOperand.evaluate(x, y, z);
        Type<T> right = rightOperand.evaluate(x, y, z);
        return evaluateImpl(left, right);
    }
    
    protected abstract Type<T> evaluateImpl(Type<T> left, Type<T> right);
}
