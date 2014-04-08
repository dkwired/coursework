package edu.ucr.cs166;

import java.lang.Thread;

import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

import java.sql.Statement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;

public class MovieNet {

	private static enum State {MAIN_MENU, USER, ADMIN};
	private static EmbeddedSQL esql = null;
	private static String uid = "";
	private static BufferedReader in = new BufferedReader(
		new InputStreamReader(System.in));

	public static void main (String[] args) {
		if (args.length != 4) {
			System.err.println ("Usage: " +
				"java [-classpath <classpath>] " +
				EmbeddedSQL.class.getName () +
				" <dbname> <port> <user> <passwd>");
			return;
		}

		ConsolePrompts.Greeting();
		try{
			// use postgres JDBC driver.
			Class.forName ("org.postgresql.Driver").newInstance ();
			// instantiate the EmbeddedSQL object and creates a physical
			// connection.
			String dbname = args[0];
			String dbport = args[1];
			String user = args[2];
			String passwd = args[3];
			esql = new EmbeddedSQL (dbname, dbport, user, passwd);
			
			State state = State.MAIN_MENU;
			int menuChoice;
			boolean exit = false;
			while(!exit) {
				switch(state) {
					case MAIN_MENU:
						menuChoice = ConsolePrompts.getMainMenuChoice();
						if(menuChoice == 3) {
							exit = true;
							break;
						}
						state = handleMainMenuSelect(menuChoice);
						break;
					case USER:
						menuChoice = ConsolePrompts.getUserMenuChoice();
						state = handleUserMenuSelect(menuChoice);
						break;
					case ADMIN:
						menuChoice = ConsolePrompts.getAdminMenuChoice();
						state = handleAdminMenuSelect(menuChoice);
						break;
					default:
						System.out.println("Error: entered an unknown state");
				}
			}
		} catch(Exception e) {
			System.err.println (e.getMessage ());
		} finally {
			// make sure to cleanup the created table and close the connection.
			try{
				if(esql != null) {
					System.out.print("Disconnecting from database...");
					esql.cleanup ();
					System.out.println("Done\n\nBye !");
				}
			} catch (Exception e) {/*do nothing*/}
		}
	}
	
	////////////////////////////////////////////////////////////////
	// Menu choice handlers
	////////////////////////////////////////////////////////////////
	
	private static State handleMainMenuSelect(int choice) {
		State nextState = State.MAIN_MENU;
		switch(choice) {
			case 0:
				registerUser();
				nextState = State.MAIN_MENU;
				break;
			case 1:
				if(loginUser()) {
					nextState = State.USER;
					System.out.println("You are now logged into your account.");
					ConsolePrompts.waitOnKeyPress();
				}
				else {
					System.out.println("That user id and/or password is invalid.  Please try again\n" +
						"or register a new account if you do not already have one.");
					ConsolePrompts.waitOnKeyPress();
					nextState = State.MAIN_MENU;
				}
				break;
			case 2:
				if(loginAdmin()) {
					nextState = State.ADMIN;
					System.out.println("You are now logged in as a system administrator.");
					ConsolePrompts.waitOnKeyPress();
				}
				else {
					System.out.println("That user id and/or password is invalid.  Please try again.");
					ConsolePrompts.waitOnKeyPress();
					nextState = State.MAIN_MENU;
				}
				break;
			default:
				System.out.println("Invalid menu choice from main menu");
				nextState = State.MAIN_MENU;
		}
		return nextState;
	}
	
	private static State handleUserMenuSelect(int choice) {
		State nextState = State.USER;
		switch(choice) {
			case 0:
				orderMovies();
				nextState = State.USER;
				break;
			case 1:
				commentOnMovie();
				nextState = State.USER;
				break;
			case 2:
				viewMovieComments();
				nextState = State.USER;
				break;
			case 3:
				rankMovie();
				nextState = State.USER;
				break;
			case 4:
				addFavoriteMovies();
				nextState = State.USER;
				break;
			case 5:
				displayWall();
				nextState = State.USER;
				break;
			case 6:
				followUser();
				nextState = State.USER;
				break;
			case 7:
				displayAccountBalance();
				nextState = State.USER;
				break;
			case 8:
				addFundsToAccount();
				nextState = State.USER;
				break;
			case 9:
				addPreferredGenres();
				nextState = State.USER;
				break;
			case 10:
				setFavsViewPermissions();
				nextState = State.USER;
				break;
			case 11:
				setFollowPermissions();
				nextState = State.USER;
				break;
			case 12:
				changeAddress();
				nextState = State.USER;
				break;
			case 13:
				changePassword();
				nextState = State.USER;
				break;
			case 14:
				nextState = State.MAIN_MENU;
				break;
			default:
				System.out.println("Invalid menu choice from user menu");
				nextState = State.USER;
		}
		return nextState;
	}
	
	private static State handleAdminMenuSelect(int choice) {
		State nextState = State.ADMIN;
		switch(choice) {
			case 0:
				registerMovie();
				nextState = State.ADMIN;
				break;
			case 1:
				registerSeries();
				nextState = State.ADMIN;
				break;
			case 2:
				removeUser();
				nextState = State.ADMIN;
				break;
			case 3:
				removeComments();
				nextState = State.ADMIN;
				break;
			case 4:
				nextState = State.MAIN_MENU;
				break;
			default:
				System.out.println("Invalid menu choice from admin menu");
				nextState = State.ADMIN;
		}
		return nextState;
	}
	
	////////////////////////////////////////////////////////////////
	// Main Menu actions
	////////////////////////////////////////////////////////////////
	
	private static void registerUser() {
		String query;
		String[] creds;
		Statement stmt = null;
		ResultSet result;
		String[] userName = ConsolePrompts.getUserName();
		try {
			while(true) {
				creds = ConsolePrompts.getUserCredentials();
				query = String.format("SELECT user_id FROM users WHERE user_id='%s'", creds[0]);
				stmt = esql.getConnectionStatement();
				result = stmt.executeQuery(query);
				if(!result.next())
					break;
				System.out.println("That user id already exists.  Please enter a new one.");
				if(stmt != null) stmt.close();
			}
			String email = ConsolePrompts.getUserEmail();
			String[] address = ConsolePrompts.getUserAddress();
			if(address[4].length() == 0) address[4] = "0";
			query = String.format("INSERT INTO users (user_id, password, first_name, middle_name, last_name, " + 					"e_mail, street1, street2, state, country, zipcode, balance) VALUES ('%s', '%s', '%s', '%s', '%s', " +
				"'%s', '%s', '%s', '%s', '%s', %s, 0)",
				creds[0], creds[1], userName[0], userName[1], userName[2], email, address[0], address[1], address[2], address[3],
				address[4]);
			esql.executeUpdate(query);
		} catch(SQLException e) {
			// TODO user friendly error message
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("We're sorry, there was an error processing your request.\n" +
				"Please try again.");
		}
		ConsolePrompts.waitOnKeyPress();
	}
	
	private static boolean loginUser() {
		String[] loginInfo = ConsolePrompts.getLoginInfo();
		//TODO check loginInfo to prevent hacking
		String query = String.format("SELECT user_id FROM users WHERE user_id = '%s' AND password = '%s'",
			loginInfo[0], loginInfo[1]);
		return login(query, loginInfo[0]);
	}
	
	private static boolean loginAdmin() {
		String[] loginInfo = ConsolePrompts.getLoginInfo();
		String query = "SELECT super_user_id " +
					   "FROM super_user S " +
					   "WHERE S.super_user_id = (" +
					   		"SELECT U.user_id " +
					   		"FROM users U " +
					   		"WHERE U.user_id = '"+loginInfo[0]+"' AND U.password = '"+loginInfo[1]+"')";
		return login(query, loginInfo[0]);
	}
	
	private static boolean login(String query, String user) {
		Statement stmt = null;
		ResultSet result = null;
		boolean valid = false;
		try {
			stmt = esql.getConnectionStatement();
			result = stmt.executeQuery(query);
			if(result.next()) {
				uid = user;
				valid = true;
			}
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			// TODO user friendly error message
			System.out.println(e.getMessage());
			return false;
		} catch(Exception e) {
			System.out.println("We're sorry, there was an error processing your request.\n" +
				"Please try again.");
			ConsolePrompts.waitOnKeyPress();
			return false;
		}
		return valid;
	}
	
	////////////////////////////////////////////////////////////////
	// User Menu actions
	////////////////////////////////////////////////////////////////
	
	private static void orderMovies() {
		Statement stmt = null;
		int numOrdered = 0;
		int cost = 0;
		String query;
		try {
			stmt = esql.getConnectionStatement();
			ConsolePrompts.clearScreen();
			System.out.println("Choose from any of the following movies.  If you would like to order");
			System.out.println("multiple movies, you may do so by entering them one at a time.");
			System.out.println("To finish your order, leave the movie ID blank and press enter.");
			query = "SELECT * FROM video";
			ResultSet result = stmt.executeQuery(query);
			String format = "%-10.10s %-50.50s %-8.8s %-15.15s %-10.10s %-8.8s %-8.8s %-8.8s %-10.10s%n";
			printResultTable(format, 9, result);
			while(result.previous()) continue;
			ArrayList<ConsolePrompts.VideoOrder> order = ConsolePrompts.getUserOrderInfo();
			if(order == null || order.size() == 0) {
				System.out.println("No items were charged to your account.");
				if(stmt != null) stmt.close();
				ConsolePrompts.waitOnKeyPress();
				return;
			}
			for(int i = 0; i < order.size(); ++i) {
				query = String.format("INSERT INTO orders (video_id, user_id) VALUES (%s, '%s')",
					order.get(i).video_id, uid);
				esql.executeUpdate(query);
				query = String.format("SELECT online_price, dvd_price FROM video WHERE video_id = %s",
					order.get(i).video_id);
				result = stmt.executeQuery(query);
				if(!result.next())
					break;
				cost += result.getInt(order.get(i).type);
				++numOrdered;
			}
			System.out.println("Your order has been placed successfully.  Your total is: $" + cost);
		} catch(SQLException e) {
			System.out.println("Some of the items you selected were invalid.  " + numOrdered + " items were ordered successfully.  $" + cost + " has been charged to your account.");
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		try {
			query = String.format("UPDATE users SET balance = balance - %d WHERE user_id = '%s'", cost, uid);
			esql.executeUpdate(query);
		} catch(SQLException e) {
			System.out.println("Error updating balance: " + e.getMessage());
		}
		try {
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			System.out.println("Error closing statement: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}
	
	private static void commentOnMovie() {		
		try {
			Statement stmt = esql.getConnectionStatement();
			String query = "SELECT video_id, title, year FROM video";
			ResultSet result = stmt.executeQuery(query);
			ConsolePrompts.clearScreen();
			System.out.println("Comment on any of the following movies.");
			String format = "%-10.10s %-50.50s %-8.8s%n";
			printResultTable(format, 3, result);
			String[] comment = ConsolePrompts.getUserComment();
			if(comment == null) return;
			query = String.format("INSERT INTO comment (user_id, video_id, content) VALUES ('%s', '%s', '%s')",
			uid, comment[0], comment[1]);
			esql.executeUpdate(query);
			System.out.println("Your comment has been recorded.");
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			System.out.println("There was a problem storing your comment.  Please try again.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}
	
	private static void viewMovieComments() {
		String vid_id = ConsolePrompts.getMovieSelection();
		if(vid_id == "") return;
		String query = String.format("SELECT user_id, comment_time, content FROM comment WHERE video_id = %s", vid_id);
		Statement stmt = null;
		ResultSet result = null;
		try {
			stmt = esql.getConnectionStatement();
			result = stmt.executeQuery(query);
			String format = "%-10.10s %-15.15s %-300.300s%n";
			printResultTable(format, 3, result);
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			System.out.println("There was a problem finding comments for that video.  Please try again.");
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void rankMovie() {
		try {
			Statement stmt = esql.getConnectionStatement();
			String query = "SELECT * FROM video";
			ResultSet result = stmt.executeQuery(query);
			ConsolePrompts.clearScreen();
			System.out.println("You may rank any of the following movies.");
			String format = "%-10.10s %-50.50s %-8.8s %-15.15s %-10.10s %-8.8s %-8.8s %-8.8s %-10.10s%n";
			printResultTable(format, 9, result);
			String[] rank = ConsolePrompts.getUserRank();
			if(rank == null) return;
			query = String.format("INSERT INTO rate (user_id, video_id, rating) VALUES ('%s', %s, %s)",
			uid, rank[0], rank[1]);
			esql.executeUpdate(query);
			System.out.println("Thank you for your input.");
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			System.out.println("You may only rank a movie once.");
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void addFavoriteMovies() {
		try {
			Statement stmt = esql.getConnectionStatement();
			String query = "SELECT * FROM video";
			ResultSet result = stmt.executeQuery(query);
			ConsolePrompts.clearScreen();
			System.out.println("You may choose any of the following movies.");
			System.out.println("To select multiple items, just place a space between each selection.");
			String format = "%-10.10s %-50.50s %-8.8s %-15.15s %-10.10s %-8.8s %-8.8s %-8.8s %-10.10s%n";
			printResultTable(format, 9, result);
			ArrayList<String> favs = ConsolePrompts.getUserFavorites();
			if(favs.size() == 0) return;
			for(int i = 0; i < favs.size(); ++i) {
				query = String.format("INSERT INTO likes (user_id, video_id) VALUES ('%s', %s)", uid, favs.get(i));
				esql.executeUpdate(query);
			}
		} catch(SQLException e) {/*do nothing*/} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		System.out.println("Your favorites list has been updated.");
		ConsolePrompts.waitOnKeyPress();
	}

	private static void displayWall() {
		String format1 = "%-10.10s %-40.40s%n";
		String format2 = "%-10.10s %-10.10s %-40.40s%n";
		try {
			Statement stmt = esql.getConnectionStatement();
			String query = String.format("SELECT F.user_id_to, V.title FROM follow F, video V, likes L " +
				"WHERE F.user_id_from='%s' AND F.user_id_to=L.user_id AND L.video_id=V.video_id " +
				"GROUP BY F.user_id_to, V.title", uid);
			ResultSet result = stmt.executeQuery(query);
			System.out.println("Favorites of those whom you follow:");
			printResultTable(format1, 2, result);
			
			query = String.format("SELECT F.user_id_to, R.rating, V.title FROM follow F, video V, rate R " +
				"WHERE F.user_id_from='%s' AND F.user_id_to=R.user_id AND R.video_id=V.video_id " +
				"GROUP BY F.user_id_to, R.rating, V.title", uid);
			result = stmt.executeQuery(query);
			System.out.println("Movie ratings from those whom you follow:");
			printResultTable(format2, 3, result);
			
			query = String.format("SELECT F.user_id_to, V.title FROM follow F, video V, orders O " +
				"WHERE F.user_id_from='%s' AND F.user_id_to=O.user_id AND O.video_id=V.video_id " +
				"GROUP BY F.user_id_to, V.title", uid);
			result = stmt.executeQuery(query);
			System.out.println("Recently watched of those whom you follow:");
			printResultTable(format1, 2, result);
			stmt.close();
		} catch(SQLException e) {
			System.out.println("There was problem generating your wall.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		
		ConsolePrompts.waitOnKeyPress();
	}

	private static void followUser() {
		ConsolePrompts.clearScreen();
		System.out.println("Do you want to follow (1) or stop following (2) another user? ");
		int choice = ConsolePrompts.getMenuChoice(1,2);
		
		try {
			if(choice == 1) {
				String query = "SELECT user_id, first_name, middle_name, last_name FROM users";
				printUsers(query);
				System.out.println("Choose a user id from the above list whom you would like to follow.");
				String follow = ConsolePrompts.getUserID();
				query = String.format("INSERT INTO follow (user_id_from, user_id_to) VALUES ('%s', '%s')", uid, follow);
				esql.executeUpdate(query);
				System.out.println("You are now following "+follow);
			} else if(choice == 2) {
				String query = "SELECT U.user_id, U.first_name, U.middle_name, U.last_name " +
					"FROM users U, follow F " +
					"WHERE F.user_id_from='"+uid+"' AND U.user_id=F.user_id_to";
				printUsers(query);
				System.out.println("Choose the user id that you would like to stop following.");
				String follow = ConsolePrompts.getUserID();
				query = String.format("DELETE FROM follow WHERE user_id_from='%s' AND user_id_to='%s'", uid, follow);
				esql.executeUpdate(query);
				System.out.println("You are no longer following "+follow);
			} else {
				System.out.println("That is not a valid choice.");
			}
		} catch(SQLException e) {
			System.out.println("That user does not exist.");
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void displayAccountBalance() {
		String query = String.format("SELECT balance FROM users WHERE user_id='%s'", uid);
		try {
			Statement stmt = esql.getConnectionStatement();
			ResultSet result = stmt.executeQuery(query);
			result.next();
			int balance = result.getInt(1);
			System.out.println("Your current account balance is: $"+balance);
			stmt.close();
		} catch(SQLException e) {
			System.out.println("An error occurred while attempting to retrieve your account balance.");
			System.out.println("Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void addFundsToAccount() {
		String amount = ConsolePrompts.getUserMoneyAmount();
		String query = String.format("UPDATE users SET balance = balance + %s WHERE user_id = '%s'", amount, uid);
		try {
			esql.executeUpdate(query);
			System.out.println("$"+amount+" has been successfully transferred to this account.");
		} catch(SQLException e) {
			System.out.println("An error occurred while attempting to update your account balance.");
			System.out.println("Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void addPreferredGenres() {
		String query = "";
		Statement stmt = null;
		try {
			query = "SELECT * FROM genre";
			stmt = esql.getConnectionStatement();
			ResultSet result = stmt.executeQuery(query);
			ConsolePrompts.clearScreen();
			System.out.println("You may choose any of the following genres.");
			System.out.println("To select multiple items, just place a space between each selection.");
			String format = "%-10.10s %-30.30s%n";
			printResultTable(format, 2, result);
			ArrayList<String> prefs = ConsolePrompts.getUserPreferredGenres();
			if(prefs.size() == 0) {
				System.out.println("No items were added to your preferrences.");
			} else {
				for(int i = 0; i < prefs.size(); ++i) {
					query = String.format("INSERT INTO prefers (user_id, genre_id) VALUES ('%s', %s)",
					uid, prefs.get(i));
					esql.executeUpdate(query);
				}
			}
			System.out.println("Your new preferrences were successfully added.");
		} catch(SQLException e) {
			System.out.println("We were unable to complete your request.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		try {
			if(stmt != null) stmt.close();
		} catch(SQLException e) {
			System.out.println("Error closing statement: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void setFavsViewPermissions() {
		//TODO xtra credit
	}

	private static void setFollowPermissions() {
		//TODO xtra credit
	}

	private static void changeAddress() {
		String[] address = ConsolePrompts.getUserAddress();
		String query = String.format("UPDATE users SET street1='%s', street2='%s', state='%s', country='%s', zipcode=%s " +
			"WHERE user_id='%s'", address[0], address[1], address[2], address[3], address[4], uid);
		try {
			esql.executeUpdate(query);
			System.out.println("Your address information has been updated.");
		} catch(SQLException e) {
			System.out.println("We were unable to complete your request.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void changePassword() {
		String pwd = ConsolePrompts.getNewUserPassword();
		if(pwd.length() != 0) {
			String query = String.format("UPDATE users SET password='%s' WHERE user_id='%s'", pwd, uid);
			try {
				esql.executeUpdate(query);
				System.out.println("Your password has been successfully changed.");
			} catch(SQLException e) {
				System.out.println("We were unable to complete your request.");
				System.out.println("Error: " + e.getMessage());
			} catch(Exception e) {
				System.out.println("Internal Error: " + e.getMessage());
			}
			ConsolePrompts.waitOnKeyPress();
		}
	}

	////////////////////////////////////////////////////////////////
	// Admin Menu actions
	////////////////////////////////////////////////////////////////
	
	private static void registerMovie() {
		String[] mov = ConsolePrompts.getNewMovieInfo();
		try {
			String query = String.format("INSERT INTO video (title, year, online_price, dvd_price) VALUES ('%s', %s, %s, %s)",
				mov[0], mov[1], mov[2], mov[3]);
			esql.executeUpdate(query);
		} catch(SQLException e) {
			// TODO user friendly error message
			System.out.println(e.getMessage());
		} catch(Exception e) {
			System.out.println("We're sorry, there was an error processing your request.\n" +
				"Please try again.");
		}
		System.out.println(mov[0]+" has been added to the database.");
		ConsolePrompts.waitOnKeyPress();
	}
	
	private static void registerSeries() {
		
	}

	private static void removeUser() {
		System.out.println("Choose a user from the list below.");
		printUsers("SELECT user_id, first_name, middle_name, last_name FROM users");
		String user = ConsolePrompts.getUserID();
		String query = String.format("DELETE FROM users WHERE user_id='%s'", user);
		try {
			esql.executeUpdate(query);
			System.out.println("User '" + user + "' has been removed.");
		} catch(SQLException e) {
			System.out.println("We were unable to complete your request.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}

	private static void removeComments() {
		String query = "SELECT comment_id, user_id, comment_time, content FROM comment";
		try {
			Statement stmt = esql.getConnectionStatement();
			ResultSet result = stmt.executeQuery(query);
			String format = "%-15.15s %-10.10s %-15.15 %-300.300s%n";
			printResultTable(format, 4, result);
			stmt.close();
			String comment_id = ConsolePrompts.getCommentID();
			query = String.format("DELETE FROM comment WHERE comment_id=%s", comment_id);
			esql.executeUpdate(query);
			System.out.println("Comment " + comment_id + " has been removed.");
		} catch(SQLException e) {
			System.out.println("We were unable to complete your request.");
			System.out.println("Error: " + e.getMessage());
		} catch(Exception e) {
			System.out.println("Internal Error: " + e.getMessage());
		}
		ConsolePrompts.waitOnKeyPress();
	}
	
	////////////////////////////////////////////////////////////////
	// Helper methods
	////////////////////////////////////////////////////////////////
	
	private static void printUsers(String query) {
		try {
			Statement stmt = esql.getConnectionStatement();
			ResultSet result = stmt.executeQuery(query);
			String format = "%-10.10s %-20.20s %-20.20s %-20.20s%n";
			printResultTable(format, 4, result);
			stmt.close();
		} catch(SQLException e) {
			System.out.println("Error while printing out users.");
			System.out.println("Error: " + e.getMessage());
		}
	}
	
	private static int printResultTable(String format, int elements, ResultSet rs) {
		int rowCount = 0;
		try {
			ResultSetMetaData rsmd = rs.getMetaData();
			String header = createTableHeader(rsmd, elements, format);
			String row = "";
			System.out.println(header);
			while(rs.next()) {
				row = createRowString(rs, elements, format);
				if(row.trim().length() != 0) {
					System.out.print(row);
					++rowCount;
				}
    		}
    	} catch(SQLException e) {
    		System.out.println("An error occurred while attempting to print the requested table.");
    		System.out.println("Error: " + e.getMessage());
    	}
    	return rowCount;
	}
	
	private static String createFormatString(int minColSize, int maxColSize, int numCol) {
		String format = "";
		for(int i = 0; i < numCol; ++i)
			format += "%-"+minColSize+"."+maxColSize+"s ";
		return format.trim() + "%n";
	}
	
	private static String createTableHeader(ResultSetMetaData rsmd, int elements, String format) {
		String header = "";
		try {
		switch(elements) {
			case 1:
				header = String.format(format, rsmd.getColumnName(1));
				break;
			case 2:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2)); 
				break;
			case 3:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3)); 
				break;
			case 4:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4));
				break;
			case 5:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4), rsmd.getColumnName(5));
				break;
			case 6:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4), rsmd.getColumnName(5), rsmd.getColumnName(6));
				break;
			case 7:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4), rsmd.getColumnName(5), rsmd.getColumnName(6), rsmd.getColumnName(7));
				break;
			case 8:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4), rsmd.getColumnName(5), rsmd.getColumnName(6), rsmd.getColumnName(7),
					rsmd.getColumnName(8));
				break;
			case 9:
				header = String.format(format, rsmd.getColumnName(1), rsmd.getColumnName(2), rsmd.getColumnName(3),
					rsmd.getColumnName(4), rsmd.getColumnName(5), rsmd.getColumnName(6), rsmd.getColumnName(7),
					rsmd.getColumnName(8), rsmd.getColumnName(9));
				break;
			default:
				System.out.println("Too many columns to print.");
		}
		} catch(SQLException e) {
			System.out.println("An error occurred while generating the table header.");
			System.out.println("Error: " + e.getMessage());
		}
		return header;
	}
	
	private static String createRowString(ResultSet rs, int elements, String format) {
		String s = "";
		try {
		switch(elements) {
			case 1:
				s = String.format(format, rs.getString(1));
				break;
			case 2:
				s = String.format(format, rs.getString(1), rs.getString(2)); 
				break;
			case 3:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3)); 
				break;
			case 4:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4));
				break;
			case 5:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4), rs.getString(5));
				break;
			case 6:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4), rs.getString(5), rs.getString(6));
				break;
			case 7:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4), rs.getString(5), rs.getString(6), rs.getString(7));
				break;
			case 8:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4), rs.getString(5), rs.getString(6), rs.getString(7),
					rs.getString(8));
				break;
			case 9:
				s = String.format(format, rs.getString(1), rs.getString(2), rs.getString(3),
					rs.getString(4), rs.getString(5), rs.getString(6), rs.getString(7),
					rs.getString(8), rs.getString(9));
				break;
			default:
				System.out.println("Too many columns to print.");
		}
		} catch(SQLException e) {
			System.out.println("An error occurred while generating the table.");
			System.out.println("Error: " + e.getMessage());
		}
		return s;
	}

}

