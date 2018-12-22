package ru.ifmo.rain.nefedov.walk;

import java.io.*;
import java.nio.file.*;
import java.util.stream.Stream;

public class RecursiveWalk {

    public static void main(String[] args) {
        if (args.length != 2) {
            System.err.println("Should be 2 args: <input file> <output file>");
            return;
        }
        Path input, output;
        try {
            input = Paths.get(args[0]);
            output = Paths.get(args[1]);
        } catch (InvalidPathException e) {
            System.err.println("One of the path strings is incorrect.");
            return;
        }
        try {
            outputStream = Files.newBufferedWriter(output);
            try (BufferedReader inputStream = Files.newBufferedReader(input)) {
                String fileName;
                while ((fileName = inputStream.readLine()) != null) {
                    Path currentFile;
                    try {
                        currentFile = Paths.get(fileName);
                    } catch (InvalidPathException e) {
                        System.err.println("Path is invalid: " + fileName);
                        try {
                            outputStream.write(String.format("%08x", 0) + " " + fileName);
                            outputStream.newLine();
                        } catch (IOException|SecurityException err) {
                            System.err.println("Output file access error.");
                        }
                        continue;
                    }
                    calculateHash(currentFile);
                }
            } catch (IOException|SecurityException e) {
                System.err.println("Input file access error.");
                return;
            }
            outputStream.close();
        } catch (IOException|SecurityException e) {
            try {
                outputStream.close();
            } catch (IOException|SecurityException err) {
                /*-- Ignoring --*/
            }
            System.err.println("Output file access error.");
        }
    }

    private static BufferedWriter outputStream;

    private static void calculateHash(Path currentFile) {
        if (Files.isDirectory(currentFile)) {
            Stream<Path> list;
            try {
                list = Files.list(currentFile);
                list.forEach(RecursiveWalk::calculateHash);
            } catch (IOException|SecurityException e) {
                System.err.println("Can't get list of files in directory " + currentFile.toString() + ".");
            }
            return;
        }
        try (InputStream hashStream = Files.newInputStream(currentFile)) {
            outputStream.write(String.format("%08x", hashFnv(hashStream)) + " " + currentFile.toString());
            outputStream.newLine();
        } catch (IOException|SecurityException e) {
            System.err.println(currentFile.toString() + " : file/directory access error.");
            try {
                outputStream.write(String.format("%08x", 0) + " " + currentFile.toString());
                outputStream.newLine();
            } catch (IOException|SecurityException err) {
                System.err.println("Output file access error.");
                System.exit(0);
            }
        }
    }

    private static final int FNV_32_PRIME = 0x01000193;

    private static int hashFnv(InputStream hashStream) throws IOException {
        int hVal = 0x811c9dc5;
        byte[] c = new byte[4096];
        int k;
        while ((k = hashStream.read(c, 0, 4096)) >= 0) {
            for (int i = 0; i < k; ++i)
                hVal = (hVal * FNV_32_PRIME) ^ (c[i] & 0xff);
        }
        return hVal;
    }
}
