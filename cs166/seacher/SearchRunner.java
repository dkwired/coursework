
import java.lang.System;
import java.lang.Exception;

import org.apache.lucene.search.TopDocs;
import org.apache.lucene.search.ScoreDoc;

public class SearchRunner {
	/**
	  * args:	String => document folder
	  *			String => index output directory
	  */
	public static void main(String[] args) {
		if(args.length < 2)
			System.out.println("Must pass in arguments: index directory, query\n");
		
		TopDocs td = null;
		try {
			td = Searcher.doSearch(args[0], args[1]);
		} catch(Exception e) {
			System.out.println("Error: " + e.getMessage());
			System.exit(1);
		}
		ScoreDoc[] sd = td.scoreDocs;
		System.out.println("Found " + td.totalHits + " total hits.");
		for(int i = 0; i < sd.length; ++i) {
			System.out.println(sd[i].toString());
		}
	}
}
