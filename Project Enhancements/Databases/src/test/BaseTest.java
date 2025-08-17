package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import src.DatabaseHelper;
import java.sql.*;


class BaseTest {
	
	protected DatabaseHelper dbHelper;

	@BeforeEach
	void setUp() throws Exception {
		dbHelper = DatabaseHelper.getInstance();
		
		try (Connection conn = dbHelper.getConnection();
	             Statement stmt = conn.createStatement()) {
	            stmt.execute("DELETE FROM tasks");
	            stmt.execute("DELETE FROM contacts");
	            stmt.execute("DELETE FROM appointments");
	        }
		
	}

	@AfterEach
	void tearDown() throws Exception {
		dbHelper.clearDatabase();
	}

}
