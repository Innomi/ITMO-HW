package expression.exceptions;

import expression.TripleExpression;
import expression.exceptions.ParserException;

public interface Parser<T extends Number> {
    TripleExpression<T> parse(String expression) throws ParserException;
}
