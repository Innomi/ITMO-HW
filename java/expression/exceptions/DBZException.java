package expression.exceptions;

public class DBZException extends MathException {
    public DBZException() {
        super("division by zero");
    }
}
