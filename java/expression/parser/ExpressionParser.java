package expression.parser;

import expression.*;
import expression.generic.Type;
import expression.exceptions.ParserException;
import expression.exceptions.Parser;

public class ExpressionParser<T extends Number> implements Parser<T> {
    private int curPos = -1, balance = 0, tokensAmount = 0;
    Type<T> curNum;
    private String curName;
    private enum Token { SUB, ADD, DIV, MUL, OB, CB, END, VAR, NUM, ABS, SQU, MOD };
    private Token curToken;
    
    public ExpressionParser(Type<T> type) {
        this.curNum = type;
    }
    
    public Type<T> getType() {
        return curNum;
    }
    
    public TripleExpression<T> parse(String expression) throws ParserException {
        try {
            TripleExpression<T> temp = addOrSub(expression);
            return temp;
        }
        catch(ParserException e) {
            throw new ParserException(e.getMessage());
        }
        catch(NumberFormatException e) {
            throw new ParserException("too big constant found");
        }
        finally {
            balance = 0;
            curPos = -1;
        }
    }
    
    private Token getToken(String expression) throws ParserException {
        tokensAmount++;
        do {
            curPos++;
        } while (curPos < expression.length() && Character.isWhitespace(expression.charAt(curPos)));
        
        if (curPos >= expression.length()) {
            return Token.END;
        }
        
        char ch = expression.charAt(curPos);
        switch(ch) {
            case 'm':
                if (expression.substring(curPos, curPos + 3).equals("mod")) {
                    curPos += 2;
                    return Token.MOD;
                }
                throw new ParserException("incorrect symbol at " + tokensAmount + " position");
            case 'a':
                if (expression.substring(curPos, curPos + 3).equals("abs")) {
                    curPos += 2;
                    return Token.ABS;
                }
                throw new ParserException("incorrect symbol at " + tokensAmount + " position");
            case 's':
                if (expression.substring(curPos, curPos + 6).equals("square")) {
                    curPos += 5;
                    return Token.SQU;
                }
                throw new ParserException("incorrect symbol at " + tokensAmount + " position");
            case '*':
                return Token.MUL;
            case '/':
                return Token.DIV;
            case '+':
                return Token.ADD;
            case '-':
                return Token.SUB;
            case '(':
                balance++;
                return Token.OB;
            case ')':
                balance--;
                if (balance < 0) {
                    throw new ParserException("expected openning bracket");
                }
                return Token.CB;
            default:
                if (ch == 'x' || ch == 'y' || ch == 'z') {
                    curName = Character.toString(ch);
                    return Token.VAR;
                }
                if (Character.isDigit(ch)) {
                    StringBuilder num = new StringBuilder();
                    while (curPos < expression.length() && Character.isDigit(expression.charAt(curPos))) {
                        num.append(expression.charAt(curPos));
                        curPos++;
                    }
                    curPos--;
                    curNum = curNum.parse(num.toString());
                    return Token.NUM;
                }
                throw new ParserException("incorrect symbol at " + tokensAmount + " position");
        }
    }
    
    private TripleExpression<T> addOrSub(String expression) throws ParserException {
        TripleExpression<T> left = mulOrDiv(expression);
        
        while (true) {
            switch (curToken) {
                case ADD:
                    left = new CheckedAdd<T>(left, mulOrDiv(expression));
                    break;
                case SUB:
                    left = new CheckedSubtract<T>(left, mulOrDiv(expression));
                    break;
                case OB:
                    throw new ParserException();
                default:
                    return left;
            }
        }
    }
    
    private TripleExpression<T> mulOrDiv(String expression) throws ParserException {
        TripleExpression<T> left = primaryExpression(expression);
        
        while (true) {
            switch (curToken) {
                case MOD:
                    left = new CheckedMod<T>(left, primaryExpression(expression));
                    break;
                case MUL:
                    left = new CheckedMultiply<T>(left, primaryExpression(expression));
                    break;
                case DIV:
                    left = new CheckedDivide<T>(left, primaryExpression(expression));
                    break;
                case OB:
                    throw new ParserException();
                default:
                    return left;
            }
        }
    }
    
    private TripleExpression<T> primaryExpression(String expression) throws ParserException {
            curToken = getToken(expression);
        
        switch(curToken) {
            case SQU:
                return new CheckedSquare<T>(primaryExpression(expression));
            case ABS:
                return new CheckedAbs<T>(primaryExpression(expression));
            case NUM:
                TripleExpression<T> c = new Const<T>(curNum);
                curToken = getToken(expression);
                return c;
            case VAR:
                TripleExpression<T> v = new Variable<T>(curName);
                curToken = getToken(expression);
                return v;
            case SUB:
                do {
                    curPos++;
                } while (curPos < expression.length() && Character.isWhitespace(expression.charAt(curPos)));
                if (Character.isDigit(expression.charAt(curPos))) {
                    StringBuilder num;
                    num = new StringBuilder("-");
                    while (curPos < expression.length() && Character.isDigit(expression.charAt(curPos))) {
                        num.append(expression.charAt(curPos));
                        curPos++;
                    }
                    curPos--;
                    curNum = curNum.parse(num.toString());
                    curToken = getToken(expression);
                    return new Const<T>(curNum);
                } else {
                    curPos--;
                    return new CheckedNegate<T>(primaryExpression(expression));
                }
            case OB:
                TripleExpression<T> r = addOrSub(expression);
                if (curToken != Token.CB) {
                    throw new ParserException("expected closing bracket");
                }
                curToken = getToken(expression);
                return r;
            default:
                throw new ParserException("no argument at " + tokensAmount + " position");
        }
    }
}
