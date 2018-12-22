package expression;

import expression.generic.Type;

public class CheckedSquare<T extends Number> implements TripleExpression<T> {
    private TripleExpression<T> operand;
    
    public CheckedSquare(TripleExpression<T> operand) {
        this.operand = operand;
    }
    
    public Type<T> evaluate(Type<T> x, Type<T> y, Type<T> z) {
        return operand.evaluate(x, y, z).square();
    }
}
