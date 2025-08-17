package src;

import java.sql.*;

public class DatabaseHelper {
    private static final String DB_URL = "jdbc:sqlite:taskmanager.db";
    private static DatabaseHelper instance;
    
    private DatabaseHelper() {
        initializeDatabase();
    }
    
    public static synchronized DatabaseHelper getInstance() {
        if (instance == null) {
            instance = new DatabaseHelper();
        }
        return instance;
    }
    
    private void initializeDatabase() {
    	try (Connection conn = DriverManager.getConnection(DB_URL);
    	    Statement stmt = conn.createStatement()) {

    	    // Create contacts table
    	    stmt.execute("CREATE TABLE IF NOT EXISTS contacts (" +
    	         "id TEXT PRIMARY KEY, " +
    	         "first_name TEXT NOT NULL, " +
    	         "last_name TEXT NOT NULL, " +
    	         "phone TEXT NOT NULL, " +
    	         "address TEXT NOT NULL)");
            
    	    //tasks table
            stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS tasks (" +
                "id TEXT PRIMARY KEY, " +
                "name TEXT NOT NULL, " +
                "description TEXT NOT NULL)");
            
            //appointments table
            stmt.executeUpdate(
                "CREATE TABLE IF NOT EXISTS appointments (" +
                "id TEXT PRIMARY KEY, " +
                "date INTEGER NOT NULL, " +
                "description TEXT NOT NULL)");
        } catch (SQLException e) {
            System.err.println("Error initializing database: " + e.getMessage());
        }
    }
    
    public Connection getConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL);
    }
    
    public void clearDatabase() {
        try (Connection conn = getConnection();
             Statement stmt = conn.createStatement()) {
            stmt.execute("DELETE FROM contacts");
        } catch (SQLException e) {
            throw new RuntimeException("Failed to clear database", e);
        }
    }
}