
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.Hashtable;

import java.net.MalformedURLException;
import java.net.URL;

public class CrawlerFilter {
	
	private ArrayList<String> protocols;
	private ArrayList<String> domainExtensions;
	private CrawlerParser parser;
	private CrawlerFilter filter;
	
	private final int encodeSize = 2;
	private final String[] nonAscii = {" ", "&"};
	private final String[] encoding = {"%20", "%26"};
	private final String relLinkPattern_str = "^(\\.|\\.\\.)?/.*";
	private final String rootLinkPattern_str = "^/.*";
	private final String backLinkPattern_str = "^\\.\\./.*";
	private final String srcLinkPattern_str = "^(\\./)?.*";
	private final String htmlPattern_str = ".*\\.html?$";
	private final String phpPattern_str = ".*\\.php$";
	
	public CrawlerFilter() {
		protocols = new ArrayList<String>();
		domainExtensions = new ArrayList<String>();
		parser = new CrawlerParser();
	}
	
	//DONE could check for correct input
	public void addScheme(String scheme) {
		protocols.add(scheme);
	}
	
	//DONE could check for correct input
	public void addDomainExtension(String extension) {
		domainExtensions.add(extension);
	}
	
	//DONE
	public ArrayList<URL> getFilteredURLs(URL source, String linkContainer) {
		if(linkContainer == "" || linkContainer == null || source == null) return null;
		ArrayList<String> links = parser.getWebLinks(linkContainer);
		printArray("UN FILTERED:", links);
		ArrayList<URL> urls = filterLinks(source, links);
		printArray("REJECTS:", links);//TODO
		printURLs("ACCEPTED:", urls);//TODO
		return urls;
	}
	
	//*********************PRIVATE METHODS*****************************
	
	//TODO finish
	private ArrayList<URL> filterLinks(URL source, ArrayList<String> links) {
		ArrayList<URL> trash = new ArrayList<URL>();
		ArrayList<URL> urls = new ArrayList<URL>();
		ArrayList<String> relativeLinks = new ArrayList<String>();
		
		encodeCharacters(links);
		relativeLinks.addAll(filterRelativeLinks(links));
		relativeLinks = normalizeRelativeLinks(source, relativeLinks);
		
		urls.addAll(convertLinksToURLs(relativeLinks));
		urls.addAll(convertLinksToURLs(links));
		
		// Filter all urls and store the rejects
		trash.addAll(filterAnchors(urls));
		trash.addAll(filterByExtension(urls, domainExtensions));
		trash.addAll(filterByProtocol(urls, protocols));
		removeDuplicates(urls);

		// Put anything filtered out into links
		links.addAll(relativeLinks);
		for(int i = 0; i < trash.size(); ++i)
			links.add(trash.get(i).toString());
		
		return new ArrayList<URL>(urls);
	}
	
	//TODO don't know about how to handle all file types
	/*private ArrayList<URL> filterNonParcables(ArrayList<URL> urls) {
		ArrayList<URL> filtered = new ArrayList<URL>();
		for(int i = 0; i < urls.size(); ++i) {
			if(urls.get(i).getPath().matches(htmlPattern_str) || urls.get(i).getPath().matches(phpPattern_str))
				continue;
			filtered.add(urls.get(i));
			urls.remove(i--);
		}
		return filtered;
	}*/
	
	private void removeDuplicates(ArrayList<URL> urls) {
		for(int i = 0; i < urls.size(); ++i) {
			for(int j = i + 1; j < urls.size(); ++j) {
				if(urls.get(i).toString().compareTo(urls.get(j).toString()) == 0)
					urls.remove(j);
			}
		}
	}
	
	//DONE
	private ArrayList<URL> convertLinksToURLs(ArrayList<String> links) {
		ArrayList<URL> list = new ArrayList<URL>();
		URL url = null;
		for(int i = 0; i < links.size(); ++i) {
			try {
				url = new URL(links.get(i));
				list.add(url);
				links.remove(i--);
			} catch (MalformedURLException e) {
				/* Ignore the exception */
			}
		}
		return list;
	}
	
	//DONE
	private void encodeCharacters(ArrayList<String> links) {
		for(int i = 0; i < links.size(); ++i) {
			for(int j = 0; j < encodeSize; ++j)
				links.get(i).replaceAll(nonAscii[j], encoding[j]); 
		}
	}
	
	//TODO check
	private ArrayList<String> normalizeRelativeLinks(URL source, ArrayList<String> links) {
		ArrayList<String> list = new ArrayList<String>();
		String urlsource = source.getProtocol() + "://" + source.getHost() + (source.getPort() == -1 ? "" : ':' + source.getPort());
		for(int i = 0; i < links.size(); ++i) {
			if(links.get(i).matches(rootLinkPattern_str)) {
				list.add(urlsource + links.get(i));
			} else if(links.get(i).matches(backLinkPattern_str)) {
				links.get(i).replaceAll("^\\.\\./", "");
				String path = source.getPath();
				path.replaceAll("/[^/]/[^/]$", "");
				list.add(urlsource + path + '/' + links.get(i));
			} else if(links.get(i).matches(srcLinkPattern_str)) {
				links.get(i).replaceAll("^\\./", "");
				String path = source.getPath();
				path.replaceAll("/[^/]$", "");
				list.add(urlsource + path + '/' + links.get(i));
			} else {
				System.out.println("Unrecognized relative link: " + links.get(i));
			}
		}
		return list;
	}
	
	//DONE
	private ArrayList<String> filterRelativeLinks(ArrayList<String> links) {
		ArrayList<String> filtered = new ArrayList<String>();
		for(int i = 0; i < links.size(); ++i) {
			if(links.get(i).matches(relLinkPattern_str)) {
				filtered.add(links.get(i));
				links.remove(i--);
			}
		}
		return filtered;
	}
	
	//DONE
	private ArrayList<URL> filterAnchors(ArrayList<URL> urls) {
		ArrayList<URL> filtered = new ArrayList<URL>();
		for(int i = 0; i < urls.size(); ++i) {
			if(urls.get(i).toString().contains("#")) {
				filtered.add(urls.get(i));
				urls.remove(i--);
			}
		}
		return filtered;
	}
	
	//DONE
	private ArrayList<URL> filterByProtocol(ArrayList<URL> urls, ArrayList<String> acceptedProtocols) {
		ArrayList<URL> filtered = new ArrayList<URL>();
		boolean found;
		for(int i = 0; i < urls.size(); ++i) {
			// Remove links without the correct protocol
			found = false;
			for(int j = 0; j < acceptedProtocols.size(); ++j) {
				if(urls.get(i).getProtocol().compareTo(acceptedProtocols.get(j)) == 0) {
					found = true;
					break;
				}
			}
			if(!found) {
				filtered.add(urls.get(i));
				urls.remove(i--);
			}
		}
		return filtered;
	}
	
	//DONE
	private ArrayList<URL> filterByExtension(ArrayList<URL> urls, ArrayList<String> acceptedExtensions) {
		ArrayList<URL> filtered = new ArrayList<URL>();
		boolean found;
		for(int i = 0; i < urls.size(); ++i) {
			// Remove links without the correct domain name extensions
			found = false;
			for(int j = 0; j < acceptedExtensions.size(); ++j) {
				if(urls.get(i).getHost().contains(acceptedExtensions.get(j))) {
					found = true;
					break;
				}
			}
			if(!found) {
				filtered.add(urls.get(i));
				urls.remove(i--);
			}
		}
		return filtered;
	}
	
	//*********************DEBUG METHODS********************
	
	//DONE
	private void printArray(String header, ArrayList<String> a) {
		System.out.println(header);
		for(int i = 0; i < a.size(); ++i) {
			System.out.println('\t'+a.get(i));
		}
	}
	
	private void printURLs(String header, ArrayList<URL> a) {
		System.out.println(header);
		for(int i = 0; i < a.size(); ++i) {
			System.out.println('\t'+a.get(i).toString());
		}
	}
}

