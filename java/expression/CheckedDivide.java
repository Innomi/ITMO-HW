package expression;

import expression.generic.Type;

public class CheckedDivide<T extends Number> extends BinaryOperation<T> implements TripleExpression<T> {
    public CheckedDivide(TripleExpression<T> leftOperand, TripleExpression<T> rightOperand) {
        super(leftOperand, rightOperand);
    }
    
    protected Type<T> evaluateImpl(Type<T> left, Type<T> right) {
        return left.divide(right);
    }
}
