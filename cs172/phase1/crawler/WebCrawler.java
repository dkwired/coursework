
import java.lang.System;
import java.lang.Boolean;
import java.lang.Thread;
import java.lang.Runnable;

import java.util.TreeSet;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.io.IOException;

import java.net.MalformedURLException;
import java.net.URL;

public class WebCrawler {

	private final String filePrefix = "file";
	private final String fileExtension = "dld";

	private int maxPages;
	private int maxDepth;
	private String storageDirectory;

	private int fileNum = 0;
	private ConcurrentLinkedQueue<Node> frontier;
	private Hashtable<String, String> visited;
	
	private CrawlerFilter filter;

	//*********************PUBLIC METHODS************************
	
	public WebCrawler(int pageLimit, int depthLimit, String destDirectory) {
		maxPages = pageLimit < 0 ? 0 : pageLimit;
		maxDepth = depthLimit < 0 ? 0 : depthLimit;
		storageDirectory = destDirectory == null || destDirectory == "" ? "./" : destDirectory;
		
		frontier = new ConcurrentLinkedQueue<Node>();
		visited = new Hashtable<String, String>();
		
		filter = new CrawlerFilter();
	}
	
	//DONE
	public void setPageLimit(int limit) {
		maxPages = limit < 0 ? 0 : limit;
	}
	
	//DONE
	public void setDepthLimit(int limit) {
		maxDepth = limit < 0 ? 0 : limit;
	}
	
	//DONE could check for correct input
	public boolean addScheme(String scheme) {
		filter.addScheme(scheme);
		return true;
	}
	
	//DONE could check for correct input
	public boolean addDomainExtension(String extension) {
		filter.addDomainExtension(extension);
		return true;
	}
	
	//DONE
	public void launch(String sourceURL) throws MalformedURLException {
		frontier.add(new Node(new URL(sourceURL), 0));
		crawlPage();
	}
	
	//*********************CRAWLER METHODS************************
	
	//TODO finish
	private void crawlPage() {
		if(fileNum >= maxPages) return;

		Node currentURL = frontier.poll();
		if(currentURL == null) return;
		//TODO get robot list
		String s = currentURL.url.toString();
		if(visited.put(s, s) != null || currentURL.depth > maxDepth) return; //TODO also check robot list
		
		ArrayList<URL> urls = filter.getFilteredURLs(currentURL.url, getNextPage(currentURL.url));
		if(urls == null) return;
		
		// Spawn crawlers for each link
		for(int i = 0; i < urls.size(); ++i) {
			frontier.add(new Node(urls.get(i), currentURL.depth + 1));
			(new Thread(new Runnable() { 
				@Override
				public void run() {
					crawlPage();
				}
			})).start();
		}
	}

	//DONE
	private String getNextFileName() {
		return storageDirectory + filePrefix + (fileNum++) + "." + fileExtension;
	}
	
	//DONE
	private String getNextPage(URL url) {
		if(url == null) return null;
		String html = "";
		try {
			html = downloadWebFile(url, getNextFileName());
		} catch(IOException e) {
			System.out.println("IO Exception while downloading: " + url.toString() + '\n' + e.getMessage());
			System.exit(1);
		}
		return html;
	}
	
	//DONE
	private class Node {
		
		public int depth;
		public URL url;
		
		public Node(URL url, int depth) {
			this.url = url;
			this.depth = depth;
		}
	}

	//*********************DOWNLOAD/STORE PAGE METHODS********************
	
	//DONE
	private String downloadWebFile(URL url, String outFile) throws IOException {
		BufferedReader x = new BufferedReader(new InputStreamReader(url.openConnection().getInputStream()));
		BufferedWriter fos = new BufferedWriter(new FileWriter(outFile));
	
		String file = "";
		while(x.ready()) {
			String line = x.readLine();
			fos.write(line);
			fos.write("\n");
			file += line;
		}

		x.close();
		fos.close();
		
		return file;
	}
}

