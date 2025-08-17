package src;


import java.sql.*;
import java.util.Date;

public class AppointmentService {
    private final DatabaseHelper dbHelper;
    
    public AppointmentService() {
        this.dbHelper = DatabaseHelper.getInstance();
    }

    /**
     * Adds a new appointment to the database after validation
     * @param ID Unique appointment ID (≤10 chars, not null/empty)
     * @param date Future date (not null or in the past)
     * @param description Description (≤50 chars, not null/empty)
     * @throws IllegalArgumentException if validation fails
     */
    public void addAppointment(String ID, Date date, String description) {
        Appointment appointment = new Appointment(ID, date, description);
        
        String sql = "INSERT INTO appointments(id, date, description) VALUES(?,?,?)";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, appointment.getAppID());
            pstmt.setLong(2, appointment.getDate().getTime());
            pstmt.setString(3, appointment.getDesc());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            if (e.getMessage().contains("UNIQUE constraint failed")) {
                return; // ignore duplicates
            }
            throw new RuntimeException("Failed to add appointment", e);
        }
    }

    /**
     * Deletes an appointment by ID
     * @param ID The appointment ID to delete
     */
    public void deleteAppointment(String ID) {
        String sql = "DELETE FROM appointments WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, ID);
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to delete appointment", e);
        }
    }

    /**
     * Updates an existing appointment's date and description
     * @param ID Appointment ID to update
     * @param newDate New future date (not null or in the past)
     * @param newDescription New description (≤50 chars, not null/empty)
     * @throws IllegalArgumentException if validation fails
     */
    public void updateAppointment(String ID, Date newDate, String newDescription) {
        Appointment appointment = getAppointment(ID);
        if (appointment == null) {
            throw new IllegalArgumentException("Appointment not found");
        }
        
        appointment.setDate(newDate);
        appointment.setDesc(newDescription);
        
        String sql = "UPDATE appointments SET date = ?, description = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setLong(1, appointment.getDate().getTime());
            pstmt.setString(2, appointment.getDesc());
            pstmt.setString(3, appointment.getAppID());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to update appointment", e);
        }
    }

    /**
     * Retrieves an appointment by ID
     * @param ID The appointment ID to find
     * @return Appointment object or null if not found
     */
    public Appointment getAppointment(String ID) {
        String sql = "SELECT * FROM appointments WHERE id = ?";
        Appointment appointment = null;
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, ID);
            ResultSet rs = pstmt.executeQuery();
            
            if (rs.next()) {
                appointment = new Appointment(
                    rs.getString("id"),
                    new Date(rs.getLong("date")),
                    rs.getString("description")
                );
            }
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to get appointment", e);
        }
        
        return appointment;
    }
}