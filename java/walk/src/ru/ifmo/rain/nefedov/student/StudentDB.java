package ru.ifmo.rain.nefedov.student;

import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;
import java.util.stream.Collector;

import info.kgeorgiy.java.advanced.student.*;

import static java.util.stream.Collectors.*;

public class StudentDB implements StudentGroupQuery {
    private final Comparator<Student> byName = Comparator.comparing(Student::getLastName)
            .thenComparing(Student::getFirstName).thenComparing(Student::getId);

    @Override
    public List<String> getFirstNames(List<Student> students) {
        return getField(students, Student::getFirstName);
    }

    @Override
    public List<String> getLastNames(List<Student> students) {
        return getField(students, Student::getLastName);
    }

    @Override
    public List<String> getGroups(List<Student> students) {
        return getField(students, Student::getGroup);
    }

    @Override
    public List<String> getFullNames(List<Student> students) {
        return getField(students, (Student s) -> String.format("%s %s", s.getFirstName(), s.getLastName()));
    }

    @Override
    public Set<String> getDistinctFirstNames(List<Student> students) {
        return students.stream().map(Student::getFirstName).collect(toCollection(TreeSet::new));
    }

    @Override
    public String getMinStudentFirstName(List<Student> students) {
        return students.stream().min(Comparator.comparing(Student::getId)).map(Student::getFirstName).orElse("");
    }

    @Override
    public List<Student> sortStudentsById(Collection<Student> students) {
        return sortWithComparator(students.stream(), Student::compareTo).collect(toList());
    }

    @Override
    public List<Student> sortStudentsByName(Collection<Student> students) {
        return sortWithComparator(students.stream(), byName).collect(toList());
    }

    @Override
    public List<Student> findStudentsByFirstName(Collection<Student> students, String name) {
        return filter(students, s -> s.getFirstName().equals(name));
    }

    @Override
    public List<Student> findStudentsByLastName(Collection<Student> students, String name) {
        return filter(students, s -> s.getLastName().equals(name));
    }

    @Override
    public List<Student> findStudentsByGroup(Collection<Student> students, String group) {
        return filter(students,  s -> s.getGroup().equals(group));
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(Collection<Student> students, String group) {
        return students.stream().filter(s -> s.getGroup().equals(group))
                .collect(toMap(Student::getLastName, Student::getFirstName,
                        BinaryOperator.minBy(String::compareTo)));
    }

    @Override
    public List<Group> getGroupsByName(Collection<Student> students) {
        return getGroupsBy(sortStudentsByName(students));
    }

    @Override
    public List<Group> getGroupsById(Collection<Student> students) {
        return getGroupsBy(sortStudentsById(students));
    }

    @Override
    public String getLargestGroup(Collection<Student> students) {
        return getGroup(students, Collectors.counting());
    }

    @Override
    public String getLargestGroupFirstName(Collection<Student> students) {
        return getGroup(students, collectingAndThen(mapping(Student::getFirstName, toSet()), s -> (long)s.size()));
    }

    private List<String> getField(List<Student> students, Function<? super Student,? extends String> field) {
        return students.stream().map(field).collect(toList());
    }

    private Stream<Student> sortWithComparator(Stream<Student> students, Comparator<Student> cmp) {
        return students.sorted(cmp);
    }

    private List<Student> filter(Collection<Student> students, Predicate<Student> predicate) {
        return sortWithComparator(students.stream().filter(predicate), byName).collect(toList());
    }

    private List<Group> getGroupsBy(Collection<Student> students) {
        return students.stream().collect(Collectors.groupingBy(Student::getGroup, toList())).entrySet()
                .stream().map(e -> new Group(e.getKey(), e.getValue())).sorted(Comparator.comparing(Group::getName))
                .collect(toList());
    }

    private String getGroup(Collection<Student> students, Collector<Student, ?, Long> collector) {
        return students.stream().collect(Collectors.groupingBy(Student::getGroup, collector)).entrySet()
                .stream().max(Comparator.comparing((Function<Map.Entry<String, Long>, Long>)Map.Entry::getValue)
                        .thenComparing(Map.Entry::getKey, Comparator.reverseOrder())).map(Map.Entry::getKey).orElse("");
    }
}
