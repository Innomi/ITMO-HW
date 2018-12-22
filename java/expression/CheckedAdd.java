package expression;

import expression.generic.Type;

public class CheckedAdd<T extends Number> extends BinaryOperation<T> implements TripleExpression<T> {
    public CheckedAdd(TripleExpression<T> leftOperand, TripleExpression<T> rightOperand) {
        super(leftOperand, rightOperand);
    }
    
    protected Type<T> evaluateImpl(Type<T> left, Type<T> right) {
        return left.add(right);
    }
}
