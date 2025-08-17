package src;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

public class ContactService {
    private DatabaseHelper dbHelper;
    
    public ContactService() {
        dbHelper = DatabaseHelper.getInstance();
    }
    
    /**
     * Adds a new contact to the database
     * @param iD Contact ID (must be ≤ 10 chars, not null/empty)
     * @param firstName First name (must be ≤ 10 chars, not null/empty)
     * @param lastName Last name (must be ≤ 10 chars, not null/empty)
     * @param phone Phone number (must be exactly 10 digits, not null/empty)
     * @param address Address (must be ≤ 30 chars, not null/empty)
     * @throws IllegalArgumentException if any parameter is invalid
     */
    public void addContact(String iD, String firstName, String lastName, String phone, String address) {
        Contact contact = new Contact(iD, firstName, lastName, phone, address);
        
        String sql = "INSERT INTO contacts(id, first_name, last_name, phone, address) VALUES(?,?,?,?,?)";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, contact.getiD());
            pstmt.setString(2, contact.getFirstName());
            pstmt.setString(3, contact.getLastName());
            pstmt.setString(4, contact.getPhone());
            pstmt.setString(5, contact.getAddress());
            pstmt.executeUpdate();
        } catch (SQLException e) {
        	if (e.getMessage().contains("UNIQUE constraint failed")) {
                return; //ignore duplicates
            }
            System.err.println("Error adding contact: " + e.getMessage());
        }
    }
    
    /**
     * Deletes a contact from the database
     * @param iD ID of contact to delete
     */
    public void removeContact(String iD) {
        String sql = "DELETE FROM contacts WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, iD);
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error removing contact: " + e.getMessage());
        }
    }
    
    /**
     * Updates a contact's first name
     * @param iD Contact ID to update
     * @param firstName New first name (must be ≤ 10 chars, not null/empty)
     * @throws IllegalArgumentException if contact not found or name invalid
     */
    public void updateContactFirstName(String iD, String firstName) {
        Contact contact = getContact(iD);
        if (contact == null) {
            throw new IllegalArgumentException("Contact not found");
        }
        
        contact.setFirstName(firstName);
        
        String sql = "UPDATE contacts SET first_name = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, contact.getFirstName());
            pstmt.setString(2, contact.getiD());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error updating first name: " + e.getMessage());
        }
    }
    
    
    
    /**
     * Updates a contact's last name
     * @param iD Contact ID to update
     * @param lastName New last name (must be ≤ 10 chars, not null/empty)
     * @throws IllegalArgumentException if contact not found or last name invalid
     */
    public void updateContactLastName(String iD, String lastName) {
        Contact contact = getContact(iD);
        if (contact == null) {
            throw new IllegalArgumentException("Contact not found");
        }
        
        contact.setLastName(lastName);
        
        String sql = "UPDATE contacts SET last_name = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, contact.getLastName());
            pstmt.setString(2, contact.getiD());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error updating last name: " + e.getMessage());
        }
    }

    /**
     * Updates a contact's phone number
     * @param iD Contact ID to update
     * @param phone New phone number (must be exactly 10 digits, not null/empty)
     * @throws IllegalArgumentException if contact not found or phone invalid
     */
    public void updateContactPhone(String iD, String phone) {
        Contact contact = getContact(iD);
        if (contact == null) {
            throw new IllegalArgumentException("Contact not found");
        }

        contact.setPhone(phone);
        
        String sql = "UPDATE contacts SET phone = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, contact.getPhone());
            pstmt.setString(2, contact.getiD());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error updating phone: " + e.getMessage());
        }
    }

    /**
     * Updates a contact's address
     * @param iD Contact ID to update
     * @param address New address (must be ≤ 30 chars, not null/empty)
     * @throws IllegalArgumentException if contact not found or address invalid
     */
    public void updateContactAddress(String iD, String address) {
        Contact contact = getContact(iD);
        if (contact == null) {
            throw new IllegalArgumentException("Contact not found");
        }
        
        contact.setAddress(address);
        
        String sql = "UPDATE contacts SET address = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, contact.getAddress());
            pstmt.setString(2, contact.getiD());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            System.err.println("Error updating address: " + e.getMessage());
        }
    }
    
    /**
     * Retrieves a contact by ID
     * @param iD Contact ID to find
     * @return Contact object or null if not found
     */
    public Contact getContact(String iD) {
        String sql = "SELECT * FROM contacts WHERE id = ?";
        Contact contact = null;
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, iD);
            ResultSet rs = pstmt.executeQuery();
            
            if (rs.next()) {
                contact = new Contact(
                    rs.getString("id"),
                    rs.getString("first_name"),
                    rs.getString("last_name"),
                    rs.getString("phone"),
                    rs.getString("address")
                );
            }
        } catch (SQLException e) {
            System.err.println("Error getting contact: " + e.getMessage());
        }
        
        return contact;
    }
}