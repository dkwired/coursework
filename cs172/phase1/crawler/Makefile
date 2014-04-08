FLAGS = -g
TEST = http://www.ucr.edu 10 1 ./crawlerOut/
FILES = CrawlerParser.java CrawlerFilter.java WebCrawler.java CrawlerTest.java

make:
	javac $(FLAGS) $(FILES)
#	javac -cp ../jsoup-1.7.2.jar Main.java

run:
	java CrawlerTest $(TEST)
#	java -cp ../jsoup-1.7.2.jar Main

clean:
	rm -f CrawlerTest.class
