package expression.generic;

public abstract class AbstractType<T extends Number> implements Type<T> {
    private T value;

    protected AbstractType(Type<T> value) {
        this.value = value.getValue();
    }

    protected AbstractType(T value) {
        this.value = value;
    }

    public T getValue() {
        return value;
    }
}
