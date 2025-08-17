package src;

import java.sql.*;

public class TaskService {
    private final DatabaseHelper dbHelper;
    
    public TaskService() {
        this.dbHelper = DatabaseHelper.getInstance();
    }

    /**
     * Adds a new task to the database after validation
     * @param ID Unique task ID (≤10 chars, not null/empty)
     * @param name Task name (≤20 chars, not null/empty)
     * @param description Description (≤50 chars, not null/empty)
     * @throws IllegalArgumentException if validation fails
     */
    public void addTask(String ID, String name, String description) {
        Task task = new Task(ID, name, description);
        
        String sql = "INSERT INTO tasks(id, name, description) VALUES(?,?,?)";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, task.getID());
            pstmt.setString(2, task.getName());
            pstmt.setString(3, task.getDescription());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            if (e.getMessage().contains("UNIQUE constraint failed")) {
                return; //ignore duplicates
            }
            throw new RuntimeException("Failed to add task", e);
        }
    }

    /**
     * Deletes a task by ID
     * @param ID The task ID to delete
     */
    public void deleteTask(String ID) {
        String sql = "DELETE FROM tasks WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, ID);
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to delete task", e);
        }
    }

    /**
     * Updates an existing task's name and description
     * @param ID Task ID to update
     * @param newName New task name (≤20 chars, not null/empty)
     * @param newDescription New description (≤50 chars, not null/empty)
     * @throws IllegalArgumentException if validation fails
     */
    public void updateTask(String ID, String newName, String newDescription) {
        Task task = getTask(ID);
        if (task == null) {
            throw new IllegalArgumentException("Task not found");
        }
        
        task.setName(newName);
        task.setDescription(newDescription);
        
        String sql = "UPDATE tasks SET name = ?, description = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, task.getName());
            pstmt.setString(2, task.getDescription());
            pstmt.setString(3, task.getID());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to update task", e);
        }
    }
    
    /**
     * Updates only the name of an existing task
     * @param ID Task ID to update
     * @param newName New task name (must be ≤20 chars, not null/empty)
     * @throws IllegalArgumentException if task not found or name invalid
     */
    public void updateTaskName(String ID, String newName) {
        Task task = getTask(ID);
        if (task == null) {
            throw new IllegalArgumentException("Task not found");
        }

        task.setName(newName);
        
        String sql = "UPDATE tasks SET name = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, task.getName());
            pstmt.setString(2, task.getID());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to update task name", e);
        }
    }

    /**
     * Updates only the description of an existing task
     * @param ID Task ID to update
     * @param newDescription New description (must be ≤50 chars, not null/empty)
     * @throws IllegalArgumentException if task not found or description invalid
     */
    public void updateTaskDescription(String ID, String newDescription) {
        Task task = getTask(ID);
        if (task == null) {
            throw new IllegalArgumentException("Task not found");
        }
        
        task.setDescription(newDescription);
        
        String sql = "UPDATE tasks SET description = ? WHERE id = ?";
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, task.getDescription());
            pstmt.setString(2, task.getID());
            pstmt.executeUpdate();
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to update task description", e);
        }
    }

    /**
     * Retrieves a task by ID
     * @param ID The task ID to find
     * @return Task object or null if not found
     */
    public Task getTask(String ID) {
        String sql = "SELECT * FROM tasks WHERE id = ?";
        Task task = null;
        
        try (Connection conn = dbHelper.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            
            pstmt.setString(1, ID);
            ResultSet rs = pstmt.executeQuery();
            
            if (rs.next()) {
                task = new Task(
                    rs.getString("id"),
                    rs.getString("name"),
                    rs.getString("description")
                );
            }
            
        } catch (SQLException e) {
            throw new RuntimeException("Failed to get task", e);
        }
        
        return task;
    }
}