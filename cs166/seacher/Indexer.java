//package edu.ucr.cs172.index;


import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import java.util.Scanner;
import java.util.Iterator;

import java.lang.Math;

import org.apache.lucene.analysis.standard.StandardAnalyzer;
import org.apache.lucene.document.Document;
import org.apache.lucene.document.Field;
import org.apache.lucene.index.CorruptIndexException;
import org.apache.lucene.index.IndexWriter;
import org.apache.lucene.index.IndexWriterConfig;
import org.apache.lucene.store.FSDirectory;
import org.apache.lucene.util.Version;

import org.jsoup.Jsoup;
import org.jsoup.select.Elements;
import org.jsoup.nodes.Element;

public class Indexer {
	
	private static final int MAX_SNIPPET_SIZE = 160; // number of characters
	
	public static void index(String docFolder, String indexPath) {
		File docDir = new File(docFolder);
		File indexPathDir = new File(indexPath);
		if(!docDir.isDirectory()) {
			System.out.println("Invalid document folder provided.");
			System.exit(1);
		}
		if(!docDir.canRead()) {
			System.out.println("Read permission denied for document folder.");
			System.exit(1);
		}
		if(!indexPathDir.isDirectory()) {
			if(indexPathDir.mkdirs())
				System.out.println("Index directory created successfully.");
			else {
				System.out.println("Could not create index path.");
				System.exit(1);
			}
		}
		if(!indexPathDir.canWrite()) {
			System.out.println("Write permission denied at index path.");
			System.exit(1);
		}
		
		IndexWriter writer = null;
		try {
			IndexWriterConfig indexConfig = new IndexWriterConfig(Version.LUCENE_36, 
				new StandardAnalyzer(Version.LUCENE_36));
			writer = new IndexWriter(FSDirectory.open(new File(indexPath)),
				indexConfig);
			System.out.println("Indexing to directory " + indexPath + " from " + docFolder + "...");
			indexDocs(writer, new File(docFolder));
			writer.close();
			System.out.println("Done with indexing ... ");
		} catch (Exception ex) {
			ex.printStackTrace();
		} finally {
			if (writer !=null)
				try {
					writer.close();
				} catch (CorruptIndexException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
		}
	}
	
	private static void indexDocs(IndexWriter writer, File file) throws IOException {
		if (file.canRead()) { // do not try to index files that cannot be read
			if (file.isDirectory()) {
				String[] files = file.list(); 					
				if (files != null) { // an IO error could occur
					for (int i = 0; i < files.length; i++) {
						indexDocs(writer, new File(file, files[i]));
					}
				}
			} else {
				System.out.println("adding " + file);
				try {
					writer.addDocument(getDocument(file));
				} catch (FileNotFoundException ex) {
					// at least on windows, some temporary files raise this exception 
					// with an "access denied" message,checking if the file can be read doesn't help
					ex.printStackTrace();
				}
			}
		}
	}
	
	private static Document getDocument(File f) throws java.io.FileNotFoundException {
		Document doc = new Document();
		// TODO get text part of the HTML file
		org.jsoup.nodes.Document htmlDoc = null;
		String source = "";
		try {
			source = readFirstLine(f);
			htmlDoc = Jsoup.parse(f, "UTF-8");
		} catch (IOException e) {
			System.out.println("Error parsing html: " + e.getMessage());
		}
		
		String title = htmlDoc.title();
		String body = htmlDoc.body().text();
		String relevant = getRelevant(htmlDoc);
		String snippet = reduceString(relevant, MAX_SNIPPET_SIZE);
		String h1 = htmlDoc.select("h1").text();
		String h2 = htmlDoc.select("h2").text();
		String h3 = htmlDoc.select("h3").text();
		String em = htmlDoc.select("em").text();
		String bold = htmlDoc.select("b").text();
		String italic = htmlDoc.select("i").text();
		String strong = htmlDoc.select("strong").text();
		Elements imgs = htmlDoc.select("img[alt]");
		String imgalt = "";
		Iterator<Element> it = imgs.iterator();
		if(it.hasNext()) {
			Element el;
			do {
				el = it.next();
				imgalt += el.attr("alt") + " ";
			} while(it.hasNext());
		}
		
		doc.add(new Field("docid", f.getName(), Field.Store.YES, Field.Index.NOT_ANALYZED));
		doc.add(new Field("source", source, Field.Store.YES, Field.Index.NOT_ANALYZED));
		doc.add(new Field("snippet", snippet, Field.Store.YES, Field.Index.NOT_ANALYZED));
		doc.add(new Field("body", body, Field.Store.NO, Field.Index.ANALYZED));
		doc.add(new Field("title", title, Field.Store.NO, Field.Index.ANALYZED));
		doc.add(new Field("headings", h1 + " " + h2 + " " + h3, Field.Store.NO, Field.Index.ANALYZED));
		doc.add(new Field("emphasized", em + " " + bold + " " + italic + " " + strong, Field.Store.NO, Field.Index.ANALYZED));
		doc.add(new Field("imgalt", imgalt, Field.Store.NO, Field.Index.ANALYZED));

		return doc;
	}
	
	private static String getRelevant(org.jsoup.nodes.Document d) { //TODO improve
		if(d == null)
			return "";
		Element e = d.select("p").first();
		String s = "";
		if(e != null)
			s = e.text();
		if(s == "")
			s = d.body().text();
		return s;
	}
	
	private static String readFirstLine(File f) throws FileNotFoundException {
		Scanner s = new Scanner(f);
		String line = "";
		if(s.hasNextLine())
			line = s.nextLine();
		s.close();
		return line;
	}

	private static String reduceString(String s, int maxChars) {
		if(s == null || s == "" || s.length() == 0)
			return "";
		String n = s.substring(0, Math.min(s.length()-1, maxChars));
		int cutoffIndex = n.lastIndexOf(' ');
		if(cutoffIndex > 0)
			n = n.substring(0, cutoffIndex);
		return n;
	}

}
