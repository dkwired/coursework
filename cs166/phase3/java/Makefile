MY_PATH = edu/ucr/cs166
MY_CLASSPATH = lib/pg73jdbc3.jar:$(MY_PATH)
FLAGS = -g -cp
FILES = $(MY_PATH)/MovieNet.java $(MY_PATH)/ConsolePrompts.java $(MY_PATH)/EmbeddedSQL.java $(MY_PATH)/FileIO.java

make:
	javac $(FLAGS) $(CLASSPATH):$(MY_CLASSPATH) $(FILES)

clean:
	rm -f $(MY_PATH)/*.class
