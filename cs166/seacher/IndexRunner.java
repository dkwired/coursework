//package edu.ucr.cs172.index;


import java.lang.System;
import java.lang.Exception;

public class IndexRunner {
	/**
	  * args:	String => document folder
	  *			String => index output directory
	  */
	public static void main(String[] args) {
		if(args.length < 2)
			System.out.println("Must pass in arguments: document directory, index output directory\n");
		
		try {
			Indexer.index(args[0], args[1]);
		} catch(Exception e) {
			System.out.println("Error: " + e.getMessage());
			System.exit(1);
		}
	}
}
