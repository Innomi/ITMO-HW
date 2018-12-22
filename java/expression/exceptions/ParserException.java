package expression.exceptions;

public class ParserException extends ComplexException {
    public ParserException() {
        super("incorrect expression");
    }
    
    public ParserException(String message) {
        super(message);
    }
}
