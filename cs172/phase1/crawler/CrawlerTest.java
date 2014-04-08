
import java.lang.System;
import java.lang.Integer;
import java.lang.Exception;

public class CrawlerTest {	
	/**
	  * args:	String => seed url
	  *			int => max pages to retrieve
	  *			int => max depth to crawl
	  *			String => output directory
	  */
	public static void main(String[] args) {
		if(args.length < 4)
			System.out.println("Must pass in arguments: seed url, max pages to retrieve, max crawl depth, output directory\n");
		
		int maxPages = 0, maxDepth = 0;
		
		try {
			maxPages = Integer.parseInt(args[1]);
			maxDepth = Integer.parseInt(args[2]);
		} catch(Exception e) {
			System.out.println("Input Error: " + e.getMessage());
			System.exit(1);
		}
				
		try {
			WebCrawler crawler = new WebCrawler(maxPages, maxDepth, args[3]);
			crawler.addScheme("http");
			crawler.addDomainExtension(".edu");
			crawler.launch(args[0]);
		} catch(Exception e) {
			System.out.println("Launch Error: " + e.getMessage());
			System.exit(1);
		}
	}
}
