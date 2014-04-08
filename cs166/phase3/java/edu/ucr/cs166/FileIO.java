package edu.ucr.cs166;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class FileIO {
	
	public static ArrayList<String> readFileLines(String fileName) {
		ArrayList<String> lines = null;
		try {
			BufferedReader x = new BufferedReader(new FileReader(fileName));
			lines = new ArrayList<String>();
			String buf = "";
			while((buf = x.readLine()) != null)
				lines.add(buf);
			x.close();
		} catch(IOException e) {
			System.out.println("Could not open file " + fileName + ": " + e.getMessage());
		}
		return lines;
	}	
	
}
