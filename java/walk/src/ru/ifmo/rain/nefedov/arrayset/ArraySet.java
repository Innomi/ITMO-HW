package ru.ifmo.rain.nefedov.arrayset;

import java.util.*;

public class ArraySet<T extends Comparable<T>> extends AbstractSet<T> implements SortedSet<T> {
    private List<T> arrayList;
    private Comparator<T> comparator;

    public ArraySet() {
        this(Collections.emptyList());
    }

    public ArraySet(Collection<T> col) {
        this(col, null);
    }

    public ArraySet(Collection<T> col, Comparator<T> cmp) {
        TreeSet<T> treeSet = new TreeSet<>(cmp);
        treeSet.addAll(col);
        arrayList = new ArrayList<>(treeSet);
        comparator = cmp;
        arrayList = Collections.unmodifiableList(arrayList);
    }

    private ArraySet(ArraySet<T> other, int fromIndex, int toIndex) {
        this.arrayList = other.arrayList.subList(fromIndex, toIndex);
        this.comparator = other.comparator;
    }

    @Override
    public Comparator<? super T> comparator() {
        return comparator;
    }

    @Override
    public ArraySet<T> subSet(T fromElement, T toElement) {
        return sub(getIndex(fromElement), getIndex(toElement));
    }

    @Override
    public ArraySet<T> headSet(T toElement) {
        return sub(0, getIndex(toElement));
    }

    @Override
    public ArraySet<T> tailSet(T fromElement) {
        return sub(getIndex(fromElement), arrayList.size());
    }

    @Override
    public T first() {
        isEmptyCheckWithException();
        return arrayList.get(0);
    }

    @Override
    public T last() {
        isEmptyCheckWithException();
        return arrayList.get(arrayList.size() - 1);
    }

    @Override
    public int size() {
        return arrayList.size();
    }

    @Override
    public boolean isEmpty() {
        return arrayList.isEmpty();
    }

    @Override
    public boolean contains(Object o) {
        return (Collections.binarySearch(arrayList, (T)o, comparator) >= 0);
    }

    @Override
    public Iterator<T> iterator() {
        return arrayList.iterator();
    }

    private int getIndex(T element) {
        int index = Collections.binarySearch(arrayList, element, comparator);
        if (index < 0) {
            index = (index + 1) * (-1);
        }
        return index;
    }

    private ArraySet<T> sub(int fromIndex, int toIndex) {
        if (fromIndex > toIndex) {
            throw new IllegalArgumentException("Illegal arguments for subSet(T fromElement, T toElement)");
        }
        return new ArraySet<>(this, fromIndex, toIndex);
    }

    private void isEmptyCheckWithException() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
    }
}