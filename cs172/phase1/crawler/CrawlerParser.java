
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class CrawlerParser {

	private Pattern linkPattern;
	private Pattern hrefPattern;
	private final String linkPattern_str = "<[ \t\r\n]?[aA][^>]*>";
	private final String hrefPattern_str = "[hH][rR][eE][fF]=\"[^\"]+\"";

	public CrawlerParser() {
		linkPattern = Pattern.compile(linkPattern_str);
		hrefPattern = Pattern.compile(hrefPattern_str);
	}

	//DONE
	public ArrayList<String> getWebLinks(String html) {
		return getLinksFromTags(getLinkTags(html));
	}
	
	//*********************PRIVATE METHODS*****************************
	
	//DONE
	private ArrayList<String> getLinkTags(String html) {
		ArrayList<String> list = new ArrayList<String>();
		Matcher m = linkPattern.matcher(html);
		while(m.find())
			list.add(m.group());
		return list;
	}
	
	//DONE
	private ArrayList<String> getLinksFromTags(ArrayList<String> tags) {
		TreeSet<String> list = new TreeSet<String>();
		Matcher m;
		for(int i = 0; i < tags.size(); ++i) {
			m = hrefPattern.matcher(tags.get(i));
			if(m.find())
				list.add(m.group().replaceFirst("href=", "").replaceAll("^\"|\"$", ""));
		}
		return new ArrayList<String>(list);
	}
}
