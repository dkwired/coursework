//package edu.ucr.cs172.search;

import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.HashMap;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.index.IndexReader;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.IndexSearcher;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.TopDocs;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

public class Searcher {

	public static TopDocs doSearch (String indexPath, String queryString) throws ParseException, IOException {
		IndexReader indexReader = IndexReader.open(FSDirectory.open(new File(indexPath)), true);
		IndexSearcher indexSearcher = new IndexSearcher(indexReader);
		QueryParser queryparse = new QueryParser(Version.LUCENE_36, "body", new StandardAnalyzer(Version.LUCENE_36));
		
		queryString = preProcessQuery(queryString);	
		Query query = queryparse.parse(queryString.trim());
		System.out.println(query.toString());
		TopDocs results = indexSearcher.search(query, 50);
		
		for(int i = 0; i < results.totalHits; ++i) {
			System.out.println(indexSearcher.doc(results.scoreDocs[i].doc).get("docid"));
			System.out.println(indexSearcher.doc(results.scoreDocs[i].doc).get("source"));
			System.out.println(indexSearcher.doc(results.scoreDocs[i].doc).get("snippet"));
		}
		// TODO here you can get the information you "stored" in inverted index
		// you need to get the whole document and generate snippets for UI ..
		indexSearcher.close();
		return results;
	}
	
	private static String preProcessQuery(String original) {
		original = "botanical garden"; //TODO for testing only
		ArrayList<String> tokens = new ArrayList<String>(Arrays.asList(original.split("\\s+")));
		ArrayList<String> stopWords = removeStopWords(tokens);
		String newQuery = original + " OR (";
		if(tokens.isEmpty()) {
			for(int i = 0; i < stopWords.size(); ++i)
				newQuery += stopWords.get(i) + "~ "; //fuzzy search
			newQuery += ")^0.9";
		} else {
			for(int i = 0; i < tokens.size(); ++i)
				newQuery += tokens.get(i) + "~ ";
			newQuery += ")^0.7 OR ";
			newQuery += "(title:(" + original + "))^2 ";
			newQuery += "(headings:(" + original + "))^1.5 ";
			newQuery += "(emphasized:(" + original + "))^1.25 OR (";
			newQuery += "body:" + original + " AND (imgalt:(" + original + "))^1.25)";
		}
		return newQuery;
	}
	
	private static ArrayList<String> removeStopWords(ArrayList<String> list) {
		HashMap<String, String> stopWords = getStopWords("stop_words.txt");
		ArrayList<String> removed = new ArrayList<String>();
		for(int i = 0; i < list.size(); ++i) {
			if(stopWords.get(list.get(i)) != null) {
				removed.add(list.get(i));
				list.remove(i);
			}
		}
		return removed;
	}
	
	private static HashMap<String, String> getStopWords(String wordFile) {
		HashMap<String, String> map = new HashMap<String, String>();
		try {
			BufferedReader x = new BufferedReader(new FileReader(wordFile));
			String buf;
			while((buf = x.readLine()) != null)
				map.put(buf, buf);
			x.close();
		} catch(IOException e) {
			System.out.println("Error getting stop words: " + e.getMessage());
		}
		return map;
	}
}
