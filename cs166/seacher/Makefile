FLAGS = -g -Xlint:deprecation -cp
TEST = ../crawler/crawlerOut/ Index
# Put your jsoup and lucene jar paths below
MY_CLASSPATH = /my_apache/lucene-3.6.2/lucene-core-3.6.2.jar:../jsoup-1.7.2.jar
FILES = Indexer.java IndexRunner.java Searcher.java SearchRunner.java

make: $(FILES)
	javac $(FLAGS) $(CLASSPATH):$(MY_CLASSPATH) $(FILES)

run_index:
	java -cp $(CLASSPATH):$(MY_CLASSPATH) IndexRunner $(TEST)

clean:
	rm -f *.class
	rm -R Index
